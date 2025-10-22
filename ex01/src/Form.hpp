#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>

class Bureaucrat; // 前方宣言（循環依存を避ける）

class Form {
public:
	Form();
	Form(const std::string& name, int gradeToSign, int gradeToExec);
	Form(const Form& other);
	Form& operator=(const Form& other);
	~Form();

	const std::string& getName() const;
	bool			isSigned() const;
	int				getGradeToSign() const;
	int				getGradeToExec() const;

	void			beSigned(const Bureaucrat& b);

	class GradeTooHighException : public std::exception 
	{
	public: virtual const char* what() const throw();
	};
	class GradeTooLowException : public std::exception 
	{
	public: virtual const char* what() const throw();
	};

private:
	const std::string name_;	 // 不変
	bool			 signed_;   // 生成時は false
	const int		 gradeToSign_; // 不変
	const int		 gradeToExec_; // 不変

	void checkGrade(int grade) const; // [1,150] 内チェック
};

std::ostream& operator<<(std::ostream& os, const Form& f);

#endif // FORM_HPP
