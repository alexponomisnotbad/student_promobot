#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    int n;
    std::cout << "Введите целое число: ";
    std::cin >> n;
    std::cout << "Вы ввели число: " << n << std::endl;
    int interval = n; // интервал в секундах
    while (true) {
        std::cout << "Hello, I'm alive" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
    return 0;
}
