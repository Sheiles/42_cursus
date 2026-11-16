#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>

template <typename T>
class Array
{
public:
	Array() : _size(0), _data(0)
	{
	}

	explicit Array(unsigned int size) : _size(size), _data(0)
	{
		if (_size != 0)
			_data = new T[_size]();
	}

	Array(const Array &other) : _size(0), _data(0)
	{
		if (other._size == 0)
			return;

		T *copy = new T[other._size]();
		try
		{
			for (unsigned int i = 0; i < other._size; ++i)
				copy[i] = other._data[i];
		}
		catch (...)
		{
			delete[] copy;
			throw;
		}
		_size = other._size;
		_data = copy;
	}

	~Array()
	{
		delete[] _data;
	}

	Array &operator=(const Array &other)
	{
		if (this != &other)
		{
			Array copy(other);
			swap(copy);
		}
		return *this;
	}

	T &operator[](unsigned int index)
	{
		if (index >= _size)
			throw std::out_of_range("Array index is out of bounds");
		return _data[index];
	}

	const T &operator[](unsigned int index) const
	{
		if (index >= _size)
			throw std::out_of_range("Array index is out of bounds");
		return _data[index];
	}

	unsigned int size() const
	{
		return _size;
	}

private:
	unsigned int _size;
	T *_data;

	void swap(Array &other)
	{
		unsigned int size = _size;
		T *data = _data;

		_size = other._size;
		_data = other._data;
		other._size = size;
		other._data = data;
	}
};

#endif
