#include <iostream>
#include <stdexcept>

int main() {
    try {
        int denominator = 0;
        if (denominator == 0) {
            throw std::runtime_error("Division by zero error");  // 例外を投げる
        }
        int result = 10 / denominator;
        std::cout << "Result: " << result << std::endl;
    }
	catch (const std::runtime_error& e) {
        std::cerr << "Caught runtime_error: " << e.what() << std::endl;  // 例外を捕捉して処理する
    }
	catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
	catch (...) {
        std::cerr << "Caught unknown exception" << std::endl;
    }

    return 0;
}