#include "../include/Commands.h"
#include "../include/Files.h"

    MkfileCommand:: MkfileCommand(string args): BaseCommand(args){
    }

    void MkfileCommand:: execute(FileSystem & fs) {
        string sSize, path;
        int size;
        
        Directory *pathDirectory;
        string::size_type sz;
        size_t found = getArgs().find_last_of(" ");

        sSize = this->getArgs().substr(found + 1);
        size = std::stoi(sSize, &sz);
        path = this->getArgs().substr(0, found);

        vector<string> pathVector = this->dividePath(path);
        string name = pathVector[pathVector.size() - 1];
        pathVector.pop_back();
        
        File *makeFile =new File(name , size);
        
        if (pathVector.size() == 0) {
            pathDirectory = &fs.getWorkingDirectory();
            pathDirectory->addFile(makeFile);
            return;
        } else if (pathVector.size() == 1) {
            if (pathVector[0] == "root") {
                pathDirectory = &fs.getRootDirectory();
                if (pathDirectory->findChildren(name) == 0) {
                    pathDirectory->addFile(makeFile);
                    return;
                } else {
                    cout << "File already exists";
                    return;
                }
            } else if (pathVector[0] == "..") {
                pathDirectory = fs.getWorkingDirectory().getParent();
                if (pathDirectory->findChildren(name) == 0) {
                    pathDirectory->addFile(makeFile);
                    return;
                } else {
                    cout << "File already exists";
                    return;
                }
            } else {
                pathDirectory = &fs.getWorkingDirectory();
                if (pathDirectory->findChildren(pathVector[0]) == 0) {
                    cout << "The system cannot find the path specified";
                    return;
                } else if (pathDirectory->findChildren(pathVector[0])->goInside() == 0)
                    cout << "The system cannot find the path specified";
                else {
                    pathDirectory = dynamic_cast<Directory *>(pathDirectory->findChildren(pathVector[0])->goInside());
                    if (pathDirectory->findChildren(name) == 0) {
                        pathDirectory->addFile(makeFile);
                        return;
                    } else {
                        cout << "File already exists";
                        return;
                    }
                }
            }
        } else {
            pathDirectory = &(this->chekAndGoTo(fs, pathVector));
            vector<string>::iterator it;
            bool foundName = false;
            for (it = pathVector.begin(); (it < pathVector.end()) && !foundName; it++) {
                if (*it == pathDirectory->getName())
                    foundName = true;
            }

            if (it == pathVector.end())
                it--;
            if ((pathDirectory->findChildren(*(it)) == 0)) {
                cout << "The system cannot find the path specified";
                return;
            } else if (pathDirectory->findChildren(*(it))->goInside() == 0) {
                cout << "File already exists";
                return;
            } else {
                pathDirectory = dynamic_cast<Directory *>(pathDirectory->findChildren(*(it)))->goInside();
                if (pathDirectory->findChildren(name) != 0) {
                    cout << "File already exists";
                    return;
                }
                pathDirectory->addFile(makeFile);
            }

        }
    }
    string MkfileCommand:: toString(){
        return "Mkfile";
    }

//
// Created by elklai on 12/11/17.
//

