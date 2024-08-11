#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src)
: AForm(src), _target(src._target)
{}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &src)
{
	if (this != &src)
	{
		AForm::operator=(src);
	}
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
    AForm::execute(executor);
    std::ofstream ofs((_target + "_shrubbery").c_str());
    ofs << " ^\n/ \\\n |" << std::endl;
    ofs.close();
}
