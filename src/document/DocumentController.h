#pragma once

#include <cassert>
#include "DocumentModel.h"
#include "DocumentView.h"

/**
 * Контроллер документа.
 */
struct DocumentController {
    using handler_t = DocumentModel::handler_t;

    /**
     * Конструктор.
     * @param model Указатель на модель.
     * @param view Указатель на представление.
     */
    DocumentController(DocumentModel *model, DocumentView *view) : model_{model}, view_{view} {
        assert(model_ != nullptr);
        assert(view_ != nullptr);
        view_->redraw(*model_);
    };

    /**
     * Добавляет примитив.
     * @param primitive Указатель на создаваемый примиттив.
     * @return Хендлер созданного примитива, либо ноль если создать невозможно.
     */
    handler_t add_primitive(IPrimitive *primitive) {
        auto id = model_->add_primitive(primitive);
        view_->redraw(*model_);
        return id;
    }

    /**
     * Удаляет примитив.
     * @param handler Хендлер удаляемого примитива
     */
    void delete_primitive(handler_t handler) {
        model_->delete_primitive(handler);
        view_->redraw(*model_);
    }

    /**
     * Выдает ссылку на созданный примитив.
     * @param handler Хендлер созданного примитива.
     * @param primitive Ссылка на созданный примитив.
     * @return true - примитив найден, false - примитив не найден.
     */
    bool get_primitive(handler_t handler, IPrimitive &primitive) {
        return model_->get_primitive(handler, primitive);
    }

    /**
     * Импортировать документ.
     * @param importer Указатель на импортер.
     * @return true - ипорт прошел удачно, false - импорт не возможен.
     */
    bool import_file(AImporter *importer) {
        if(model_->import_file(importer)) {
            view_->redraw(*model_);
            return true;
        }
        return false;
    }

    /**
     * Экспортировать документ.
     * @param exporter Указатель на экспортер.
     * @return true - экспорт прошел удачно, false - экспорт не возможен.
     */
    bool export_file(AExporter *exporter) {
        return model_->export_file(exporter);
    }

    /**
     * Очистить документ.
     */
    void clear() {
        model_->clear();
        view_->redraw(*model_);
    }

private:
    std::unique_ptr<DocumentModel> model_{nullptr};
    std::unique_ptr<DocumentView>  view_{nullptr};
};

