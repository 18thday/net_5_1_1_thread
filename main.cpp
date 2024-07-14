#include <iostream>
#include <thread>
#include <chrono>

void add_client(size_t& client_count, size_t max_count) {
    std::cout << "add_client start" << std::endl;
    for (size_t i = 0; i < max_count; ++i) {
        ++client_count;
        std::cout << "add_client " << i << " : current client count = " << client_count << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "add_client finished" << std::endl;
}

void work_operator(size_t& client_count) {
    std::cout << "work_operator start" << std::endl;
    while (client_count > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        --client_count;
        std::cout << "work_operator : current client count = " << client_count << std::endl;
    }
    std::cout << "work_operator finished" << std::endl;
}


int main() {
    std::cout << "main start" << std::endl;
    size_t client_count = 0;
    std::thread th_add_client{add_client, std::ref(client_count), 11};
    std::thread th_work_operator{work_operator, std::ref(client_count)};
    th_add_client.join();
    th_work_operator.join();

    std::cout << "main finished" << std::endl;
    return 0;
}
