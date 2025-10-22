// ShrubberyCreationForm.hpp
#ifndef SHRUBBERY_CREATION_FORM_HPP
#define SHRUBBERY_CREATION_FORM_HPP

#include "AForm.hpp"
#include <string>

class ShrubberyCreationForm : public AForm {
public:
    explicit ShrubberyCreationForm(const std::string& target);
    ShrubberyCreationForm(const ShrubberyCreationForm& );
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& );
    ~ShrubberyCreationForm();

private:
    std::string target_;
protected:
    virtual void doExecute() const;
};

#endif

