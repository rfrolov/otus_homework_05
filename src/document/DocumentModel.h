#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include "../primitives/IPrimitive.h"
#include "../converter/converter.h"

/**
 * Модель документа.
 */
struct DocumentModel {
    using handler_t    = uint64_t;
    using serialised_t = IPrimitive::serialised_t;
    using map_t        = std::map<handler_t, IPrimitive *>;
    using primitives_t = std::vector<IPrimitive *>;

    /**
     * Добавляет примитив.
     * @param primitive Указатель на примитив.
     * @return Хендлер созданного примитива, либо ноль если создать невозможно.
     */
    handler_t add_primitive(IPrimitive *primitive) {
        if (map_.size() >= max_primitives_) { return 0; }
        if (++handler_ == 0) { ++handler_; }
        map_[handler_] = primitive;
        return handler_;
    }

    /**
    * Удаляет примитив.
    * @param handler Хендлер удаляемого примитива
    * @return true - Удаление прошло успешно, false - примитив не найден.
    */
    bool delete_primitive(handler_t handler) {
        return map_.erase(handler) != 0;
    }

    /**
     * Экспортировать документ.
     * @param exporter Указатель на экспортер.
     * @return true - экспорт прошел удачно, false - экспорт не возможен.
     */
    bool export_file(AExporter *exporter) {
        auto data = get_primitives();
        return exporter->do_convert(data);
    }

    /**
     * Импортировать документ.
     * @param importer Указатель на импортер.
     * @return true - ипорт прошел удачно, false - импорт не возможен.
     */
    bool import_file(AImporter *importer) {
        AImporter::result_t primitives{};
        if (importer->do_convert(primitives)) {
            clear();
            for (const auto &it: primitives) {
                add_primitive(it);
            }
            return true;
        }
        return false;
    }

    /**
     * Выдает указатели на все созданные примитивы.
     * @return Указатели на все созданные примитивы.
     */
    primitives_t get_primitives() {
        primitives_t    data{};
        for (const auto it : map_) {
            data.emplace_back(it.second);
        }
        return data;
    }

    /**
     * Выдает ссылку на созданный примитив.
     * @param handler Хендлер созданного примитива.
     * @param primitive Ссылка на созданный примитив.
     * @return true - примитив найден, false - примитив не найден.
     */
    bool get_primitive(handler_t handler, IPrimitive &primitive) {
        auto it = map_.find(handler);
        primitive = *it->second;
        return it != map_.end();
    }

    /**
     * Удаляет все примитивы.
     */
    void clear() {
        map_.clear();
    }

private:
    static const auto max_primitives_ = 1000;     ///< Максимальное количество примитивов в документе.
    handler_t         handler_        = 0;        ///< Последный выданный хендлер.
    map_t             map_{};                     ///< Мап указателей на созданные примитивы.
};
