#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"
#include <string>

class PresidentialPardonForm : public AForm {
public:
    explicit PresidentialPardonForm(const std::string& target);
    virtual ~PresidentialPardonForm();
    PresidentialPardonForm(const PresidentialPardonForm& o);
    PresidentialPardonForm& operator=(const PresidentialPardonForm& o);

protected:
    virtual void doExecute() const;

private:
    std::string target_;
};

#endif

