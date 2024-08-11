#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	try
	{
		Bureaucrat boss("Boss", 1);
		Intern someRandomIntern;

		AForm *shrubbery = someRandomIntern.makeForm("shrubbery creation", "Home");
		AForm *robotomy = someRandomIntern.makeForm("robotomy request", "Bender");
		AForm *pardon = someRandomIntern.makeForm("presidential pardon", "Marvin");


		boss.signForm(*shrubbery);
		boss.executeForm(*shrubbery);
		delete shrubbery;


		boss.signForm(*robotomy);
		boss.executeForm(*robotomy);
		delete robotomy;


		boss.signForm(*pardon);
		boss.executeForm(*pardon);
		delete pardon;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
