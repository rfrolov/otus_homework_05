#pragma once

#include "IPrimitive.h"

struct Line : public IPrimitive {
    Line(int x1, int y1, int x2, int y2) {}

    serialised_t get_data() override { return "Line\n"; }

    type get_type() override { return type::line; };
};