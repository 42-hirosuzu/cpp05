// RobotomyRequestForm.cpp
#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

static const int kSign = 72;
static const int kExec = 45;

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", kSign, kExec), target_(target) {}
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& o)
    : AForm(o), target_(o.target_) {}
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& o) {
    if (this != &o) { this->target_ = o.target_; }
    return *this;
}
RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::doExecute() const {
    std::cout << "* Bzzzz... DRRRRrrrr... *" << std::endl; // ドリル音
    // C++98: rand() で 50%
    std::srand(static_cast<unsigned int>(std::time(0)) ^ static_cast<unsigned int>(reinterpret_cast<std::size_t>(this)));
    if (std::rand() % 2)
        std::cout << target_ << " has been robotomized successfully." << std::endl;
    else
        std::cout << "Robotomy failed on " << target_ << "." << std::endl;
}

