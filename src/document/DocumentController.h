#pragma once

#include <cassert>
#include "DocumentModel.h"
#include "../converter/ExporterOne.h"
#include "../converter/ExporterTwo.h"
#include "../converter/ImporterOne.h"
#include "../converter/ImporterTwo.h"

/// Контроллер документа.
struct DocumentController {
    using handler_t = DocumentModel::handler_t;
    using primitive_t = std::shared_ptr<IPrimitive>;

    /**
     * Конструктор.
     * @param model Указатель на модель.
     */
    explicit DocumentController(std::shared_ptr<DocumentModel> model) : model_{model} {
        assert(model_ != nullptr);
    };

    /**
     * Добавляет точку.
     * @param coordinates Координаты точки.
     * @return Идентификатор.
     */
    handler_t add_dot(const Coordinates &coordinates) {
        auto serialised_data = IPrimitive::serialised_t{static_cast<int>(IPrimitive::type::dot), coordinates.x, coordinates.y};
        auto id              = model_->add_primitive(serialised_data);
        return id;
    }

    /**
     * Добавляет линию.
     * @param coordinates Координаты концов линии.
     * @return Идентификатор.
     */
    handler_t add_line(const Coordinates coordinates[2]) {
        auto serialised_data = IPrimitive::serialised_t{static_cast<int>(IPrimitive::type::line),
                                                        coordinates[0].x, coordinates[0].y,
                                                        coordinates[1].x, coordinates[1].y};
        auto id              = model_->add_primitive(serialised_data);
        return id;
    }

    /**
     * Добавляет треугольник.
     * @param coordinates координаты вершин треугольника.
     * @return Идентификатор.
     */
    handler_t add_triangle(const Coordinates coordinates[3]) {
        auto serialised_data = IPrimitive::serialised_t{static_cast<int>(IPrimitive::type::triangle),
                                                        coordinates[0].x, coordinates[0].y,
                                                        coordinates[1].x, coordinates[1].y,
                                                        coordinates[2].x, coordinates[2].y};

        auto id = model_->add_primitive(serialised_data);
        return id;
    }

    /**
     * Изменяет линию.
     * @param handler Идентификатор примитива.
     * @param coordinates Новые координаты вершин треугольника.
     * @return true - Изменение прошло успешно, false - примитив не найден.
     */
    bool modify_line(handler_t handler, const Coordinates coordinates[2]) {
        auto serialised_data = IPrimitive::serialised_t{static_cast<int>(IPrimitive::type::line),
                                                        coordinates[0].x, coordinates[0].y,
                                                        coordinates[1].x, coordinates[1].y};
        return model_->modify_primitive(handler, serialised_data);
    }

    /**
     * Экспортирует документ в файл формата "One".
     * @param file_name Имя файла.
     * @return true - выполнено успешно, false - ошибка.
     */
    bool export_format_one(std::string file_name) {
        return model_->export_document(std::make_shared<ExporterOne>(file_name));
    }

    /**
     * Экспортирует документ в файл формата "Two".
     * @param file_name Имя файла.
     * @return true - выполнено успешно, false - ошибка.
     */
    bool export_format_two(std::string file_name) {
        return model_->export_document(std::make_shared<ExporterTwo>(file_name));
    }

    /**
     * Импортирует документ из файла формата "One".
     * @param file_name Имя файла.
     * @return true - выполнено успешно, false - ошибка.
     */
    bool import_format_one(std::string file_name) {
        return model_->import_document(std::make_shared<ImporterOne>(file_name));
    }

    /**
     * Импортирует документ из файла формата "Two".
     * @param file_name Имя файла.
     * @return true - выполнено успешно, false - ошибка.
     */
    bool import_format_two(std::string file_name) {
        return model_->import_document(std::make_shared<ImporterTwo>(file_name));
    }

    /**
     * Удаляет примитив.
     * @param handler Идентификатор удаляемого примитива.
     */
    void delete_primitive(handler_t handler) {
        model_->delete_primitive(handler);
    }

    /// Очистить документ.
    void clear() {
        model_->clear();
    }

    /// Перерисовывает документ.
    void redraw() {
        model_->redraw();
    }

private:
    std::shared_ptr<DocumentModel> model_{nullptr};
};

