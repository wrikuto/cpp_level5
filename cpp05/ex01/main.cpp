#include "Bureaucrat.hpp"
#include "Form.hpp"



#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
    try {
        Bureaucrat a("a", 30);
        Bureaucrat b("b", 150);

        a.incrementGrade();
        std::cout << a << std::endl;
        b.decrementGrade();
        std::cout << b << std::endl;
        b.incrementGrade();
        std::cout << b << std::endl;

        std::cout << std::endl;
        
        // 有効なフォーム
        Form f("important form", 50, 20);
        Form f1("more important form", 150, 20);
        
        a.signForm(f);
        b.signForm(f1);
        std::cout << f << std::endl;
        b.signForm(f);
        std::cout << f << std::endl;
        
        // 無効なフォーム
        try {
            std::cout << "無効なフォーム." << std::endl;
            Form fBad("bad form", 160, 120);
        } catch (const std::exception &e) {
            std::cout << "error: " << e.what() << std::endl;
        }
    } catch (const std::exception &e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }

    return (0);
}