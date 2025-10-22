#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

static void header(const char* title) {
    std::cout << "\n== " << title << " ==\n";
}

int main() {
    // 1) 生成・getter・表示
    header("construct / getters / operator<<");
    {
        Bureaucrat a("Alice", 3);
        std::cout << "[create] " << a << "\n";                    // 書式確認
        std::cout << "  current grade = " << a.getGrade() << "\n"; // いま何点か
    }

    // 2) 増減の基本（3 -> 2 -> 3）
    header("increment / decrement (normal)");
    {
        Bureaucrat b("Bob", 3);
        std::cout << "[start] grade = " << b.getGrade() << "\n";
        b.incrementGrade();   // 3 -> 2
        std::cout << "[increment] grade = " << b.getGrade() << "\n";
        b.decrementGrade();   // 2 -> 3
        std::cout << "[decrement] grade = " << b.getGrade() << "\n";
    }

    // 3) 境界での例外：1でincrement、150でdecrement（失敗後の現在グレードも表示）
    header("boundary errors (1 increment / 150 decrement)");
    {
        Bureaucrat top("Top", 1);
        std::cout << "[start:Top] grade = " << top.getGrade() << "\n";
        try {
            top.incrementGrade(); // 例外
            std::cout << "[increment] grade = " << top.getGrade() << "\n";
        } catch (const std::exception& e) {
            std::cout << "[increment] exception: " << e.what()
                      << " | current grade = " << top.getGrade() << "\n";
        }

        Bureaucrat low("Low", 150);
        std::cout << "[start:Low] grade = " << low.getGrade() << "\n";
        try {
            low.decrementGrade(); // 例外
            std::cout << "[decrement] grade = " << low.getGrade() << "\n";
        } catch (const std::exception& e) {
            std::cout << "[decrement] exception: " << e.what()
                      << " | current grade = " << low.getGrade() << "\n";
        }
    }

    // 4) コンストラクタの範囲外例外（0 と 151）
    header("ctor out-of-range errors (0 / 151)");
    {
        try {
            Bureaucrat badHigh("BadHigh", 0); // 例外
            std::cout << "[ctor] BadHigh created (unexpected)\n";
        } catch (const std::exception& e) {
            std::cout << "[ctor] grade=0 -> exception: " << e.what() << "\n";
        }

        try {
            Bureaucrat badLow("BadLow", 151); // 例外
            std::cout << "[ctor] BadLow created (unexpected)\n";
        } catch (const std::exception& e) {
            std::cout << "[ctor] grade=151 -> exception: " << e.what() << "\n";
        }
    }
    // 1) 署名→実行（Shrubbery：成功コース）
    header("Shrubbery: sign & execute");
    {
        Bureaucrat chief("Chief", 1);
        ShrubberyCreationForm sh("home");
        std::cout << sh << std::endl;
        chief.signForm(sh);
        chief.executeForm(sh);     // home_shrubbery が作成される
    }

    // 2) Robotomy：署名→実行（50% 成功/失敗）
    header("Robotomy: sign & execute (50%)");
    {
        Bureaucrat exec("Exec", 1);
        RobotomyRequestForm rb("Bender");
        exec.signForm(rb);
        exec.executeForm(rb);
    }

    // 3) Pardon：未署名で実行→失敗 → 署名して再実行→成功
    header("Pardon: execute fails when unsigned, then works");
    {
        Bureaucrat prez("Prez", 1);
        PresidentialPardonForm pd("Arthur Dent");
        prez.executeForm(pd);  // not signed
        prez.signForm(pd);
        prez.executeForm(pd);
    }

    // 4) 低グレードでは実行失敗
    header("Exec grade too low");
    {
        Bureaucrat low("Low", 150);
        ShrubberyCreationForm sh("tiny");
        low.signForm(sh);      // 署名も失敗
        low.executeForm(sh);   // 実行も当然失敗
    }
    return 0;
}