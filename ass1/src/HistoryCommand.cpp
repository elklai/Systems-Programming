
#include "../include/Commands.h"

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> & history):BaseCommand(args) , history(history){

}// maybe history was not initial as should expected;

void HistoryCommand::execute(FileSystem & fs){
    int counter = 0;
    vector<BaseCommand*> ::const_iterator it;
    for( it = this->history.begin() ; it < this->history.end() ; it++ )
    {
        cout << counter + "\t" + (*it)->toString() + " " + (*it)->getArgs() +"\n";
        counter++;
    }

}
string HistoryCommand:: toString(){
    return "History";
}





//
// Created by elklai on 12/11/17.
//

