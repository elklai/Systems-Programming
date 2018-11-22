//
// Created by elklai on 12/11/17.

#include "../include/Commands.h"
using namespace std;//why does we need to include it when it already been included in files


BaseCommand::BaseCommand(string args):args(args){}


string BaseCommand::getArgs() {
    return args;
}


void BaseCommand:: execute(FileSystem & fs){}


string BaseCommand::  toString(){
    return "base";
}


BaseCommand:: ~BaseCommand(){}



vector<string> BaseCommand:: dividePath(string a){//make a vector of BaseFile names
    vector<string> divideString;
    if(a.length()==0)
        return divideString;
    size_t firstPos = 0;
    size_t secondPos = a.find_first_of("/");
    if( a[0] == '/' )
    {
        divideString.push_back( "root" );
        firstPos = secondPos + 1;
        secondPos = a.find_first_of( "/" , firstPos );
        if(a.length() == 1)
            return divideString;
    }

    while (secondPos != string::npos){
        divideString.push_back( a.substr( firstPos , secondPos - firstPos ) );
        firstPos = secondPos + 1;
        secondPos = a.find_first_of("/" , firstPos);
    }

    divideString.push_back( a.substr( firstPos ) );
    return divideString;
}

    Directory& BaseCommand::chekAndGoTo(FileSystem & fs,vector <string> vec){//return a referance to the Directory in the path
    bool found;
    if(vec.empty())
        return fs.getWorkingDirectory();
    Directory* currentDyrectoryP=&(fs.getWorkingDirectory());
    if(vec[0]=="root")
        currentDyrectoryP=&(fs.getRootDirectory());

    //vector<string>::iterator it;
    //for(it=vec.begin();it<(vec.end()-- );it++)
        int i;
    for(i=0;i<vec.size()-1;i++)
    {
        if ((vec[i]) == "..") {
            currentDyrectoryP=((*currentDyrectoryP).getParent());
        }
        else if(vec[i]=="root"){}
        else {
            string current = (vec[i]);
            found=false;
            int j;
            for( j = 0 ; (j < currentDyrectoryP->getChildren().size() ) && ( !found) ; j++ )
            {
                if (currentDyrectoryP->getChildren()[j]->getName() == current) {
                    BaseFile* mem=(currentDyrectoryP->getChildren()[j])->goInside();
                    if(mem!=0) {
                        currentDyrectoryP = dynamic_cast<Directory*> (mem);
                        found = true;
                    }
                    else
                        return *currentDyrectoryP;
                }
            }
            if(!found)
                return *currentDyrectoryP;

        }
    }
    return *currentDyrectoryP ;
}
