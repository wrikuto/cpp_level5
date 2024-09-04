#include <iostream>

struct Data {
    int value;
};

uintptr_t serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}

int main()
{
    Data data;
    data.value = 42;

    uintptr_t raw = serialize(&data);
    Data* deserialized = deserialize(raw);

    if (deserialized == &data)
        std::cout << "Serialization and deserialization successful!: " << data.value << std::endl;
}
