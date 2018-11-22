#include "../include/Commands.h"


    RenameCommand:: RenameCommand(string args):BaseCommand(args) {
    }


    void RenameCommand:: execute(FileSystem & fs){

        string newName , path , oldName;
        size_t found = this->getArgs().find_last_of(" ");
        Directory* parentCheck;

        newName = this->getArgs().substr( found + 1 );
        path = this->getArgs().substr( 0 , found );

        vector<string> pathVector = this->dividePath( path );
        oldName = pathVector.back();
        pathVector.pop_back();
        Directory* pathDirectory;
        if(pathVector.size() == 0)
        {
            pathDirectory = &fs.getWorkingDirectory();
        }
        else {
            if (pathVector.size() == 1) {
                if ((pathVector[0] == ("root" ) )|| (pathVector[0] ==("/"))) {
                    pathDirectory = &fs.getRootDirectory();
                } else if (pathVector[0] == "..") {
                    pathDirectory = fs.getWorkingDirectory().getParent();
                } else {
                    pathDirectory = &fs.getWorkingDirectory();
                }
            } else {
                pathDirectory = (&(this->chekAndGoTo(fs, pathVector)));
                vector<string>::iterator it;
                bool notFound = true;
                for (it = pathVector.begin(); it < pathVector.end() && notFound; it++) {
                    if (*it == pathDirectory->getName())
                        notFound = false;
                }
                if (pathDirectory->findChildren(*(it)) == 0) {
                    cout << "No such file or directory";
                    return;
                } else if (pathDirectory->findChildren(*(it))->goInside() == 0) {
                    cout << "No such file or directory";
                    return;
                } else
                    pathDirectory = dynamic_cast<Directory *> (pathDirectory->findChildren(*(it))->goInside());
            }
        }
        if( pathDirectory->findChildren( oldName ) == 0 )
        {
            cout << "No such file or directory" ;
            return;
        }
        parentCheck = &fs.getWorkingDirectory();
        while ( parentCheck != nullptr )
        {
            if(parentCheck->getName() == oldName )
            {
                 cout << "Can’t rename the working directory or parents";
                 return;
            }
            parentCheck = parentCheck->getParent();
        }

        pathDirectory->findChildren(oldName)->setName( newName );

    }


    string RenameCommand:: toString(){
        return ("Rename" + this->getArgs());
    }




//
// Created by elklai on 12/11/17.
//