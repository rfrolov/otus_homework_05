#pragma once

#include <iostream>
#include "../DocumentModel/DocumentModel.h"

struct DocumentView {
    void redraw(DocumentModel &model) {
        auto map = model.get_primitives();
        for(const auto &it : map) {
            std::cout << it.second->get_data();
        }
    }
};
