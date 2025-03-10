#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <map>

Intern::Intern()
{}

Intern::Intern(const Intern &other)
{
    *this = other;
}

Intern::~Intern()
{}

Intern &Intern::operator=(const Intern &other)
{
    (void)other;
    return (*this);
}

AForm *Intern::makeForm(std::string formName, std::string target) const
{
    std::map<std::string, int> formMap;
    formMap["shrubbery creation"] = 0;
    formMap["robotomy request"] = 1;
    formMap["presidential pardon"] = 2;

    switch (formMap[formName])
    {
        case 0:
            std::cout << "Intern creates " << formName << std::endl;
            return new ShrubberyCreationForm(target);
        case 1:
            std::cout << "Intern creates " << formName << std::endl;
            return new RobotomyRequestForm(target);
        case 2:
            std::cout << "Intern creates " << formName << std::endl;
            return new PresidentialPardonForm(target);
        default:
            std::cout << "Intern couldn't create form: " << formName << std::endl;
            return NULL;
    }
}