#include "../include/Commands.h"


ExecCommand:: ExecCommand(string args, const vector<BaseCommand *> & history): BaseCommand(args) , history(history){
}


void ExecCommand:: execute(FileSystem & fs){
    int counter = 0;
    string::size_type sz;
    int commandNumber = std::stoi ( this->getArgs() , &sz );

    vector<BaseCommand*> ::const_iterator it;
    for( it = this->history.begin() ; ( it < this->history.end() ) && ( counter < commandNumber ) ; it++ ){counter++;}
    (*it)->execute(fs);
}



string ExecCommand:: toString(){
    return "Exec";
}



//
// Created by elklai on 12/11/17.
//
