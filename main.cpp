#include "AVL.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    AVLTreeClass myTree;
    string line;
    int commands = 0;
    if (getline(cin, line)){
        stringstream stream(line);
        stream >> commands;
    }
    int completedCommands = 0;
    while (completedCommands < commands){
        if (!getline(cin, line)){
            break;
        }
        stringstream stream(line);
        string command;
        stream >> command;
        if (command == "insert"){
            string name, gatorID;
            getline(stream, name, '"');
            getline(stream, name, '"');
            stream >> gatorID;
            myTree.insert(name, gatorID);
        }else if (command == "remove"){
            string gatorID;
            stream >> gatorID;
            myTree.remove(gatorID);
        }else if (command == "search"){
            string identifier;
            if (stream.peek() == ' '){
                stream.ignore();
            }if (stream.peek() == '"'){
                getline(stream, identifier, '"');
                getline(stream, identifier, '"');
                myTree.searchName(identifier);
            } else{
                stream >> identifier;
                myTree.searchID(identifier);
            }
        }else if (command == "printInorder"){
            myTree.printInorder();
        }else if (command == "printPreorder"){
            myTree.printPreorder();
        }else if (command == "printPostorder"){
            myTree.printPostorder();
        }else if (command == "printLevelCount"){
            myTree.getTreeLevelCount(myTree.root);
        } else if (command == "removeInorder"){
            int y;
            stream >> y;
            //cout << "are you reaching removeInorder";
            myTree.removeInorder(y);
        }else{
            cout << "unsuccessful";
        }
        completedCommands += 1;
    }
    return 0;
}