#include "../include/Commands.h"


RmCommand:: RmCommand(string args):BaseCommand(args){
}


void RmCommand:: execute(FileSystem & fs) {
    BaseFile* toRm;
    Directory* pathDirectory;
    vector<string> pathVector = this->dividePath(this->getArgs());
        if (pathVector.size() == 1) {
            pathDirectory = &fs.getWorkingDirectory();
            if(pathDirectory->findChildren(pathVector.back())==0) {

                cout << "No such file or directory";
                return;
            }
            else {
                toRm = pathDirectory->findChildren(pathVector.back());
                pathDirectory->removeFile(toRm);
            }
        }
        else {
            pathDirectory = &(this->chekAndGoTo(fs, pathVector));
            int i;
            bool found = false;
            for( i = 0 ; (i < pathVector.size()) && !found ; i++ )
            {
                if( pathDirectory->getName() == pathVector[i] )
                    found = true;
            }
            toRm = pathDirectory->findChildren(pathVector[i]);
            if (toRm == 0) {
                cout << "No such file or directory";//to check print
                return;
            }
            vector<string> pathCheckVector = this->dividePath(fs.getWorkingDirectory().getAbsolutePath());
            int j;
            bool found2 = false;
            for( j = 0 ; (j < pathCheckVector.size()) && !found2 ; j++ )
            {
                if( toRm->getName() == pathCheckVector[j] ){
                    cout << "Can’t remove directory";
                    return;
                }
            }

            pathDirectory->removeFile(toRm);

        }
    }

string RmCommand:: toString(){
    return ("Rm");
}
//
// Created by elklai on 12/11/17.
//

