#include "../primitives/Dot.h"
#include "../primitives/Line.h"
#include "../primitives/Triangle.h"
#include "../utils/utils.h"
#include "ImporterOne.h"

bool ImporterOne::do_convert(result_t &result) {
    uint32_t         n{0};
    int              type{0};
    IPrimitive::type primitive_type{IPrimitive::type::none};

    if (!fs_.is_open()) { return false; }

    fs_ >> n;
    for (auto i = 0; i < n; ++i) {
        fs_ >> type;
        primitive_type = static_cast<IPrimitive::type>(type);

        switch (primitive_type) {
            case IPrimitive::type::dot : {
                int x, y;
                fs_ >> x >> y;
                auto dot            = new Dot();
                auto serialisedData = IPrimitive::serialised_t{type, x, y};
                dot->set_data(serialisedData);
                result.emplace_back(dot);
                break;
            }

            case IPrimitive::type::line : {
                int x1, y1, x2, y2;
                fs_ >> x1 >> y1 >> x2 >> y2;
                auto line           = new Line();
                auto serialisedData = IPrimitive::serialised_t{type, x1, y1, x2, y2};
                line->set_data(serialisedData);
                result.emplace_back(line);
                break;
            }

            case IPrimitive::type::triangle : {
                int x1, y1, x2, y2, x3, y3;
                fs_ >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
                auto triangle       = new Triangle();
                auto serialisedData = IPrimitive::serialised_t{type, x1, y1, x2, y2, x3, y3};
                triangle->set_data(serialisedData);
                result.emplace_back(triangle);
                break;
            }

            default: {
                return false;
            }
        }
    }
    return true;
}