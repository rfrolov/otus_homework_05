#pragma once

#include "DocumentModel.h"
#include "../utils/utils.h"

/**
 * Представление документа.
 */
struct DocumentView {

    /**
     * Перерисовывает документ.
     * @param model Ссылка на модель.
     */
    void redraw(DocumentModel &model) {
        auto vect = model.get_primitives();

        if(vect.size() == 0) {
            std::cout << "Clean" << std::endl;
        } else {
            for (const auto &it : vect) {
                IPrimitive::serialised_t data = it->get_data();
                std::cout << data;
            }
        }
    }
};
