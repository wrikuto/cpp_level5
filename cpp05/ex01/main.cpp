#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
    Bureaucrat a("a", 1);
    Bureaucrat b("b", 150);
    Bureaucrat c("c", 0);
    Bureaucrat d("d", 156);

    a.incrementGrade();
    std::cout << a << std::endl;
    b.decrementGrade();
    std::cout << b << std::endl;
    b.incrementGrade();
    std::cout << b << std::endl;


    std::cout << std::endl;
    Form f("important form", 50, 20);
    Form f1("more important form", 150, 20);
    Form fBad("bad form", 160, 120);

    a.signForm(f);
    b.signForm(f1);
    std::cout << f << std::endl;
    b.signForm(f);
    std::cout << f << std::endl;

    return (0);
}