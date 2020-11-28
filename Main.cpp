#include <iostream>
#include "FileSystemController.cpp"

int main(){
    FileSystemController* fileSystemController = new FileSystemController(200, 4);
    std::cout << "createF Ulyan" << std::endl;
    fileSystemController->action("createF Ulyan");
    std::cout << "createF Alina" << std::endl;
    fileSystemController->action("createF Alina");
    std::cout << "createD dir" << std::endl;
    fileSystemController->action("createD dir");

    std::cout << "show" << std::endl;
    fileSystemController->action("show");

    std::cout << "dir dir" << std::endl;
    fileSystemController->action("dir dir");
    std::cout << "createF Ulyan" << std::endl;
    fileSystemController->action("createF Ulyan");
    std::cout << "createF Alina" << std::endl;
    fileSystemController->action("createF Alina");
    std::cout << "dir dir" << std::endl;
    fileSystemController->action("dir ..");

    std::cout << "show" << std::endl;
    fileSystemController->action("show");

    std::cout << "deleteD dir" << std::endl;
    fileSystemController->action("deleteD dir");
    std::cout << "show" << std::endl;
    fileSystemController->action("show");
}