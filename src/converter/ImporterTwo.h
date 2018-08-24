#pragma once

#include "converter.h"

struct ImporterTwo : public AImporter {

    /**
      * Конструктор.
      * @param file_name Имя файла, откуда происходит импорт.
      */
    explicit ImporterTwo(const std::string &file_name) : AImporter(file_name) {};

    /**
     * Произвести экспорт.
     * @return true - конвертация выполнена успешно.
     */
    bool do_convert(result_t &result) override {
        //
        // Реализация импорта данных из файла.
        //
        return true;
    }
};