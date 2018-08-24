#pragma once

#include <cassert>
#include "DocumentModel.h"
#include "DocumentView.h"

/// Контроллер документа.
struct DocumentController {
    using handler_t = DocumentModel::handler_t;
    using primitive_t = std::shared_ptr<IPrimitive>;

    /**
     * Конструктор.
     * @param model Указатель на модель.
     * @param view Указатель на представление.
     */
    explicit DocumentController(std::shared_ptr<DocumentModel> model, std::shared_ptr<DocumentView> view) : model_{model}, view_{view} {
        assert(model_ != nullptr);
        assert(view_ != nullptr);
        view_->redraw();
    };

    /**
     * Добавляет примитив.
     * @param primitive Указатель на создаваемый примиттив.
     * @return Хендлер созданного примитива, либо ноль если создать невозможно.
     */
    handler_t add_primitive(primitive_t primitive) {
        auto id = model_->add_primitive(primitive);
        view_->redraw();
        return id;
    }

    /**
     * Удаляет примитив.
     * @param handler Хендлер удаляемого примитива
     */
    void delete_primitive(handler_t handler) {
        model_->delete_primitive(handler);
        view_->redraw();
    }

    /**
     * Выдает указатель на созданный примитив.
     * @param handler Хендлер созданного примитива.
     * @param primitive Указатель на созданный примитив.
     * @return true - примитив найден, false - примитив не найден.
     */
    bool get_primitive(handler_t handler, primitive_t *primitive) {
        return model_->get_primitive(handler, primitive);
    }

    /**
     * Импортировать документ.
     * @param importer Указатель на импортер.
     * @return true - ипорт прошел удачно, false - импорт не возможен.
     */
    bool import_document(std::shared_ptr<AImporter> importer) {
        if(model_->import_document(importer)) {
            view_->redraw();
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
        return model_->export_document(exporter);
    }

    /**
     * Очистить документ.
     */
    void clear() {
        model_->clear();
        view_->redraw();
    }

    /// Перерисовывает документ.
    void redraw() {
        view_->redraw();
    }

private:
    std::shared_ptr<DocumentModel> model_{nullptr};
    std::shared_ptr<DocumentView>  view_{nullptr};
};

