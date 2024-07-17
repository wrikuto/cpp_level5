#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(const std::string &name, int grade)
:_name(name)
{
	try
	{
		if (grade < 1)
			throw GradeTooLowException();
		else if (150 < grade)
			throw GradeTooHighException();
		else
			this->_grade = grade;
	}
	catch (const Bureaucrat::GradeTooLowException &err)
	{
		std::cerr << err.what() << std::endl;
	}
	catch (const Bureaucrat::GradeTooHighException &err)
	{
		std::cerr << err.what() << std::endl;
	}
	return ;

}

Bureaucrat::Bureaucrat(const Bureaucrat &src)
: _name(src._name), _grade(src._grade) {}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &src)
{
    if (this != &src)
       this->_grade = src._grade;
    return (*this);
}

Bureaucrat::~Bureaucrat() {}

std::string const &Bureaucrat::getName() const 
{
	return (_name);
}

int Bureaucrat::getGrade() const 
{
	return (_grade);
}

void Bureaucrat::incrementGrade()
{
	try
	{
		if (150 < this->_grade + 1)
			throw GradeTooHighException();
		_grade++;
	}
	catch(const Bureaucrat::GradeTooHighException &err)
	{
		std::cerr << err.what() << std::endl;
	}
	
}

void Bureaucrat::decrementGrade()
{
	try
	{  
		if (this->_grade - 1 < 1)
			throw GradeTooLowException();
		_grade--;
	}
	catch(const Bureaucrat::GradeTooLowException &err)
	{
		std::cerr << err.what() << std::endl;
	}
	
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return ("exception: Bureaucrat grade is too high!");
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return ("exception: Bureaucrat grade is too low!");
}

void Bureaucrat::signForm(Form &form) {
    try
	{
        form.beSigned(*this);
        std::cout << this->getName() << " signed " << form.getName() << std::endl;
    }
	catch (const std::exception &err)
	{
        std::cout << \
		this->getName() << " couldn’t sign " << form.getName() << " because " \
		<< err.what() \
		<< std::endl;
    }
}


std::ostream & operator<<(std::ostream & out, Bureaucrat const &obj)
{
    out << obj.getName() << ", bureaucrat grade " << obj.getGrade();
    return (out);
}
