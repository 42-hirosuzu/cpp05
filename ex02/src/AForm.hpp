#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>

class Bureaucrat; // 前方宣言（循環依存を避ける）

class AForm {
public:
    AForm(const std::string& name, int gradeToSign, int gradeToExec);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);
    virtual ~AForm();

    const std::string& getName() const;
    bool               isSigned() const;
    int                getGradeToSign() const;
    int                getGradeToExec() const;

    void               beSigned(const Bureaucrat& b);
    void               execute(Bureaucrat const& executor) const; // 共通チェック→doExecute()

    // 例外
    class GradeTooHighException : public std::exception {
    public: virtual const char* what() const throw();
    };
    class GradeTooLowException : public std::exception {
    public: virtual const char* what() const throw();
    };
    class NotSignedException : public std::exception {
    public: virtual const char* what() const throw();
    };

private:
    const std::string name_;        // 不変
    bool              signed_;      // 生成時 false
    const int         gradeToSign_; // 不変
    const int         gradeToExec_; // 不変

    void checkGradeRange(int grade) const; // [1,150] 内か
protected:
    // 派生クラスが実処理を実装
    virtual void doExecute() const = 0;
};

std::ostream& operator<<(std::ostream& os, const AForm& f);

#endif // AFORM_HPP

