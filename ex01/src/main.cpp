#include "Bureaucrat.hpp"
#include "Form.hpp"   
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

     // =========================
    // ex01: Form の基本テスト
    // =========================

    // A) 情報表示（operator<<）
    header("ex01: Form info / operator<<");
    {
        Form leave("LeaveRequest", 50, 20);
        std::cout << "[form] " << leave << "\n";
    }

    // B) Bureaucrat::signForm 経由で署名（成功例）
    header("ex01: signForm (success)");
    {
        Form leave("LeaveRequest", 50, 20);  // 署名に必要=50
        Bureaucrat alice("Alice", 45);       // 45 は 50 より“高位”→署名可
        std::cout << "[before] " << leave << "\n";
        alice.signForm(leave);               // "<bureaucrat> signed <form>"
        std::cout << "[after ] " << leave << "\n";
    }

    // C) Bureaucrat::signForm 経由で署名（失敗例）
    header("ex01: signForm (failure)");
    {
        Form report("WeeklyReport", 60, 40); // 署名に必要=60
        Bureaucrat bob("Bob", 100);          // 100 は“低位”→署名不可
        std::cout << "[before] " << report << "\n";
        bob.signForm(report);                 // "<bureaucrat> couldn’t sign <form> because <reason>."
        std::cout << "[after ] " << report << "\n";
    }

    // D) 直接 beSigned を叩いて例外経路を確認
    header("ex01: direct beSigned (exception path)");
    {
        Form critical("Critical", 25, 5);
        Bureaucrat intern("Intern", 140);
        try {
            critical.beSigned(intern);       // 140 は 25 に届かない → 例外
            std::cout << "[beSigned] success -> " << critical << "\n";
        } catch (const std::exception& e) {
            std::cout << "[beSigned] exception: " << e.what()
                      << " | signed=" << (critical.isSigned() ? "true" : "false") << "\n";
        }
    }

    // E) Form のコンストラクタ入力チェック（範囲外で例外）
    header("ex01: Form ctor out-of-range");
    {
        try {
            Form bad1("Bad1", 0, 10);  // 署名等級=0 は高すぎ（1未満）→例外
            std::cout << "unexpected: " << bad1 << "\n";
        } catch (const std::exception& e) {
            std::cout << "[ctor] sign=0 -> exception: " << e.what() << "\n";
        }
        try {
            Form bad2("Bad2", 10, 151); // 実行等級=151 は低すぎ（150超）→例外
            std::cout << "unexpected: " << bad2 << "\n";
        } catch (const std::exception& e) {
            std::cout << "[ctor] exec=151 -> exception: " << e.what() << "\n";
        }
    }
    return 0;
}