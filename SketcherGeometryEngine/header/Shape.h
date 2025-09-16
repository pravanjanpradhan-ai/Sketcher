#pragma once
#include "framework.h"
#include <string>
#include <utility>
#include <vector>
#include "Point.h"

// Abstract Base Class (Abstraction)
class Shape
{
protected:
    std::string name; // Encapsulation (private/protected data)

public:
    Shape(const std::string &n);
    virtual ~Shape();

    // Common method
    std::string getName() const;
    virtual std::vector<Point> getPoints() const = 0;
};