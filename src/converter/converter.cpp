#include "../primitives/IPrimitive.h"
#include "../primitives/Dot.h"
#include "../primitives/Line.h"
#include "../primitives/Triangle.h"

#include "converter.h"

bool Importer::doConvert(result_t &result) {
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
                result.emplace_back(new Dot(x, y));
                break;
            }

            case IPrimitive::type::line : {
                int x1, y1, x2, y2;
                fs_ >> x1 >> y1 >> x2 >> y2;
                result.emplace_back(new Line(x1, y1, x2, y2));
                break;
            }

            case IPrimitive::type::triangle : {
                int x1, y1, x2, y2, x3, y3;
                fs_ >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
                result.emplace_back(new Triangle(x1, y1, x2, y2, x3, y3));
                break;
            }

            default: {
                return false;
            }
        }
    }
    return true;
}

bool Exporter::doConvert(data_t &data) {
    if (!fs_.is_open()) { return false; }

    fs_ << data.size() << std::endl;
    for (const auto &it : data) {
        auto primitive_type = it->get_type();
        switch (primitive_type) {
            case IPrimitive::type::dot : {
                auto *dot = dynamic_cast<Dot *>(it);
                auto serialised_data = dot->get_data();
                fs_ << serialised_data;
                break;
            }

            case IPrimitive::type::line : {
                auto *dot = dynamic_cast<Line *>(it);
                auto serialised_data = dot->get_data();
                fs_ << serialised_data;
                break;
            }

            case IPrimitive::type::triangle : {
                auto *dot = dynamic_cast<Triangle *>(it);
                auto serialised_data = dot->get_data();
                fs_ << serialised_data;
                break;
            }

            default: {
                return false;
            }
        }
    }

    return true;
}