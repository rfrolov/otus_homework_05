#include "../primitives/IPrimitive.h"
#include "../utils/utils.h"
#include "ExporterOne.h"


bool ExporterOne::do_convert(data_t &data) {
    if (!fs_.is_open()) { return false; }

    fs_ << data.size() << std::endl;
    for (auto &serialised_data : data) {
        fs_ << serialised_data;
    }

    return true;
}