
#include "../include/Commands.h"

LsCommand::LsCommand(string args):BaseCommand(args){

}


void LsCommand:: execute(FileSystem & fs) {

    bool bySize = false;
    BaseFile *mem;
    int i;
    Directory *dir;
    vector<string> path;
    string fixedArgs = this->getArgs();
    if (fixedArgs == "") {
        dir = &fs.getWorkingDirectory();
        dir->sortByName();
        dir->printChildren();
        return;
    } else if (fixedArgs[0] == '-') {
        bySize = true;
        if(fixedArgs.length() >2 )
            fixedArgs = fixedArgs.substr(3);
        else {
            fixedArgs = "";
            dir = &fs.getWorkingDirectory();
            dir->sortBySize();
            dir->printChildren();
            return;
        }
    }
    path = this->dividePath(fixedArgs);
    if (path.size() == 1) {
        if (path[0] == "root") {
            dir = &fs.getRootDirectory();
        } else if (path[0] == "..") {
            dir = fs.getWorkingDirectory().getParent();
        } else {
            mem = fs.getWorkingDirectory().findChildren(path[0])->goInside();
            if (mem == 0) {
                cout << "The system cannot find the path specified";
                return;
            } else
                dir = (dynamic_cast<Directory *> (mem));
        }
    } else {
        dir = &(this->chekAndGoTo(fs, path));
        bool found = false;
        for (i = 0; (i < path.size()) && !found; i++)
            if (path[i] == dir->getName())
                found = true;

        mem = fs.getWorkingDirectory().findChildren(path[i])->goInside();
        if (mem == 0) {
            cout << "The system cannot find the path specified";
            return;

        } else
            dir = (dynamic_cast<Directory *> (mem));
    }
    if (bySize)
        dir->sortBySize();
    else
        dir->sortByName();

    dir->printChildren();
}



//      !!!!!!
//      bySize = this->getArgs().substr(0, 2) == "-s";
//      if (bySize)
//          fixedArgs = this->getArgs().substr(3);
//      vector<string> path = this->dividePath(fixedArgs);
//      if (path.size() == 0) {
//          fs.getWorkingDirectory().sortBySize();
//          fs.getWorkingDirectory().printChildren();
//      }
//      else if (path.size() == 1) {
//          if(path[0]=="root"){
//              fs.getRootDirectory().sortBySize();
//              fs.getRootDirectory().printChildren();
//          }
//          else if(path[0]==".."){
//              fs.getWorkingDirectory().getParent()->sortChildren(bySize);
//              fs.getWorkingDirectory().getParent()->printChildren();
//          }
//          else{
//              mem=fs.getWorkingDirectory().findChildren(path[0]);
//              if(mem== 0) {
//                  cout << "The system cannot find the path specified";
//                  return;
//              }
//              else if(mem->goInside()==0){
//                  cout<<"The system cannot find the path specified";
//                  return;
//              }
//              else{
//                  dynamic_cast<Directory*>(mem)->sortChildren(bySize);
//                  dynamic_cast<Directory*>(mem)->printChildren();
//              }
//          }
//      }
//      else {
//          dir = &(this->chekAndGoTo(fs, path));
//          for (i = 0; path[i] == dir->getName(); i++) {}
//          mem = fs.getWorkingDirectory().findChildren(path[i + 1]);
//          if (mem == 0) {
//              cout << "The system cannot find the path specified";
//              return;
//          } else if (mem->goInside() == 0) {
//              cout << "The system cannot find the path specified";
//              return;
//          } else {
//                dynamic_cast<Directory *>(mem)->sortChildren(bySize);
//                dynamic_cast<Directory *>(mem)->printChildren();
//            }
//        }
//    }
//}


string LsCommand::toString(){
    return "Ls";
}

//
// Created by elklai on 12/11/17.
//

