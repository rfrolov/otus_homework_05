#pragma once

#include "IPrimitive.h"

/**
 * Точка.
 */
struct Dot : public IPrimitive {

    /**
     * Конструктор.
     * @param coordinates Координаты точки.
     */
    explicit Dot(Coordinates coordinates) : coordinates_{coordinates} {}
    Dot() = default;

    /**
     * Выдает сериализованные данные.
     * @return Сериализованные данные.
     */
    serialised_t get_data() override {
        serialised_t data;
        data.clear();
        data.emplace_back(static_cast<int>(get_type()));
        data.emplace_back(coordinates_.x);
        data.emplace_back(coordinates_.y);
        return data;
    }

    /**
     * Заполняет внутренние параметры из сериализованных данных.
     * @param data Сериализованные данные.
     * @return true - данные корректны, false - данные некорректны.
     */
    bool set_data(const serialised_t &data) override {
        auto it = data.cbegin();
        if (data.size() != 3 &&
            *it != static_cast<int>(get_type())) {
            return false;
        }
        coordinates_.x = *++it;
        coordinates_.y = *++it;
        return true;
    }

    /**
     * Выдает тип примитива.
     * @return Тип примитива.
     */
    type get_type() override { return type::dot; };

private:
    Coordinates coordinates_{0, 0};
};
