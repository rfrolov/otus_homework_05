#pragma once

#include "IPrimitive.h"

struct Triangle : public IPrimitive {
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3) {}

    serialised_t get_data() override { return "Triangle\n"; }

    type get_type() override { return type::triangle; };
};
