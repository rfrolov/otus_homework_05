#pragma once

#include "IPrimitive.h"
#include <array>

/// Треугольник.
struct Triangle : public IPrimitive {
    using coordinates_t = std::array<Coordinates, 3>;

    /**
     * Конструктор.
     * @param coordinates Координаты вершин треугольника.
     */
    explicit Triangle(const coordinates_t &coordinates) {
        std::copy(coordinates.cbegin(), coordinates.cend(), coordinates_.begin());
    }

    Triangle() = default;

    /**
     * Выдает сериализованные данные.
     * @return Сериализованные данные.
     */
    serialised_t get_data() override {
        serialised_t data;
        data.clear();
        data.emplace_back(static_cast<int>(get_type()));
        for (auto i = 0; i < 3; ++i) {
            data.emplace_back(coordinates_[i].x);
            data.emplace_back(coordinates_[i].y);
        }
        return data;
    }

    /**
     * Заполняет внутренние параметры из сериализованных данных.
     * @param data Сериализованные данные.
     * @return true - данные корректны, false - данные некорректны.
     */
    bool set_data(const serialised_t &data) override {
        auto it = data.cbegin();
        if (data.size() != 7 &&
            *it != static_cast<int>(get_type())) {
            return false;
        }

        for (auto i = 0; i < 3; ++i) {
            coordinates_[i].x = *++it;
            coordinates_[i].y = *++it;
        }
        return true;
    }

    /**
     * Выдает тип примитива.
     * @return Тип примитива.
     */
    type get_type() override { return type::triangle; };

private:
    coordinates_t coordinates_{};
};
