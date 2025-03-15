#include "Span.hpp"

int main()
{
    Span sp = Span(5);

    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
    std::cout << "Longest Span: " << sp.longestSpan() << std::endl;

    Span largeSpan(10000);
    
    std::vector<int> numbers(10000);
    for (int i = 0; i < 10000; i++) {
        numbers[i] = i;
    }
    
    largeSpan.addNumber(numbers.begin(), numbers.end());
    
    std::cout << "Large Span - Shortest: " << largeSpan.shortestSpan() << std::endl;
    std::cout << "Large Span - Longest: " << largeSpan.longestSpan() << std::endl;

    return (0);
}
