#include <iostream>
#include <unistd.h>
#include <string>
#include <tuple>
#include <thread>

#include <zmq.hpp>
#include "s_list.hpp"

static ProcessList processes(0);

zmq::context_t ctx;
zmq::socket_t root_socket(ctx, ZMQ_REQ);

std::vector<int> node_ids;
std::vector<std::string> node_values;

void send_msg() {
    zmq::message_t request;

    auto result = root_socket.recv(request, zmq::recv_flags::none);

    std::string message = std::string(static_cast<char*>(request.data()), request.size());
    std::cout << message << std::endl;
}

std::string next(std::string* s) {
    unsigned long i = 0;
    for (; i < s->size() && (*s)[i] != ' ' && (*s)[i] != '\n'; ++i) {}

    std::string result = s->substr(0, i);
    *s = s->substr(i + 1, s->size());

    return result;
}

int main() {
    std::string line;
    root_socket.connect("ipc:///tmp/lab5_0");

    pid_t child_pid = fork();

    if (child_pid == -1) {
        std::cout << "Error: Could not fork current process!\n";
        return 1;
    } else if (child_pid == 0) {
        const char* argv[] = {"./child.out", "ipc:///tmp/lab5_0", NULL};
        if (execv(argv[0], const_cast<char* const*>(argv)) == -1)
            std::cout << "Error: Could not create a child process!\n";
    }

    processes.insert(std::make_tuple(0, true));

    std::cout << "> ";
    while (getline(std::cin, line)) {
        line.push_back('\n');
        std::string command = next(&line);

        if (command == "create") {
            int child_id = std::stoi(next(&line));

            if (processes.is_in_list(child_id)) {
                std::cout << "Error: Child with id = " << child_id << " already exists!\n";
            } else {
                std::string socket_path = "ipc:///tmp/lab5_" + std::to_string(child_id);

                pid_t child_pid = fork();

                if (child_pid == -1) {
                    std::cout << "Error: Could not fork current process!\n";
                } else if (child_pid == 0) {
                    const char* argv[] = {"./child.out", socket_path.c_str(), NULL};
                    if (execv(argv[0], const_cast<char* const*>(argv)) == -1)
                        std::cout << "Error: Could not create a child process!\n";
                } else {
                    std::cout << "Ok: child pid is " << child_pid << '\n';
                    processes.insert(std::make_tuple(child_id, true));
                }
            }
        } else if (command == "exec") {
            int child_id = std::stoi(next(&line));
            std::string var = next(&line);

            if (line.size() > 0) {
                std::string value = next(&line);

                if (!processes.is_in_list(child_id)) {
                    std::cout << "Error: No child with id = " << child_id << "!\n";
                    std::cout << "> ";
                    continue;
                }

                std::string msg_command = "s " + var + " " + value + '\n';
                root_socket.send(zmq::buffer(msg_command), zmq::send_flags::none);

                node_ids.push_back(child_id);
                node_values.push_back(value);

                std::thread wait(send_msg);
                wait.join();
            } else {
                if (!processes.is_in_list(child_id)) {
                    std::cout << "Error: No child with id = " << child_id << "!\n";
                    std::cout << "> ";
                    continue;
                }

                std::string msg_command = "g " + var + '\n';
                root_socket.send(zmq::buffer(msg_command), zmq::send_flags::none);

                std::thread wait(send_msg);
                wait.join();
            }
        } else if (command == "pingall") {
            std::vector<int> nodes_with_values;

            for (size_t i = 0; i < node_ids.size(); ++i) {
                if (!node_values[i].empty()) {
                    nodes_with_values.push_back(node_ids[i]);
                }
            }

            if (nodes_with_values.empty()) {
                std::cout << "Ok: -1\n";
            } else {
                std::cout << "Ok:";
                for (size_t i = 0; i < nodes_with_values.size(); ++i) {
                    std::cout << " " << nodes_with_values[i];
                    if (i < nodes_with_values.size() - 1) {
                        std::cout << ";";
                    }
                }
                std::cout << "\n";
            }
        } else if (command == "exit") {
            break;
        }
        std::cout << "> ";
    }

    return 0;
}
