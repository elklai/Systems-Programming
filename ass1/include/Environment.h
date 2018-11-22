#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Files.h"
#include "Commands.h"

#include <string>
#include <vector>

using namespace std;

class Environment {
private:
	vector<BaseCommand*> commandsHistory;
	FileSystem fs;

public:
	Environment();
	void start();
	FileSystem& getFileSystem(); // Get a reference to the file system
	void addToHistory(BaseCommand *command); // Add a new command to the history
	const vector<BaseCommand*>& getHistory() const; // Return a reference to the history of commands
	virtual ~Environment();
    Environment( const Environment& env );
    Environment& operator=( const Environment& env );
    Environment( Environment&& env );
    Environment& operator=( Environment&& env );
    void clear();
    void  copy( const Environment& env);

};

#endif