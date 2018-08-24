#include "document/DocumentController.h"
#include "primitives/Dot.h"
#include "primitives/Line.h"
#include "primitives/Triangle.h"
#include "converter/ExporterOne.h"
#include "converter/ImporterOne.h"

int main(int, char *[]) {
    std::cout << std::endl << "Create document:" << std::endl;
    DocumentController document_control = DocumentController(new DocumentModel, new DocumentView);

    std::cout << std::endl << "Add dot:" << std::endl;
    document_control.add_primitive(new Dot(Coordinates(1, 2)));

    std::cout << std::endl << "Add line:" << std::endl;
    auto line_h = document_control.add_primitive(new Line({Coordinates(1, 2), Coordinates(3, 4)}));

    std::cout << std::endl << "Add triangle:" << std::endl;
    document_control.add_primitive(new Triangle({Coordinates(1, 2), Coordinates(3, 4), Coordinates(5, 6)}));

    std::cout << std::endl << "Delete line:" << std::endl;
    document_control.delete_primitive(line_h);

    std::cout << std::endl << "Export:";
    if (document_control.export_file(new ExporterOne("test.txt"))) {
        std::cout << std::endl << "OK" << std::endl;
    } else {
        std::cout << std::endl << "error" << std::endl;
    }

    std::cout << std::endl << "Clear:" << std::endl;
    document_control.clear();

    std::cout << std::endl << "Import:" << std::endl;
    document_control.import_file(new ImporterOne("test.txt"));

    std::cout << std::endl << "Add triangle:" << std::endl;
    document_control.add_primitive(new Line({Coordinates(7, 8), Coordinates(9, 10)}));
    return 0;
}