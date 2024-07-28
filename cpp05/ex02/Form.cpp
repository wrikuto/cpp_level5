#include "Form.hpp"

Form::Form(const std::string &name, int signGrade, int executeGrade)
: _name(name), _isSigned(false), _signGrade(signGrade), _executeGrade(executeGrade)
{
	try
	{
		if (signGrade < 1 || executeGrade < 1)
			throw GradeTooLowException();
		if (signGrade > 150 || executeGrade > 150)
			throw GradeTooHighException();
	}
	catch (Form::GradeTooHighException & err)
	{
		std::cout << err.what() << std::endl;
	}
	catch (Form::GradeTooLowException & err)
	{
		std::cout << err.what() << std::endl;
	}
}

Form::Form(const Form &src)
 : _name(src._name), _isSigned(src._isSigned), _signGrade(src._signGrade), _executeGrade(src._executeGrade)
{
	try
	{
		if (_signGrade < 1 || _executeGrade < 1)
			throw GradeTooHighException();
		if (_signGrade > 150 || _executeGrade > 150)
			throw GradeTooLowException();
	}
	catch (Form::GradeTooHighException & err)
	{
		std::cout << err.what() << std::endl;
	}
	catch (Form::GradeTooLowException & err)
	{
		std::cout << err.what() << std::endl;
	}
}

Form &Form::operator=(const Form &src)
{
	if (this != &src)
		this->_isSigned = src._isSigned;
	return (*this);
}

Form::~Form() {}

const std::string &Form::getName() const
{
	return (_name);
}

bool Form::isSigned() const
{
	return (_isSigned);
}

int Form::getSignGrade() const
{
	return (_signGrade);
}

int Form::getExecuteGrade() const {
	return (_executeGrade);
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() < _signGrade)
		throw GradeTooLowException();
	_isSigned = true;
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Form grade is too high!");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Form grade is too low!");
}

std::ostream &operator<<(std::ostream &out, const Form &form) {
	out << "Form " << form.getName() << ", sign status: ";
	if (form.isSigned())
		out << "signed";
	else
		out << "not signed";
	out << ", sign grade: " << form.getSignGrade() << ", execute grade: " << form.getExecuteGrade() << ".";
	return (out);
}