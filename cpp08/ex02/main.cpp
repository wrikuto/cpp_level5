#include <iostream>
#include "MutantStack.hpp"

int main() {
    std::cout << "--- ORIGINAL TEST ---\n";
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << mstack.top() << std::endl;

    mstack.pop();

    std::cout << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }

    std::stack<int> s(mstack);
    
    std::cout << "\nSTRING TEST\n";
    MutantStack<std::string> strStack;
    strStack.push("Hello");
    strStack.push("World");
    
    std::cout << "Top: " << strStack.top() << std::endl;
    for (MutantStack<std::string>::iterator it = strStack.begin(); it != strStack.end(); ++it) {
        std::cout << *it << std::endl;
    }

	std::cout << "\nLIST TEST";
	MutantStack<int> listStack;
	listStack.push(10);
	listStack.push(20);
	listStack.push(30);

	std::cout << "\nList contents:\n";
	for (MutantStack<int>::iterator it = listStack.begin(); it != listStack.end(); ++it) {
		std::cout << *it << std::endl;
	}

	std::cout << "Popping elements:\n";
	while (!listStack.empty()) {
		std::cout << listStack.top() << std::endl;
		listStack.pop();
	}

    return 0;
}