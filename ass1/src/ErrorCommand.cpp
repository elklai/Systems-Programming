#include "../include/Commands.h"



ErrorCommand:: ErrorCommand(string args): BaseCommand(args){
}



void ErrorCommand:: execute(FileSystem & fs){
    size_t found = this->getArgs().find_first_of(" ");

    cout << ( this->getArgs().substr( 0 , found) ) + ": Unknown command";
}



string ErrorCommand:: toString(){
    return "Error";
}
//
// Created by elklai on 12/11/17.
//

