#ifndef FILES_H_
#define FILES_H_
using namespace std;
#include <string>
#include <vector>

class BaseFile {
private:
    string name;

public:
    BaseFile(string name);
    string getName() const;
    void setName(string newName);
    virtual int getSize() = 0;
    virtual string toPrint();
    virtual void changeParent(BaseFile* newParent);
    virtual BaseFile* goInside();
    virtual ~BaseFile();

};

class File : public BaseFile {
private:
    int size;

public:
    File(string name, int size); // Constructor
    int getSize(); // Return the size of the file
    virtual string toPrint();
    virtual void changeParent(BaseFile* newParent);
    virtual BaseFile* goInside();
    ~File();
    File(const File &file);
    File& operator=(const File &other);
};

class Directory : public BaseFile {
private:
    vector<BaseFile*> children;
    Directory *parent;

public:
    Directory(string name, Directory *parent); // Constructor
    Directory *getParent() const; // Return a pointer to the parent of this directory
    void setParent(Directory *newParent); // Change the parent of this directory
    void addFile(BaseFile* file); // Add the file to children
    void removeFileUndeep(string name);
    void removeFile(string name); // Remove the file with the specified name from children
    void removeFile(BaseFile* file); // Remove the file from children
    void sortByName(); // Sort children by name alphabetically (not recursively)
    void sortBySize(); // Sort children by size (not recursively)
    void sortChildren(bool bySize);//go to the correct sort
    vector<BaseFile*> getChildren(); // Return children
    int getSize(); // Return the size of the directory (recursively)
    string getAbsolutePath();  //Return the path from the root to this
    virtual Directory* goInside();

    //our functions
    virtual string toPrint();
    void printChildren();
    BaseFile* findChildren(string name);

    static bool compByName (BaseFile* b1,BaseFile* b2);
    static bool compBySize(BaseFile* b1, BaseFile* b2);
    virtual ~Directory();//destructor
    Directory (const Directory &other);//copy constructor
    Directory (Directory &&other);//move constructor
    Directory& operator= (const Directory &other);//copy assignment
    Directory& operator= (Directory &&other);//move assignment
    virtual void changeParent(Directory* newParent);
    void copy(const Directory &other);
    void clear();
};

#endif