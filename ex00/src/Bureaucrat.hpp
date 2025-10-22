#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>

// カラーコードの定義
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

class Bureaucrat
{
public:
	Bureaucrat();
	Bureaucrat(const std::string name, int grade);
	Bureaucrat(const Bureaucrat & src);
	const Bureaucrat & operator=(const Bureaucrat & src);
	~Bureaucrat();

	std::string	getName() const;
	int			getGrade() const;
	void		setGrade(int grade);

	void		incrementGrade();
	void		decrementGrade();

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
	
private:
	const std::string	name_;
	int			grade_;
	static const int kMaxGrade = 1;
	static const int kMinGrade = 150;

	void checkGrade(int grade) const;
};
std::ostream & operator<<(std::ostream & os, const Bureaucrat & bureaucrat);

#endif // BUREAUCRAT_HPP