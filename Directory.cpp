#include <iostream>
#include <vector>
#include "File.cpp"

class Directory {
private:
    std::vector<int> clusterNumbers;
    std::string directoryName;
    Directory* parent;
    std::vector<File*> files;
    std::vector<Directory*> childs;
public:
    Directory(int clusterNumber, Directory* dir, std::string name) {
        clusterNumbers.push_back(clusterNumber);
        parent = dir;
        directoryName = name;
    }

    std::vector<int> getClusterNumbers() {
        return clusterNumbers;
    }

    std::string getDirectoryName() {
        return directoryName;
    }

    std::vector<File*> getFiles() {
        return files;
    }

    std::vector<Directory*> getDirectories() {
        return childs;
    }

    void setDirectoryName(std::string newDirectoryName) {
        directoryName = newDirectoryName;
    }

    void addFile(File* file) {
        files.push_back(file);
    }

    void removeFile(std::string fileName) {
        for (int i = 0; i < files.size(); i++)
        {
            if ((*files[i]).getFileName() == fileName) {
                files.erase(files.begin() + i);
            }
        }
    }

    void addDirectory(Directory* directory) {
        childs.push_back(directory);
    }

    void removeDirectory(std::string dirName) {
        for (int i = 0; i < childs.size(); i++)
        {
            if ((*childs[i]).getDirectoryName() == dirName) {
                childs.erase(childs.begin() + i);
            }
        }
    }

    Directory* getParent() {
        return parent;
    }
};