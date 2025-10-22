#include "Form.hpp"
#include "Bureaucrat.hpp" // beSignedでBureaucrat::getGrade()を使う

// --- ヘルパ ---
void Form::checkGrade(int grade) const {
    if (grade < 1)   throw GradeTooHighException();
    if (grade > 150) throw GradeTooLowException();
}

// --- OCF ---
Form::Form(const std::string& name, int gradeToSign, int gradeToExec)
    : name_(name), signed_(false), gradeToSign_(gradeToSign), gradeToExec_(gradeToExec)
{
    checkGrade(gradeToSign_);
    checkGrade(gradeToExec_);
}
Form::Form(const Form& other)
    : name_(other.name_),
      signed_(other.signed_),
      gradeToSign_(other.gradeToSign_),
      gradeToExec_(other.gradeToExec_)
{}

Form& Form::operator=(const Form& other) 
{
    if (this != &other) {
        // constメンバはコピー不可なので、署名フラグのみ同期
        this->signed_ = other.signed_;
    }
    return *this;
}
Form::~Form() {}

// --- ゲッター ---
const std::string& Form::getName() const        { return name_; }
bool               Form::isSigned() const       { return signed_; }
int                Form::getGradeToSign() const { return gradeToSign_; }
int                Form::getGradeToExec() const { return gradeToExec_; }

// --- 動作 ---
void Form::beSigned(const Bureaucrat& b) {
    // 官僚の等級が「必要署名等級以下（より高位）」なら署名可
    if (b.getGrade() <= gradeToSign_)
	{
        signed_ = true;
    }
	else
	{
        throw GradeTooLowException();
    }
}

// --- 例外 ---
const char* Form::GradeTooHighException::what() const throw() {
    return "Form: grade too high";
}
const char* Form::GradeTooLowException::what() const throw() {
    return "Form: grade too low";
}

// --- 出力演算子 ---
std::ostream& operator<<(std::ostream& os, const Form& f) {
    os << "Form \"" << f.getName() << "\""
       << " [signed: " << (f.isSigned() ? "true" : "false")
       << ", sign grade: " << f.getGradeToSign()
       << ", exec grade: " << f.getGradeToExec()
       << "]";
    return os;
}
