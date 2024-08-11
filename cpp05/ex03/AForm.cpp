#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string &name, int signGrade, int executeGrade)
: _name(name), _isSigned(false), _signGrade(signGrade), _executeGrade(executeGrade)
{
	if (signGrade < 1 || executeGrade < 1)
		throw GradeTooHighException();
	if (signGrade > 150 || executeGrade > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm &src)
: _name(src._name), _isSigned(src._isSigned), _signGrade(src._signGrade), _executeGrade(src._executeGrade) {}

AForm &AForm::operator=(const AForm &src)
{
	if (this != &src) {
		this->_isSigned = src._isSigned;
	}
	return (*this);
}

AForm::~AForm() {}

const std::string &AForm::getName() const
{
	return (_name);
}

bool AForm::isSigned() const
{
	return (_isSigned);
}

int AForm::getSignGrade() const
{
	return (_signGrade);
}

int AForm::getExecuteGrade() const
{
	return (_executeGrade);
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > _signGrade)
		throw GradeTooLowException();
	_isSigned = true;
}

void AForm::execute(Bureaucrat const &executor) const
{
	if (!_isSigned)
		throw FormNotSignedException();
	if (executor.getGrade() > _executeGrade)
		throw GradeTooLowException();
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Form grade is too high!");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Form grade is too low!");
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return ("Form is not signed!");
}

std::ostream &operator<<(std::ostream &out, const AForm &form)
{
	out << "Form " << form.getName() << ", sign status: ";
	if (form.isSigned())
		out << "signed";
	else
		out << "not signed";
	out << ", sign grade: " << form.getSignGrade() << ", execute grade: " << form.getExecuteGrade() << ".";
	return (out);
}
