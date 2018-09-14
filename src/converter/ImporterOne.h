#pragma once

#include "converter.h"

/// Импортер формата "один".
struct ImporterOne : public AImporter {

   /**
     * Конструктор.
     * @param file_name Имя файла, откуда происходит импорт.
     */
    explicit ImporterOne(const std::string &file_name) : AImporter(file_name) {};

    /**
     * Произвести экспорт.
     * @return true - конвертация выполнена успешно.
     */
    bool do_convert(result_t &result) override;
};