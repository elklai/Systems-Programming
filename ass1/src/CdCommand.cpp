#include "../include/Commands.h"

CdCommand:: CdCommand(string args) :BaseCommand(args){

}


void CdCommand:: execute(FileSystem & fs){
    vector<string> path= this->dividePath(this->getArgs());
    Directory* di;
    BaseFile* mem;
    if( path.size() == 0 ) {
        cout << "The system cannot find the path specified";
        return;
    }
    else {
        if (path.size() == 1)
        {
            if (path[0] == "root") {
                fs.setWorkingDirectory(&fs.getRootDirectory());
                return;
            } else if (path[0] == "..") {
                fs.setWorkingDirectory(fs.getWorkingDirectory().getParent());
                return;
            } else {
                di = &fs.getWorkingDirectory();
                mem= (di->findChildren( path.back()));////eror we said to push the last no good;
                if(mem==0)
                    cout << "The system cannot find the path specified";
                else
                    fs.setWorkingDirectory(dynamic_cast<Directory *>(mem));
            }
        }
        else
        {
            di = &this->chekAndGoTo(fs, path);
            mem= (di->findChildren( path.back()));////eror we said to push the last no good;

            if(mem==0)
                cout << "The system cannot find the path specified" ;
            else
                fs.setWorkingDirectory(dynamic_cast<Directory*>(mem));

        }
    }
    return;
}

// need to check if we should also check the workingDirectory children


string CdCommand:: toString(){
    return "Cd" ;
}

