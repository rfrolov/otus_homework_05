#pragma once

#include "IPrimitive.h"

struct Dot : public IPrimitive {
    Dot(int x, int y) {}

    serialised_t get_data() override {return "Dot\n"; }

    type get_type() override { return type::dot; };
};
