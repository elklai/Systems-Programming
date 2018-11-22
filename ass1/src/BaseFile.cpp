#include "../include/Files.h"
//important note: to check if virtual is needed in this class!!!

BaseFile::BaseFile(string name):name(name) {

}

string BaseFile:: getName() const{
    return name;// to check how written
}

void BaseFile::setName(string newName){
    name=newName;//to check how written and maybe we have a memory leak need to check in string class
}



int BaseFile:: getSize(){ }



string BaseFile::toPrint(){}

void BaseFile:: changeParent(BaseFile* newParent){}

BaseFile* BaseFile:: goInside(){}

BaseFile::~BaseFile(){}

//
// Created by elklai on 12/11/17.
//

