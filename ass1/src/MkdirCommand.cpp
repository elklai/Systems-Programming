
#include "../include/Commands.h"

MkdirCommand:: MkdirCommand (string args):BaseCommand(args) {

}


void MkdirCommand:: execute(FileSystem & fs){
    vector<string> path=this->dividePath(this->getArgs());
    Directory* di=&(this->chekAndGoTo(fs,path));
    if(( path.back() == "root") || (path.back() == ".." ) || (di == 0 ) )
    {
        cout << "The system cannot find the path specified";
        return;
    }
    bool found = false;
    vector<string>::iterator it;
    for (it = path.begin(); (it < path.end()) && !found ; it++)
        if( (*(it)) == di->getName() )
            found = true;


    if( (found) && (di-> findChildren(*(it)) != 0 ))
        cout<<"The directory already exists";
    else {
        if(!found)
            it = path.begin();
        while (it < path.end()) {
            di->addFile(new Directory(*it,di));//to check if its legal writing
            di = dynamic_cast<Directory*>(di->findChildren(*it));
            it++;
        }
    }
}


string MkdirCommand:: toString(){
    return "Mkdir";
}
//
// Created by elklai on 12/11/17.
//

