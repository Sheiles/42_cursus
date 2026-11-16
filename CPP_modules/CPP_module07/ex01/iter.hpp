#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename T, typename Function>
void iter(T *array, const std::size_t length, Function function)
{
	for (std::size_t i = 0; i < length; ++i)
		function(array[i]);
}

#endif
