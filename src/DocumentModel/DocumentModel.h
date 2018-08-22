#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include "../primitives/IPrimitive.h"

struct DocumentModel {
    using handler_t    = uint64_t;                          ///< Тип хендлера примитива.
    using serialised_t = IPrimitive::serialised_t;           ///< Тип сериализованых данных примитива.
    using map_t        = std::map<handler_t, IPrimitive *>; // TODO: написать правильное название и комментарий.

    /**
     * Добавить примитив.
     * @return Хендлер созданного примитива, либо ноль если создать невозможно.
     */
    handler_t add_primitive(IPrimitive *primitive) {
        if (map_.size() >= max_primitives_) { return 0; }
        if (++handler_ == 0) { ++handler_; }
        map_[handler_] = primitive;
        return handler_;
    }

    /**
    * Удалить примитив.
    * @param handler Хендлер удаляемого примитива
    * @return true - Удаление прошло успешно, false - примитив не найден.
    */
    bool delete_primitive(handler_t handler) {
        return map_.erase(handler) != 0;
    }

    // TODO: добавить коментарий.
    const map_t get_primitives() { return map_; };

private:
    static const auto max_primitives_   = 1000;     ///< Максимальное количество примитивов в документе.
    handler_t         handler_ = 0;                 ///< Последный выданный хендлер.
    map_t             map_;                         ///< Мап сериализованных даннх примитивов.
};
