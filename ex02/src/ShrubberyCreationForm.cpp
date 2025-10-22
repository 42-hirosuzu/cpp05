// ShrubberyCreationForm.cpp
#include "ShrubberyCreationForm.hpp"
#include <fstream>

static const int kSign = 145;
static const int kExec = 137;

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", kSign, kExec), target_(target) {}
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& o)
    : AForm(o), target_(o.target_) {}
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& o) {
    if (this != &o) { this->target_ = o.target_; }
    return *this;
}
ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::doExecute() const {
    std::ofstream ofs((target_ + "_shrubbery").c_str());
    if (!ofs) return; // 課題は失敗時の例外は要求していないので静かに失敗可
    ofs <<
"      /\\\n"
"     /\\*\\\n"
"    /\\O*\\\n"
"   /*/\\/\\\\\n"
"  /\\O/*/\\*\\\n"
" /\\* /\\ O/\\\n"
"/\\ O /\\* /\\\n"
"      ||\n"
"      ||\n";
}

