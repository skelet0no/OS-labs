#include <vector>
#include <algorithm>
#include <random>
#include <pthread.h>

const int NUM_CARDS = 52;
int countEqualPairs = 0;
pthread_mutex_t mutex;

struct ThreadData {
    int rounds;
};


std::vector<int> createDeck() {
    std::vector<int> deck(NUM_CARDS);
    for (int i = 0; i < NUM_CARDS; ++i) {
        deck[i] = i % 13;
    }
    return deck;
}

void* simulateRounds(void* threadArg) {
    ThreadData* data = static_cast<ThreadData*>(threadArg);
    int localCount = 0;
    std::default_random_engine generator;

    for (int i = 0; i < data->rounds; ++i) {
        std::vector<int> deck = createDeck();
        std::shuffle(deck.begin(), deck.end(), generator);
        if (deck[0] == deck[1]) {
            localCount++;
        }
    }

    pthread_mutex_lock(&mutex);
    countEqualPairs += localCount;
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

double cards(const int rounds, const int threads) {
    int numRounds = rounds;
    int maxThreads = threads;

    pthread_t stream[maxThreads];
    pthread_mutex_init(&mutex, nullptr);

    int roundsPerThread = numRounds / maxThreads;
    ThreadData threadData[maxThreads];

    for (int i = 0; i < maxThreads; ++i) {
        threadData[i].rounds = roundsPerThread;
        pthread_create(&stream[i], nullptr, simulateRounds, (void*)&threadData[i]);
    }

    for (int i = 0; i < numRounds % maxThreads; ++i) {
        threadData[i].rounds += 1;
    }

    for (int i = 0; i < maxThreads; ++i) {
        pthread_join(stream[i], nullptr);
    }

    pthread_mutex_destroy(&mutex);

    double probability = static_cast<double>(countEqualPairs) / numRounds;
    countEqualPairs = 0;
    return probability;
}
