#pragma once

#include "converter.h"

struct ExporterTwo : public AExporter {

    /**
     * Конструктор.
     * @param file_name Имя файла, куда происходит экспорт.
     */
    explicit ExporterTwo(const std::string &file_name) : AExporter(file_name) {};

    /**
     * Произвести экспорт.
     * @return true - конвертация выполнена успешно.
     */
    bool do_convert(data_t &data) override {
        //
        // Реализация экспорта данных в файл.
        //
        return true;
    }
};