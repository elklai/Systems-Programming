//
// Created by elklai on 12/11/17.
//
#include "../include/Commands.h"

PwdCommand:: PwdCommand(string args):BaseCommand(args){

}


void PwdCommand:: execute(FileSystem & fs){
     cout<<fs.getWorkingDirectory().getAbsolutePath();



} // Every derived class should implement this function according to the document (pdf)


string PwdCommand:: toString(){
    return "Pwd";//to check what this function need to do

}