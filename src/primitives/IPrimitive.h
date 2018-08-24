#pragma once

#include <vector>

/// Интерфейс примитива.
struct IPrimitive {
    using serialised_t = std::vector<int>;

    /// Тип примитива.
    enum class type {
        none,
        dot,
        line,
        triangle,
    };

    /**
     * Выдает сериализованные данные.
     * @return Сериализованные данные.
     */
    virtual serialised_t get_data() = 0;

    /**
     * Заполняет внутренние параметры из сериализованных данных.
     * @param data Сериализованные данные.
     * @return true - данные корректны, false - данные некорректны.
     */
    virtual bool set_data(const serialised_t &data) = 0;

    /**
     * Выдает тип примитива.
     * @return Тип примитива.
     */
    virtual type get_type() = 0;
};

/// Координаты.
struct Coordinates {
    Coordinates(int x, int y) : x{x}, y{y} {}
    Coordinates() = default;

    int x = 0;
    int y = 0;
};

