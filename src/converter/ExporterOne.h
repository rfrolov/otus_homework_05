#pragma once

#include "converter.h"

/**
 * Экспортер в формат "один".
 */
struct ExporterOne : public AExporter {

    /**
     * Конструктор.
     * @param file_name Имя файла, куда происходит экспорт.
     */
    explicit ExporterOne(const std::string &file_name) : AExporter(file_name) {};

    /**
     * Произвести экспорт.
     * @return true - конвертация выполнена успешно.
     */
    bool do_convert(data_t &data) override;
};