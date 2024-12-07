#pragma once
#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vector)
{
    size_t size = vector.size();

    if (size == 0)
    {
        return os;
    }
    else if (size <= 6)
    {
        os << "[" << vector[0];
        for (size_t i{1}; i < size; i++)
        {
            os << ", " << vector[i];
        }
        os << "]";

        return os;
    }
    else
    {
        os << "[" << vector[0] << ", " << vector[1] << ", " << vector[2] << ", ..., "
           << vector[size - 3] << ", " << vector[size - 2] << ", " << vector[size - 1] << "]";
        return os;
    }
}
