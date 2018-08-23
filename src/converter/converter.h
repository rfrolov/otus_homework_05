#pragma once

#include <string>
#include <fstream>
#include <vector>


struct AImporter {
    using primitive_t = IPrimitive *;
    using result_t = std::vector<primitive_t>;

    explicit AImporter(const std::string &file_name) { fs_.open(file_name, std::ios::in); }

    virtual ~AImporter() { fs_.close(); }

    virtual bool doConvert(result_t &) = 0;

protected:
    std::fstream fs_;
};

struct AExporter {
    using primitive_t = IPrimitive *;
    using data_t = std::vector<primitive_t>;

    explicit AExporter(const std::string &file_name) { fs_.open(file_name, std::ios::out); }

    virtual ~AExporter() { fs_.close(); }

    virtual bool doConvert(data_t &) = 0;

protected:
    std::fstream fs_;
};

struct Importer : public AImporter {
    explicit Importer(const std::string &file_name) : AImporter(file_name) {};

    bool doConvert(result_t &result) override;
};

struct Exporter : public AExporter {
    explicit Exporter(const std::string &file_name) : AExporter(file_name) {};

    bool doConvert(data_t &data) override;
};