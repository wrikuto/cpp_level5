#include <iostream>
#include <cstdlib>
#include <ctime>

class Base
{
public:
	virtual ~Base() {}
};

class A : public Base {};
class B : public Base {};
class C : public Base {};

Base* generate()
{
	int random_value = std::rand() % 3;
	if (random_value == 0)
		return new A();
	else if (random_value == 1)
		return new B();
	else if (random_value == 2)
		return new C();
	
	return (nullptr);
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	}
	catch (std::bad_cast&) {}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
	}
	catch (std::bad_cast&) {}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
	}
	catch (std::bad_cast&) {}
}


int     main( void )
{
    Base*   a = generate();
    Base*   b = generate();
    Base*   c = generate();
    Base*   d = generate();

    std::cout << "a*: "; identify( a );
    std::cout << "a&: "; identify( *a ); std::cout << std::endl;

    std::cout << "b*: "; identify( b );
    std::cout << "b&: "; identify( *b ); std::cout << std::endl;

    std::cout << "c*: "; identify( c );
    std::cout << "c&: "; identify( *c ); std::cout << std::endl;

    std::cout << "d*: "; identify( d );
    std::cout << "d&: "; identify( *d ); std::cout << std::endl;

    delete a;
    delete b;
    delete c;
    delete d;

    return (0);
}