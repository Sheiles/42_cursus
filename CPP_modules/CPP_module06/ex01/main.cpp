#include "Data.hpp"
#include "Serializer.hpp"

#include <iostream>

int main()
{
	Data data;
	uintptr_t raw;
	Data *restored;

	data.id = 42;
	data.name = "serialization check";
	raw = Serializer::serialize(&data);
	restored = Serializer::deserialize(raw);
	std::cout << "Original address: " << &data << std::endl;
	std::cout << "Serialized value: " << raw << std::endl;
	std::cout << "Restored address: " << restored << std::endl;
	if (restored != &data)
	{
		std::cerr << "Serialization round trip failed" << std::endl;
		return (1);
	}
	std::cout << "Round trip successful: " << restored->id << ", "
		<< restored->name << std::endl;
	return (0);
}
