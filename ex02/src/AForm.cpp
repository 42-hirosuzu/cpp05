#include "AForm.hpp"
#include "Bureaucrat.hpp"

void AForm::checkGradeRange(int g) const {
    if (g < 1)  throw GradeTooHighException();
    if (g > 150) throw GradeTooLowException();
}

// OCF
AForm::AForm(const std::string& name, int gs, int ge)
    : name_(name), signed_(false), gradeToSign_(gs), gradeToExec_(ge)
{
    checkGradeRange(gradeToSign_);
    checkGradeRange(gradeToExec_);
}
AForm::AForm(const AForm& o)
    : name_(o.name_), signed_(o.signed_), gradeToSign_(o.gradeToSign_), gradeToExec_(o.gradeToExec_) {}
AForm& AForm::operator=(const AForm& o) {
    if (this != &o) { this->signed_ = o.signed_; }
    return *this;
}
AForm::~AForm() {}

const std::string& AForm::getName() const        { return name_; }
bool               AForm::isSigned() const       { return signed_; }
int                AForm::getGradeToSign() const { return gradeToSign_; }
int                AForm::getGradeToExec() const { return gradeToExec_; }

void AForm::beSigned(const Bureaucrat& b) {
    // 1 が最上位（数値が小さいほど強い）
    if (b.getGrade() <= gradeToSign_) signed_ = true;
    else throw GradeTooLowException();
}

void AForm::execute(const Bureaucrat& executor) const {
    if (!signed_) throw NotSignedException();
    if (executor.getGrade() > gradeToExec_) throw GradeTooLowException();
    doExecute(); // 実処理は派生クラスへ
}

// 例外
const char* AForm::GradeTooHighException::what() const throw() { return "AForm: grade too high"; }
const char* AForm::GradeTooLowException::what()  const throw() { return "AForm: grade too low"; }
const char* AForm::NotSignedException::what()    const throw() { return "AForm: not signed";    }

// 出力
std::ostream& operator<<(std::ostream& os, const AForm& f) {
    os << "Form \"" << f.getName() << "\""
       << " [signed: " << (f.isSigned() ? "true" : "false")
       << ", sign grade: " << f.getGradeToSign()
       << ", exec grade: " << f.getGradeToExec()
       << "]";
    return os;
}

