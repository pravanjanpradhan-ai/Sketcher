#include "pch.h"
#include "Shape.h"

Shape::Shape(const std::string& n) : name(n) {}
Shape::~Shape() {}

std::string Shape::getName() const {
    return name;
}

