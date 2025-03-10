#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
    Bureaucrat a("Alice", 1);
    Bureaucrat b("Bob", 150);

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    try {
        a.incrementGrade();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        b.decrementGrade();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        Bureaucrat c("Charlie", 0);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        Bureaucrat d("David", 151);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        a.decrementGrade();
        std::cout << "decriment: " << a << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}