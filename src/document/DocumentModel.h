#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include "../primitives/IPrimitive.h"
#include "../converter/converter.h"
#include "../primitives/Dot.h"
#include "../primitives/Line.h"
#include "../primitives/Triangle.h"
#include "DocumentView.h"
#include <cassert>

/// Модель документа.
struct DocumentModel {
    using primitive_t  = std::shared_ptr<IPrimitive>;
    using handler_t    = uint64_t;
    using serialised_t = IPrimitive::serialised_t;
    using map_t        = std::map<handler_t, primitive_t>;
    using primitives_t = std::vector<primitive_t>;

    /**
     * Конструктор.
     * @param view Указатель на класс представления.
     */
    explicit DocumentModel(std::shared_ptr<DocumentView> view) : view_{std::move(view)} {
        assert(view_ != nullptr);
    }

    /**
     * Добавляет примитив.
     * @param data Сериализованые данные примитива.
     * @return Идентификатор примитива. 0 - примитив не создан.
     */
    handler_t add_primitive(IPrimitive::serialised_t data) {
        if (map_.size() >= max_primitives_) { return 0; }
        if (++handler_ == 0) { ++handler_; }

        primitive_t primitive{};
        auto        primitive_type = static_cast<IPrimitive::type>(data[0]);
        switch (primitive_type) {
            case IPrimitive::type::dot: {
                primitive = std::make_shared<Dot>();
                break;
            }

            case IPrimitive::type::line: {
                primitive = std::make_shared<Line>();
                break;
            }

            case IPrimitive::type::triangle: {
                primitive = std::make_shared<Triangle>();
                break;
            }

            default: {
                return 0;
            }
        }

        primitive->set_data(data);
        map_[handler_] = primitive;
        view_->redraw(data);
        return handler_;
    }

    /**
     * Изменяет примитив.
     * @param handler Идентификатор примитива.
     * @param serialised Сериализованные данные примитива.
     * @return true - выполнено, false - примитив не найден.
     */
    bool modify_primitive(handler_t handler, IPrimitive::serialised_t serialised) {
        auto it = map_.find(handler);
        if (it != map_.end()) {
            auto is_ok =  it->second->set_data(serialised);
            view_->redraw(serialised);
            return is_ok;
        }
        return false;
    }

    /**
    * Удаляет примитив.
    * @param handler Идентификатор удаляемого примитива.
    * @return true - удаление прошло успешно, false - примитив не найден.
    */
    bool delete_primitive(handler_t handler) {
        auto it = map_.find(handler);
        if (it != map_.end()) {
            map_.erase(it);
            redraw();
            return true;
        }
        return false;
    }

    /**
     * Экспортировать документ.
     * @param exporter Указатель на экспортер.
     * @return true - экспорт прошел удачно, false - экспорт не возможен.
     */
    bool export_document(std::shared_ptr<AExporter> exporter) {
        AExporter::data_t data{};

        for (const auto &it : map_) {
            data.emplace_back(it.second->get_data());
        }
        return exporter->do_convert(data);
    }

    /**
     * Импортировать документ.
     * @param importer Указатель на импортер.
     * @return true - ипорт прошел удачно, false - импорт не возможен.
     */
    bool import_document(std::shared_ptr<AImporter> importer) {
        AImporter::result_t result{};
        if (importer->do_convert(result)) {
            clear();
            for (const auto &it: result) {
                add_primitive(it);
            }
            return true;
        }
        return false;
    }

    /// Удаляет все примитивы.
    void clear() {
        map_.clear();
        redraw();
    }

    /// Перерисовать документ.
    void redraw() {
        for (const auto &it : map_) {
            view_->redraw(it.second->get_data());
        }
    }

private:
    static const auto             max_primitives_ = 1000;     ///< Максимальное количество примитивов в документе.
    handler_t                     handler_        = 0;        ///< Последный выданный хендлер.
    map_t                         map_{};                     ///< Мап указателей на созданные примитивы.
    std::shared_ptr<DocumentView> view_{};
};
