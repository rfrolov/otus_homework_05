#include "document/DocumentController.h"
#include "primitives/Dot.h"
#include "primitives/Line.h"
#include "primitives/Triangle.h"
#include "converter/ExporterOne.h"
#include "converter/ImporterOne.h"

int main() {
    std::cout << std::endl << "Create document:" << std::endl;

    auto model = std::make_shared<DocumentModel>();
    auto view  = std::make_shared<DocumentView>(model);

    DocumentController document_control = DocumentController(model, view);


    std::cout << std::endl << "Add dot:" << std::endl;
    document_control.add_primitive(std::make_shared<Dot>(Coordinates(1, 2)));


    std::cout << std::endl << "Add line:" << std::endl;
    auto line_h = document_control.add_primitive(std::make_shared<Line>(Line::coordinates_t{Coordinates(1, 2), Coordinates(3, 4)}));


    std::cout << std::endl << "Add triangle:" << std::endl;
    document_control.add_primitive(std::make_shared<Triangle>(Triangle::coordinates_t{Coordinates(1, 2), Coordinates(3, 4), Coordinates(5, 6)}));


    std::cout << std::endl << "Modify line:" << std::endl;
    std::shared_ptr<IPrimitive> line{};
    auto isOk = document_control.get_primitive(line_h, &line);
    if(isOk) {
        line->set_data(Line::serialised_t{2, 1001, 1002, 1003, 1004});
    }
    document_control.redraw();


    std::cout << std::endl << "Delete line:" << std::endl;
    document_control.delete_primitive(line_h);


    std::cout << std::endl << "Export:";
    if (document_control.export_document(std::make_shared<ExporterOne>("test.txt"))) {
        std::cout << std::endl << "OK" << std::endl;
    } else {
        std::cout << std::endl << "error" << std::endl;
    }


    std::cout << std::endl << "Clear:" << std::endl;
    document_control.clear();


    std::cout << std::endl << "Import:" << std::endl;
    document_control.import_document(std::make_shared<ImporterOne>("test.txt"));


    std::cout << std::endl << "Add triangle:" << std::endl;
    document_control.add_primitive(std::make_shared<Line>(Line::coordinates_t{Coordinates(7, 8), Coordinates(9, 10)}));
    return 0;
}