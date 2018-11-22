

#include "../include/GlobalVariables.h"
#include "../include/FileSystem.h"
#include "../include/Commands.h"
#include "../include/Environment.h"

#include <string>
#include <vector>

using namespace std;

Environment:: Environment() : fs(), commandsHistory(*new vector<BaseCommand*>()){
}

void Environment:: start(){
    string inputCommand = "";
    string commandName;
    size_t found;
    cout << ( this->fs.getWorkingDirectory().getAbsolutePath()) + ">";
    getline( cin , inputCommand ); // recive new command

    while( inputCommand != "exit" )
    {
        if( ( verbose == 2 ) || (verbose == 3 ) )
            cout << inputCommand +"\n";
        found = inputCommand.find_first_of(" ");
        if( found != string::npos ) {
            commandName = inputCommand.substr(0, found);//divide string into command name + args
            inputCommand=inputCommand.substr(found+1);
        }
        else {
            commandName = inputCommand;
            inputCommand = "";
        }

        BaseCommand* thisCommand;
        if( commandName == "pwd" )
            thisCommand = new PwdCommand(inputCommand);
        else if(commandName == "cd" )
            thisCommand = new CdCommand(inputCommand);
        else if(commandName == "ls" )
            thisCommand = new LsCommand(inputCommand);
        else if(commandName == "mkdir" )
            thisCommand = new MkdirCommand(inputCommand);
        else if(commandName == "mkfile" )
            thisCommand = new MkfileCommand(inputCommand);
        else if(commandName == "cp" )
            thisCommand = new CpCommand(inputCommand);
        else if(commandName == "mv" )
            thisCommand = new MvCommand(inputCommand);
        else if(commandName == "rename" )
            thisCommand = new RenameCommand(inputCommand);
        else if(commandName == "rm" )
            thisCommand = new RmCommand(inputCommand);
        else if(commandName == "history" )
            thisCommand = new HistoryCommand(inputCommand , this->getHistory() );
        else if(commandName == "verbose" )
            thisCommand = new VerboseCommand(inputCommand);
        else if(commandName == "exec" )
            thisCommand = new ExecCommand(inputCommand , this->getHistory() );
        else
            thisCommand = new ErrorCommand(inputCommand);


        //build new baseCommand according to the command name

        thisCommand->execute( this->getFileSystem() );
        addToHistory( thisCommand );

        cout << ("\n");
        cout << (this->fs.getWorkingDirectory().getAbsolutePath()) + ">";

            getline(cin, inputCommand); // recive new command

    }

}


FileSystem& Environment:: getFileSystem(){
    return fs;

}	// Get a reference to the file system


void Environment:: addToHistory(BaseCommand *command){
    this->commandsHistory.push_back( command );
}	// Add a new command to the history



const vector<BaseCommand*>& Environment:: getHistory() const{
    return this->commandsHistory;
}// Return a reference to the history of commands




//destructor
Environment:: ~Environment()
{
    if( ( verbose == 3 ) || ( verbose ==1) )
    {
        cout << "Environment:: ~Environment()";
    }
    clear();
}


//copy constructor
Environment:: Environment( const Environment& env )
{
    if( ( verbose == 3 ) || ( verbose ==1) )
    {
        cout << "Environment:: Environment( const Environment& env )";
    }
    this->copy(env);
}


//copy assignment
Environment& Environment:: operator=( const Environment& env ){
    if( ( verbose == 3 ) || ( verbose ==1) )
    {
        cout << "Environment& Environment:: operator=( const Environment& env )";
    }
    if( this != &env )
    {
        this->clear();
        this->copy(env);
    }
    return *this;
}


//move constructor
Environment:: Environment( Environment&& env ){
    if( ( verbose == 3 ) || ( verbose ==1) )
    {
        cout << "Environment:: Environment( Environment&& env )";
    }
    FileSystem tmp;
    vector<BaseCommand*> tmp2;
    this->fs = env.fs;
    this->commandsHistory = env.getHistory();
    env.commandsHistory = tmp2;
    env.fs = tmp;

}


//move assignment
Environment& Environment:: operator=( Environment&& env ){
    if( ( verbose == 3 ) || ( verbose ==1) )
    {
        cout << "Environment& Environment:: operator=( Environment&& env )";
    }
    if( this != &env )
    {
        clear();
        this->fs = env.getFileSystem();
        this->commandsHistory = env.getHistory();

        FileSystem tmp;
        vector<BaseCommand*> tmp2;// could make memory leaks!!!!
        env.fs = tmp;
        env.commandsHistory = tmp2;
    }
    return *this;
}


void Environment:: clear(){
    delete (&this->fs);
    vector<BaseCommand*> ::iterator it;
    for( it = this->commandsHistory.begin() ; it < this->commandsHistory.end() ; it++){
        delete (*it);
    }
    delete (&commandsHistory);

    FileSystem tmp;
    vector<BaseCommand*> tmp2;
    this->fs = tmp;
    this->commandsHistory = tmp2;
}


void  Environment:: copy( const Environment& env){
    const FileSystem* tmp= (&(env.fs ));
    FileSystem current(*tmp);
    this->fs = current;

    vector<BaseCommand*> newVector = (*(new vector<BaseCommand*>()));
    vector<BaseCommand*> ::iterator it;
    for( it = this->commandsHistory.begin() ; it < this->commandsHistory.end() ; it++){
        BaseCommand* newCommand(*it);
        newVector.push_back( newCommand );
    }
    this->commandsHistory = newVector;

}
