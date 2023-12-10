#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <stdexcept>

struct Coordinate // Struct for a 2-integer coordinate. Also provides easy comparison.
{
    Coordinate() : coord{0, 0} {}

    Coordinate(int x, int y) : coord{x, y} {}

    int& operator[](int i)
    {
        if (i < 0 || i >= 2) throw std::out_of_range("Index out of range");
        return coord[i];
    }

    int operator[](int i) const
    {
        if (i < 0 || i >= 2) throw std::out_of_range("Index out of range");
        return coord[i];
    }

    bool operator==(const Coordinate& other) const
    {
        return coord[0] == other.coord[0] && coord[1] == other.coord[1];
    }

    bool operator!=(const Coordinate& other) const
    {
        return !(*this == other);
    }

    void setCoord(int x, int y)
    {
        coord[0] = x;
        coord[1] = y;
    }

    int coord[2];
    
};

#endif