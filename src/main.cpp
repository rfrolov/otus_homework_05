#include "document/DocumentController.h"
#include "primitives/Dot.h"
#include "primitives/Line.h"
#include "primitives/Triangle.h"

int main(int, char *[]) {
    DocumentController document_control = DocumentController(new DocumentModel, new DocumentView);

    std::cout << std::endl << "Add dot:" << std::endl;
    document_control.add_primitive(new Dot(1, 2));

    std::cout << std::endl << "Add line:" << std::endl;
    auto line_h = document_control.add_primitive(new Line(1, 2, 3, 4));

    std::cout << std::endl << "Add triangle:" << std::endl;
    document_control.add_primitive(new Triangle(1, 2, 3, 4, 5, 6));

    std::cout << std::endl << "Delete line:" << std::endl;
    document_control.delete_primitive(line_h);

    std::cout << std::endl << "Export:" << std::endl;
    document_control.export_file("../../test/export.txt");

//    std::cout << std::endl << "Import:" << std::endl;
//    document_control.import_file("../../test/import.txt");

//    std::cout << std::endl << "Add triangle:" << std::endl;
//    document_control.add_primitive(new Triangle(1, 2, 3, 4, 5, 6));

    return 0;
}