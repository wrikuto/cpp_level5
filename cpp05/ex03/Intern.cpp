#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

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
	std::string formNames[] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	AForm *forms[] = {
		new ShrubberyCreationForm(target),
		new RobotomyRequestForm(target),
		new PresidentialPardonForm(target)
	};

	for (int i = 0; i < 3; i++)
	{
		if (formNames[i] == formName)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (forms[i]);
		}
		delete forms[i];
	}

	std::cout << "Intern couldn't create form: " << formName << std::endl;
	return (nullptr);
}
