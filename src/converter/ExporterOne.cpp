#include "../primitives/Dot.h"
#include "../primitives/Line.h"
#include "../primitives/Triangle.h"
#include "../utils/utils.h"
#include "ExporterOne.h"


bool ExporterOne::do_convert(data_t &data) {
    if (!fs_.is_open()) { return false; }

    fs_ << data.size() << std::endl;
    for (const auto &it : data) {
        auto primitive_type = it->get_type();
        switch (primitive_type) {
            case IPrimitive::type::dot : {
                auto *dot            = dynamic_cast<Dot *>(it);
                auto serialised_data = dot->get_data();
                fs_ << serialised_data;
                break;
            }

            case IPrimitive::type::line : {
                auto *dot            = dynamic_cast<Line *>(it);
                auto serialised_data = dot->get_data();
                fs_ << serialised_data;
                break;
            }

            case IPrimitive::type::triangle : {
                auto *dot            = dynamic_cast<Triangle *>(it);
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