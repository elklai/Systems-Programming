#include "../include/Files.h"
#include <algorithm>
#include <iostream>
#include "../include/GlobalVariables.h"

using namespace std;//why does we need to include it when it already been included in files



Directory::Directory(string name, Directory *parent):BaseFile(name) , children(), parent(parent)
{
    //children = *(new vector<BaseFile*>());
    //maybe we need to initial vector
} // Constructor


Directory* Directory::getParent() const{
    return parent;
} // Return a pointer to the parent of this directory


void Directory:: setParent(Directory *newParent){
    parent=newParent;
} // Change the parent of this directory


void Directory:: addFile(BaseFile* file){

    bool found = false;
    for( int i = 0 ; i < children.size() && !found ; i++)
    {
        if(file->getName() == children[i]->getName())
            found = true;
    }
    if(!found) {
        children.push_back(file);

    }
} // Add the file to children

//to check this function(many misunderstandings)
void Directory:: removeFile(string name){
    vector<BaseFile*>::iterator it;//to check what "std" means and when we need to use it
    for(it=children.begin(); it < children.end(); it++){
        if(((*it)->getName())==name)
        {
            //[["*it" is wrong - should be "it->getName"]]
            delete *it;
            children.erase(it);
            return;
            //[[ You need to exit the loop here, by using "break". Note that after "children.erase(it)", "it" is no longer valid]]
            }
        }
    cout << " File does not exists";
    } // Remove the file with the specified name from children


    void Directory::removeFile(BaseFile* file){

        for(int i = 0 ; i < children.size() ; i++ )
        {
            if(children[i] == file ) {
                delete (children[i]);
                children.erase(children.begin()+i);
                return;
            }
        }
        cout << " File does not exists";

    } // Remove the file from children


    void Directory::sortByName(){
        sort(children.begin(),children.end(),compByName);

    } // Sort children by name alphabetically (not recursively)


    void Directory::sortBySize() {
        sort(children.begin(), children.end(), compBySize);
    }
    // Sort children by size (not recursively)


    void Directory::sortChildren(bool bySize){
        if(bySize)
            this->sortBySize();
        else
            this->sortByName();
    }


    vector<BaseFile*> Directory:: getChildren() {
        return this->children;
    }
       // [[ Just note that a copy constructor is used here, returning a copy of the vector "children"]]
         // Return children


    int Directory:: getSize(){
        int totalSize=0;
        std::vector<BaseFile*>::iterator it;

        for(it=children.begin(); it < children.end(); it++)
            totalSize+=(*it)->getSize();
       // [[Here too should be "it->getSize()"

        return totalSize;
    } // Return the size of the directory (recursively)


    string Directory:: getAbsolutePath(){
        string absPath;
        if(parent)
            absPath = parent->getAbsolutePath() + "/" +this->getName();
        else
            absPath = "/";
        return absPath;
    }  //Return the path from the root to this

    bool Directory:: compByName(BaseFile* b1, BaseFile* b2) {
        string s1=b1->getName();
        string s2=b2->getName();
        return (s1.compare(s2)<=0);
    }



    bool Directory:: compBySize(BaseFile* b1, BaseFile* b2) {

        return (b1->getSize() <= b2->getSize() );

    }



        string Directory:: toPrint(){
            return ("DIR    "+ this->getName() +"   " );
        }


    void Directory::printChildren() {
        //vector<BaseFile*>::iterator it;
        //for(it=this->getChildren().begin();it<this->getChildren().end();it++){
        //    (*it)->toPrint();
         //   cout<<"\n";
        //}
        for(int i=0;i<this->getChildren().size();i++){
            cout << this->getChildren()[i]->toPrint() ;
            cout << this->getChildren()[i]->getSize();
            cout<<"\n";
        }
    }

        BaseFile* Directory:: findChildren(string name){
            if( this->getChildren().size() == 0)
                return nullptr;
            //vector <BaseFile*>::iterator it;
            for(int i=0;i<this->getChildren().size();i++){
            //for (it =this->getChildren().begin(); it <(this->getChildren().end()); it++) {//found in remove file also consider different function
            //    if ((*(it))->getName()==name )
             //       return *it;
            if(this->getChildren()[i]->getName()==name)
                return this->getChildren()[i];
            }
            return nullptr;
        }

        void Directory::removeFileUndeep(string name)
        {
            for(int i=0;i<this->children.size();i++)
                if(children[i]->getName()==name){
                    children.erase(children.begin()+i);
                    return;
                }
        }
        void Directory:: changeParent(Directory* newParent){
                this->setParent(newParent);
        }


        Directory* Directory::goInside(){
            return this;
        }


        void Directory::copy(const Directory &other) {
            vector<BaseFile*>::const_iterator it;//to check what "std" means and when we need to use it
            this->parent = nullptr;
            for(it=other.children.begin();it<other.children.end();it++) {
                BaseFile* current(*it);//ron:to understand why it need to be written in to different line!
                (this->children).push_back(current);
            }
        }


    void Directory::clear()
    {
        this->parent = nullptr;
        vector<BaseFile*>::iterator it;//to check what "std" means and when we need to use it
        for(it=children.begin();it<children.end();it++)
            delete (*it);
    }


    Directory::~Directory()
    {
        if( ( verbose == 3 ) || ( verbose ==1) )
        {
            cout << "Directory::~Directory()";
        }
        this->clear();
    }
        //destructor


    Directory:: Directory(const Directory &other):BaseFile(other.getName()) , children() , parent() {////////////////////!!need to fix this function we dont know how to divide the vector
        if( ( verbose == 3 ) || ( verbose ==1) )
        {
            cout << "Directory:: Directory(const Directory &other) \n";
        }
        this->copy(other);
    }//copy constructor


    Directory:: Directory(Directory &&other):BaseFile(other.getName()){//rule of five later
        //Directory:: Directory(Directory &&other): parent(std::move(other.parent)), children(std::move(other.children){} ]]
        // (!!it may be correct need to check move function!)
        if( ( verbose == 3 ) || ( verbose ==1) )
        {
            cout << "Directory:: Directory(Directory &&other) \n";
        }
        this->parent=other.getParent();
        this->children=other.children;
        vector<BaseFile*> temp;
        other.parent= nullptr;
        other.children=temp;
        delete &other;
    }//move constructor


    Directory& Directory:: operator= (const Directory &other){
        if( ( verbose == 3 ) || ( verbose ==1) )
        {
            cout << "Directory& Directory::operator=(const Directory &other) \n";
        }
        if(this!= &other){
            this->clear();
            this->copy(other);

        }
        return *this;
    }//copy assignment


    Directory& Directory:: operator= (Directory &&other) {
        if( ( verbose == 3 ) || ( verbose ==1) )
        {
           cout << "Directory& Directory::operator=(Directory &&other) \n";
        }

        if (this != &other) {
            this->clear();
            this->setName(other.getName());
            this->parent = other.getParent();
            this->children = other.children;
            //to check how i prevent memory problems:here is an idea:

        }
        return *this;
        //move assignment//rule of five later
    }
//
// Created by elklai on 12/11/17.
//
