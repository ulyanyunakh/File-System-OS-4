#include <iostream>
#include <string>
#include <Windows.h>
#include "FileSystemController.cpp"

int main(){
    FileSystemController* fileSystemController = new FileSystemController(200, 4);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
    while (true) {
        std::string command;
        std::getline(std::cin, command);
        if (command == "exit") break;
        fileSystemController->action(command);
    }
}