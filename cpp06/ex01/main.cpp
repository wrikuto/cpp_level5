#include <iostream>
#include "Data.hpp"
#include "Serializer.hpp"

int main()
{
    Data data;
    data.value = 42;

    uintptr_t raw = Serializer::serialize(&data);
    Data* deserialized = Serializer::deserialize(raw);

    if (deserialized == &data)
        std::cout << "Serialization and deserialization successful!: " << data.value << std::endl;
    else
        std::cout << "Serialization and deserialization failed!" << std::endl;

    return 0;
}