#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <cstdlib>   // getenv
#include <unistd.h>  // isatty

Bureaucrat::Bureaucrat()
	: name_("Default"), grade_(kMinGrade)
{
	std::cout << CYAN "[Bureaucrat default constructor]" RESET " " << name_ << std::endl;
}

Bureaucrat::Bureaucrat(const std::string name, int grade)
	: name_(name), grade_(grade)
{
	checkGrade(grade);
	std::cout << CYAN "[Bureaucrat parameterized constructor]" RESET " " << name_ << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat & src)
{
	*this = src; // operator= を呼ぶ
	std::cout << CYAN "[Bureaucrat copy constructor]" RESET " " << name_ << std::endl;
}

const Bureaucrat & Bureaucrat::operator=(const Bureaucrat & src)
{
	if (this != &src)
	{
		this->grade_ = src.grade_;
	}
	std::cout << CYAN "[Bureaucrat operator=]" RESET " " << name_ << std::endl;

	return *this;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << CYAN "[Bureaucrat destructor]" RESET " " << name_ << std::endl;
}

std::string Bureaucrat::getName() const {	return name_; }
int Bureaucrat::getGrade() const { return grade_; }
void Bureaucrat::setGrade(int grade) 
{ 
	checkGrade(grade); 
	grade_ = grade;
}

void Bureaucrat::incrementGrade() 
{
	checkGrade(grade_ - 1);
	--grade_;
}

void Bureaucrat::decrementGrade() 
{
	checkGrade(grade_ + 1);
	++grade_;
}

void Bureaucrat::signForm(Form& form) const
{
    try {
        form.beSigned(*this);
        // 仕様の例: "<bureaucrat> signed <form>"
        std::cout << getName() << " signed " << form.getName() << std::endl;
    } catch (std::exception& e) {
        // 仕様の例: "<bureaucrat> couldn’t sign <form> because <reason>."
        std::cout << getName() << " couldn’t sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}

void Bureaucrat::checkGrade(int grade) const
{
	if (grade < kMaxGrade)
		throw GradeTooHighException();
	if (grade > kMinGrade)
		throw GradeTooLowException();
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Bureaucrat: grade too high";
}
const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Bureaucrat: grade too low";
}

std::ostream & operator<<(std::ostream & os, const Bureaucrat & bureaucrat)
{
	os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return os;
}