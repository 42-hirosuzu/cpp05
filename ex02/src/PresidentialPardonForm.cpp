#include "PresidentialPardonForm.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
  : AForm("PresidentialPardonForm", 25, 5), target_(target) {}
PresidentialPardonForm::~PresidentialPardonForm() {}
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& o)
  : AForm(o), target_(o.target_) {}
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& o) {
    if (this != &o) { AForm::operator=(o); target_ = o.target_; }
    return *this;
}

void PresidentialPardonForm::doExecute() const {
    std::cout << target_ << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

