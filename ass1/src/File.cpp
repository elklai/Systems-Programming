#include "../include/Files.h"



File:: File( string name , int size ):BaseFile(name) , size(size){

}// Constructor


int File:: getSize(){
    return size;
} // Return the size of the file



string File:: toPrint(){
    return ("FILE   " + this->getName() +"  ");
}


void File:: changeParent(BaseFile* newParent){}


BaseFile* File:: goInside(){return 0;}

File:: ~File(){}

File::File(const File &other):BaseFile(other.getName()) , size(other.size){}

File& File:: operator=(const File &other){
    this->setName(other.getName());
    this->size = other.size;
    return *this;
}
//
// Created by elklai on 12/11/17.
//

