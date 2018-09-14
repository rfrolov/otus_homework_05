#include "document/DocumentController.h"

int main() {
    std::cout << std::endl << "Create document:" << std::endl;

    auto view  = std::make_shared<DocumentView>();
    auto model = std::make_shared<DocumentModel>(view);
    DocumentController document_control = DocumentController(model);


    std::cout << std::endl << "Add dot:" << std::endl;
    document_control.add_dot(Coordinates{1, 2});


    std::cout << std::endl << "Add line:" << std::endl;
    Coordinates line_coordinates[2] = {Coordinates{1, 2}, Coordinates{3, 4}};
    auto line_h = document_control.add_line(line_coordinates);


    std::cout << std::endl << "Add triangle:" << std::endl;
    Coordinates triangle_coordinates[3] = {Coordinates{1, 2}, Coordinates{3, 4}, Coordinates{5, 6}};
    document_control.add_triangle(triangle_coordinates);


    std::cout << std::endl << "Modify line:" << std::endl;
    line_coordinates[0] = Coordinates{1001, 1002};
    line_coordinates[1] = Coordinates{1003, 1004};
    document_control.modify_line(line_h, line_coordinates);


    std::cout << std::endl << "Redraw:" << std::endl;
    document_control.redraw();


    std::cout << std::endl << "Delete line:" << std::endl;
    document_control.delete_primitive(line_h);


    std::cout << std::endl << "Export:";
    if (document_control.export_format_one("test.txt")) {
        std::cout << std::endl << "OK" << std::endl;
    } else {
        std::cout << std::endl << "error" << std::endl;
    }


    std::cout << std::endl << "Clear:" << std::endl;
    document_control.clear();


    std::cout << std::endl << "Import:" << std::endl;
    document_control.import_format_one("test.txt");


    std::cout << std::endl << "Add line:" << std::endl;
    line_coordinates[0] = Coordinates{7, 8};
    line_coordinates[1] = Coordinates{9, 10};
    document_control.add_line(line_coordinates);


    std::cout << std::endl << "Redraw:" << std::endl;
    document_control.redraw();

    return 0;
}