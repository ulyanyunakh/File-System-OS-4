#include <iostream>
#include <vector>
#include "Directory.cpp"
#include "Cluster.cpp"

class FileSystem {
private:
    Directory* root;
    Directory* current;
    std::vector<Cluster> clusters;

    int findFreeCluster() {
        for (int i = 0; i < clusters.size(); i++) {
            if (clusters[i].isFree()) {
                return i;
            }
        }
        return -1;
    }

    void deleteFile(File* file){
        freeClusters(file->getClusterNumbers());  
        delete file;
    }

    void deleteDirectory(Directory* directory) {
        std::vector<Directory*> directories = directory->getDirectories();
        for (int i = 0; i < directories.size(); i++) {
            directory->removeDirectory((*directories[i]).getDirectoryName());
            deleteDirectory(directories[i]);
        }
        std::vector<File*> files = directory->getFiles();
        for (int i = 0; i < files.size(); i++) {
            directory->removeFile((*files[i]).getFileName());
            deleteFile(files[i]);
        }
        freeClusters(directory->getClusterNumbers());
        delete directory;
    }

    void freeClusters(std::vector<int> clusterNumbers) {
        for (int i = 0; i < clusterNumbers.size(); i++) {
            clusters[clusterNumbers[i]].freeCluster();
            clusters[clusterNumbers[i]].freeClusterInfo();
        }
    }
public: 
    FileSystem(int memory, int clusterSize) {
        for (int i = 0; i < memory / clusterSize; i++) {
            Cluster cluster(i, clusterSize);
            clusters.push_back(cluster);
        }
        int clusterNumber = findFreeCluster();
        root = new Directory(clusterNumber, NULL, "root");
        current = root;
    }
    
    void createFile(std::vector<std::string> action) {
        int clusterNumber = findFreeCluster();
        if (clusterNumber != -1) {
            clusters[clusterNumber].takeCluster();
            File* file = new File(clusterNumber, action[1]);
            current->addFile(file);
        }
    }

    void createDirectory(std::vector<std::string> action) {
        int clusterNumber = findFreeCluster();
        if (clusterNumber != -1) {
            clusters[clusterNumber].takeCluster();
            Directory* directory = new Directory(clusterNumber, current, action[1]);
            current->addDirectory(directory);
        }
    }

    void showDirectory(std::vector<std::string> action) {
        std::cout << "Files:\n";
        std::vector<File*> files = current->getFiles();
        for (int i = 0; i < files.size(); i++) {
            std::cout << (*files[i]).getFileName() << std::endl;
        }
        std::cout << "Directories:\n";
        std::vector<Directory*> directories = current->getDirectories();
        for (int i = 0; i < directories.size(); i++) {
            std::cout << (*directories[i]).getDirectoryName() << std::endl;
        }
        int h = 0;
        for (int i = 0; i < clusters.size(); i++) {
            if (clusters[i].isFree()) h++;
        }
        std::cout << "Clusters: " << h << std::endl;
    }

    void changeDirectory(std::vector<std::string> action) {
        if (action[1] == "..") {
            if (current->getParent() != NULL) {
                current = current->getParent();
            }
        }
        else {
            std::vector<Directory*> directories = current->getDirectories();
            for (int i = 0; i < directories.size(); i++) {
                if ((*directories[i]).getDirectoryName() == action[1]) {
                    current = directories[i];
                }
            }
        }
    }

    void deleteFile(std::vector<std::string> action) {
        std::vector<File*> files = current->getFiles();
        for (int i = 0; i < files.size(); i++) {
            if ((*files[i]).getFileName() == action[1]) {
                current->removeFile(action[1]);
                deleteFile(files[i]);
            }
        }
    }

    void deleteDirectory(std::vector<std::string> action) {
        std::vector<Directory*> directories = current->getDirectories();
        for (int i = 0; i < directories.size(); i++) {
            if ((*directories[i]).getDirectoryName() == action[1]) {
                current->removeDirectory(action[1]);
                deleteDirectory(directories[i]);
            }
        }
    }
};