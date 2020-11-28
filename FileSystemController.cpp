#include <iostream>
#include "FileSystem.cpp"

class FileSystemController {
private:
	FileSystem *fileSystem;

	std::string ADD_FILE = "createF";
	std::string SHOW_DIR = "show";
	std::string ADD_DIR = "createD";
	std::string CHANGE_DIR = "dir";
	std::string DELETE_DIR = "deleteD";
	std::string DELETE_FILE = "deleteF";

	std::vector<std::string> handleAction(std::string actionStr) {
		std::vector<std::string> command;
		int start = 0;
		int lenght = 0;
		for (int i = 0; i < actionStr.length(); i++) {
			if (actionStr[i] == ' ' || i == actionStr.length() - 1) {
				if (i == actionStr.length() - 1) lenght++;
				std::string str = actionStr.substr(start, lenght);
				start = i + 1;
				lenght = 0;
				command.push_back(str);
			}
			else lenght++;
		}
		return command;
	}
public:
	FileSystemController(int memory, int clusterSize) {
		fileSystem = new FileSystem(memory, clusterSize);
	}

	void action(std::string actionStr) {
		std::vector<std::string> action = handleAction(actionStr);
		if (action[0] == ADD_FILE) fileSystem->createFile(action);
		if (action[0] == SHOW_DIR) fileSystem->showDirectory(action);
		if (action[0] == ADD_DIR) fileSystem->createDirectory(action);
		if (action[0] == CHANGE_DIR) fileSystem->changeDirectory(action);
		if (action[0] == DELETE_DIR) fileSystem->deleteDirectory(action);
		if (action[0] == DELETE_FILE) fileSystem->deleteFile(action);
	}
};