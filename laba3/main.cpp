#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SHM_NAME "/shm_example"
#define SHM_SIZE 1024

volatile sig_atomic_t signalReceived = 0;
volatile sig_atomic_t childCompleted = 0;

void handleError(const std::string& message) {
    perror(message.c_str());
    exit(EXIT_FAILURE);
}

void signalHandler(int signum) {
    signalReceived = 1;
}

void childSignalHandler(int signum) {
    childCompleted = 1;
}

int main() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        handleError("shm_open");
    }
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        handleError("ftruncate");
    }
    void* shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        handleError("mmap");
    }

    signal(SIGUSR1, signalHandler);
    signal(SIGCHLD, childSignalHandler);

    pid_t pid = fork();
    if (pid < 0) {
        handleError("fork");
    }

    if (pid == 0) {
        execl("./child", "child", filename.c_str(), nullptr);
        handleError("execl");
    } else {
        while (!childCompleted) {
            pause();

            if (signalReceived) {
                signalReceived = 0;
                std::cout << static_cast<char*>(shm_ptr);
            }
        }

        if (munmap(shm_ptr, SHM_SIZE) == -1) {
            handleError("munmap");
        }
        if (shm_unlink(SHM_NAME) == -1) {
            handleError("shm_unlink");
        }
    }

    return 0;
}
