

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

template<typename T>
class Array
{
private:
	T* _elements;
	unsigned int _len;

public:
	Array() : _elements(nullptr), _len(0) {}
	Array(unsigned int n) : _elements(new T[n]()), _len(n) {}
	Array(const Array& other) : _elements(nullptr), _len(0)
	{
		*this = other;
	}

	Array& operator=(const Array& other)
	{
		if (this != &other)
		{
			delete[] _elements;
			_len = other._len;
			if (_len > 0)
			{
				_elements = new T[_len];
				for (unsigned int i = 0; i < _len; i++)
					_elements[i] = other._elements[i];
			}
			else
				_elements = nullptr;
		}
		return (*this);
	}

	~Array()
	{
		delete[] _elements;
	}

	T& operator[](unsigned int index)
	{
		if (index >= _len)
			throw std::out_of_range("Index out of range");
		return (_elements[index]);
	}

	const T& operator[](unsigned int index) const
	{
		if (index >= _len)
			throw std::out_of_range("Index out of range");
		return (_elements[index]);
	}

	unsigned int size() const
	{
		return (_len);
	}
};

#endif
