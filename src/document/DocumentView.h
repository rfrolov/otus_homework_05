#pragma once

#include "DocumentModel.h"
#include "../utils/utils.h"

/// Представление документа.
struct DocumentView {
    explicit DocumentView(std::shared_ptr<DocumentModel> model) : model_{model} {
    }

    /// Перерисовывает документ.
    void redraw() {
        auto vect = model_.lock()->get_primitives();

        if(vect.size() == 0) {
            std::cout << "Clean" << std::endl;
        } else {
            for (const auto &it : vect) {
                IPrimitive::serialised_t data = it->get_data();
                std::cout << data;
            }
        }
    }

private:
    std::weak_ptr<DocumentModel> model_{};
};
