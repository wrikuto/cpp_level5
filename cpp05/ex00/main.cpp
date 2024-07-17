#include "Bureaucrat.hpp"

int main(void)
{
    Bureaucrat a("a", 1);
    Bureaucrat b("b", 150);
    Bureaucrat c("c", 0);
    Bureaucrat d("d", 156);
	Bureaucrat e("e", -20);

    a.incrementGrade();
    std::cout << a << std::endl;
    b.decrementGrade();
    std::cout << b << std::endl;
    b.incrementGrade();
    std::cout << b << std::endl; 
    b.incrementGrade();
    std::cout << b << std::endl; 


    return (0);
}
