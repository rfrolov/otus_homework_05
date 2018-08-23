#pragma once

#include <memory>
#include <cassert>
#include "DocumentModel.h"
#include "DocumentView.h"
#include "../primitives/IPrimitive.h"
#include "../converter/converter.h"

struct DocumentController {
    using handler_t = DocumentModel::handler_t;

    DocumentController(DocumentModel *model, DocumentView *view) : model_{model}, view_{view} {
        assert(model_ != nullptr);
        assert(view_ != nullptr);
    };

    /**
     * Добавить примитив.
     * @return Хендлер созданного примитива, либо ноль если создать невозможно.
     */
    handler_t add_primitive(IPrimitive *primitive) {
            auto id = model_->add_primitive(primitive);
            view_->redraw(*model_);
            return id;
    }

    /**
     * Удалить примитив.
     * @param handler Хендлер удаляемого примитива
     */
    void delete_primitive(handler_t handler) {
        model_->delete_primitive(handler);
        view_->redraw(*model_);
    }

    // TODO: Дописать.
    bool get_primitive(handler_t handler, IPrimitive &primitive) {
        auto primitives = model_->get_primitives();
        auto it = primitives.find(handler);
        primitive = *it->second;
        return it != primitives.end();
    }

    bool import_file(const std::string& fileName) {
        // TODO: Сделать реализацию иморта из разных форматов.
        // TODO: Переместить в модель.
        Importer importer{fileName};
        Importer::result_t primitives{};
        auto isOk = importer.doConvert(primitives);
        if(isOk) {
            for(const auto& it: primitives) {
                model_->add_primitive(it);
            }
        }
        view_->redraw(*model_);
    }

    bool export_file(const std::string &fileName) {
        // TODO: Сделать реализацию экспорта в разные форматы.
        // TODO: Переместить в модель.
//        Exporter exporter{fileName};
//        Exporter::data_t data{new Dot(1, 2), new Line(1, 2, 3, 4), new Triangle(1, 2, 3, 4, 5, 6)};
//        auto isOk = exporter.doConvert(data);

        return true;
    }

private:
    std::unique_ptr<DocumentModel> model_{nullptr};
    std::unique_ptr<DocumentView>  view_{nullptr};
};

