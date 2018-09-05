#pragma once

#include <memory>
#include "../utils/utils.h"

/// Представление документа.
struct DocumentView {

    /// Отрисовывает примитив.
    void redraw(IPrimitive::serialised_t data) {
        std::cout << data;
    }
};
