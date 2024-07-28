#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void) {
    try {
        Bureaucrat a("a", 1);
        Bureaucrat b("b", 150);

        ShrubberyCreationForm form1("home");
        RobotomyRequestForm form2("office");
        PresidentialPardonForm form3("criminal");

        a.signForm(form1);
        a.executeForm(form1);

        a.signForm(form2);
        a.executeForm(form2);

        a.signForm(form3);
        a.executeForm(form3);

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return (0);
}
