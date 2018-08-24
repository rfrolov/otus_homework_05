#pragma once

#include <fstream>
#include <memory>
#include "../primitives/IPrimitive.h"

/// Абстракный класс для импортеров данных.
struct AImporter {
    using primitive_t = std::shared_ptr<IPrimitive>;
    using result_t = std::vector<primitive_t>;

    /**
     * Конструктор.
     * @param file_name Имя файла, откуда происходит импорт.
     */
    explicit AImporter(const std::string &file_name) { fs_.open(file_name, std::ios::in); }

    virtual ~AImporter() { fs_.close(); }

    /**
     * Произвести импорт.
     * @return true - конвертация выполнена успешно.
     */
    virtual bool do_convert(result_t &) = 0;

protected:
    std::fstream fs_;
};


/// Абстракный класс для экспортеров данных.
struct AExporter {
    using primitive_t = std::shared_ptr<IPrimitive>;
    using data_t = std::vector<primitive_t>;

    /**
     * Конструктор.
     * @param file_name Имя файла, куда происходит экспорт.
     */
    explicit AExporter(const std::string &file_name) { fs_.open(file_name, std::ios::out); }

    virtual ~AExporter() { fs_.close(); }

    /**
     * Произвести экспорт.
     * @return true - конвертация выполнена успешно.
     */
    virtual bool do_convert(data_t &) = 0;

protected:
    std::fstream fs_;
};
