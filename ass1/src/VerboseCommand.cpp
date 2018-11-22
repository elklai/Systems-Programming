#include "../include/Commands.h"
#include "../include/GlobalVariables.h"

VerboseCommand :: VerboseCommand(string args):BaseCommand(args){
}


void VerboseCommand:: execute(FileSystem & fs){
    string::size_type sz;
    int verboseNumber = std::stoi ( this->getArgs() , &sz );
    verbose = verboseNumber;
}


string VerboseCommand:: toString(){
    return "Verbose";
}
//
// Created by elklai on 12/11/17.
//

