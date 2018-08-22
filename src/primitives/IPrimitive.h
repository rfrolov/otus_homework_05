#pragma once

#include <string>

struct IPrimitive {
    using serialised_t = std::string;   ///< Тип сериализованых данных примитива.

    // TODO: Написать коментарий.
    enum class type {
        none,
        dot,
        line,
        triangle,
    };

    /**
     * Выдает сериализованные данные примитива.
     * @return Сериализованные данные примитива.
     */
    virtual serialised_t get_data() = 0;

    /**
     * Выдает тип примитива.
     * @return
     */
    virtual type get_type() = 0;
};

