
#include "../include/Commands.h"

MvCommand::MvCommand(string args):BaseCommand(args){

}


void MvCommand:: execute(FileSystem & fs){
    string source , destination ;
    Directory* sourcePathDirectory;
    Directory* destinationPathDirectory;
    BaseFile* mem;
    Directory* memParent;
    BaseFile* current;
    BaseFile* current2;
    int currentPos=0;
    bool canNotMv=false;
    size_t found = this->getArgs().find_last_of(" ");

    source = this->getArgs().substr( 0 , found );
    destination = this->getArgs().substr( found + 1 );

    vector<string> sourcePathVector = this->dividePath( source );
    vector<string> destinationPathVector = this->dividePath( destination );

    if(sourcePathVector.size()==1)
        sourcePathDirectory=&fs.getWorkingDirectory();
    else
        sourcePathDirectory = &( this->chekAndGoTo( fs , sourcePathVector ) );
    if(destinationPathVector.size()==0)
        destinationPathDirectory=&fs.getWorkingDirectory();
    else if(destinationPathVector.size()==1){
        if (destinationPathVector[0] == "root")
            destinationPathDirectory = &fs.getRootDirectory();
        else if (destinationPathVector[0] == "..")
            destinationPathDirectory = fs.getWorkingDirectory().getParent();
        else {
            destinationPathDirectory = &fs.getWorkingDirectory();
            mem = destinationPathDirectory->findChildren(destinationPathVector[0]);
            if (mem == 0) {
                cout << "No such file or directory";
                return;
            }
            if (mem->goInside() == 0) {
                cout << "No such file or directory";//for case that the print need to be different!
                return;
            }
            destinationPathDirectory = dynamic_cast<Directory *>(mem);

        }
    }
    else
        destinationPathDirectory = &( this->chekAndGoTo( fs , destinationPathVector ) );
    int i, j;
    bool found1 = false;
    bool found2 = false;
    if (sourcePathVector.size() > 1) {
        for (i = 0; i < sourcePathVector.size() && !found1; i++)
            if (sourcePathDirectory->getName() == sourcePathVector[i])
                found1 = true;

        if (i != sourcePathVector.size() - 1) {
            cout << "No such file or directory";
            return;
        }
    }
    if (destinationPathVector.size() > 1)
        for ( j = 0; j < destinationPathVector.size() && !found2; j++)
            if (destinationPathDirectory->getName() == destinationPathVector[j])
                found2 = true;
    if (j != destinationPathVector.size() - 1) {
        cout << "No such file or directory";
        return;
    }
    current = sourcePathDirectory->findChildren(sourcePathVector[sourcePathVector.size() - 1]);
    memParent=&fs.getWorkingDirectory();
    while(memParent!= nullptr){
        if(current==memParent) {
            cout <<"Can’t move directory";
            return;
        }
        memParent=memParent->getParent();
    }
    if (destinationPathVector.size() < 2) {}
    else {
        current2 = destinationPathDirectory->findChildren(destinationPathVector[j]);
        if ((current == 0) || (current2 == 0) || (current2->goInside() == 0))
            cout << "No such file or directory";
        else {
            //vector<BaseFile*> tmp=(sourcePathDirectory->getChildren());
            //tmp.erase(tmp.begin()+1);

            destinationPathDirectory = dynamic_cast<Directory *>(current2->goInside());
            sourcePathDirectory->removeFileUndeep(current->getName());
            destinationPathDirectory->addFile(current);
            if(current->goInside() != 0 )
            {
                Directory* current3 = dynamic_cast<Directory*>(current->goInside());
                current3->setParent(destinationPathDirectory);
            }
        }
    }
}


string MvCommand:: toString(){
 return "Mv";
}
//
// Created by elklai on 12/11/17.
//

