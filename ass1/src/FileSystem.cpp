#include "../include/FileSystem.h"//
#include "../include/Commands.h"//
#include "../include/GlobalVariables.h"
// Created by elklai on 16/11/17.
//
/////////important to updates root and dont delete on set !!!!
#include "../include/FileSystem.h"

FileSystem:: FileSystem():rootDirectory(new Directory( "root" , nullptr )) , workingDirectory(rootDirectory){
}


Directory& FileSystem:: getRootDirectory() const{
    return *(this->rootDirectory);
} // Return reference to the root directory


Directory& FileSystem:: getWorkingDirectory() const{
    return *(this->workingDirectory);
} // Return reference to the working directory


void FileSystem:: setWorkingDirectory(Directory *newWorkingDirectory){
    this->workingDirectory=newWorkingDirectory;
} // Change the working directory of the file system


void FileSystem:: copy(const FileSystem &other){
    Directory* copy=&(other.getRootDirectory());
    Directory currentRoot(*copy);
    this->rootDirectory=&currentRoot;
    vector<string> absolutePath=BaseCommand ::dividePath(other.getWorkingDirectory().getAbsolutePath());
    FileSystem* thisFs=this;
    this->setWorkingDirectory(&(BaseCommand::chekAndGoTo(*thisFs,absolutePath)));

}

void FileSystem:: clear(){
    delete &(this->getRootDirectory());
    setWorkingDirectory(nullptr);
    this->rootDirectory= nullptr;
}

FileSystem::~FileSystem(){
    if( ( verbose == 3 ) || ( verbose ==1) )
    {
        cout << "FileSystem::~FileSystem()";
    }
    this->clear();
}

FileSystem::FileSystem(const FileSystem &other):FileSystem(){///to check why we need FileSystem() constructor init!
    if( ( verbose == 3 ) || ( verbose ==1) )
    {
        cout << "FileSystem::FileSystem(const FileSystem &other)";
    }
    this->copy(other);
}

FileSystem::FileSystem(FileSystem &&other){
    if( ( verbose == 3 ) || ( verbose ==1) )
    {
        cout << "FileSystem::FileSystem(FileSystem &&other)";
    }
    this->rootDirectory=other.rootDirectory;
    this->setWorkingDirectory(&(other.getWorkingDirectory()));
    other.rootDirectory= nullptr;
    other.setWorkingDirectory(nullptr);

}//move constructor


FileSystem& FileSystem:: operator= (const FileSystem &other) {
        if( ( verbose == 3 ) || ( verbose ==1) )
        {
            cout << "FileSystem& operator= (const FileSystem &other)";
        }
    if(this!=&other) {
        this->clear();
        this->copy(other);
    }
    return *this;
}//copy assignment


FileSystem& FileSystem:: operator= (FileSystem &&other){
    if( ( verbose == 3 ) || ( verbose ==1) )
    {
        cout << "FileSystem& operator= (FileSystem &&other)";
    }
    if(this!=&other) {
        this->clear();
        this->rootDirectory=other.rootDirectory;
        this->setWorkingDirectory(&(other.getWorkingDirectory()));
        other.rootDirectory= nullptr;
        other.setWorkingDirectory(nullptr);
    }
}//move assignment

// we never set root directory (we never asked for it)