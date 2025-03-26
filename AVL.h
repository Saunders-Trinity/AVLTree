using namespace std;
#include <string>
#include "iostream"
#include <regex>
#include <climits>
//if your looking at this. Dont copy this code directly, change it up -Thanks
//this code passes all cases except for Test 12: input validation - 8 digit IDs, no special characters, no duplicate IDs and Test 14: insert many, remove, removeInorder, search, printInorder, and printLevelCount (0/5)
//note that those are hidden test cases i couldnt figure out how to fix in time

struct TreeNode{
public:
    // store student info, left and right children, maybe the height + constructor
    string name;
    string gatorID;
    int treeHeight;
    int count;
    TreeNode* root;
    TreeNode *left;
    TreeNode *right;
    //make a constructor
    TreeNode( string& studentName,string& studentGatorID, int height = 1)
            : name(studentName), gatorID(studentGatorID), treeHeight(height), left(nullptr), right(nullptr) {}
};


class AVLTreeClass{//functions to be used in main
public:
    TreeNode* root;
    AVLTreeClass() : root(nullptr) {}

int getTreeHeight(TreeNode* &root){
    if(root == nullptr) {
        return 0;//tree height 0
    }else {
        //use recursion and amaan formula for tree height and edugator problem exampple
        int leftTree = getTreeHeight(root->left);
        int rightTree = getTreeHeight(root->right);
        return 1 + max(leftTree, rightTree); // height formula from class
    }
}
//prototype for tree search, follows edugator problem structute
TreeNode* insertStudent(TreeNode* &root, string &name, string &gatorId) {
    if (root == nullptr) {
        //cout << " insert reached here";
        cout << "successful" << endl;
        return new TreeNode(name, gatorId);
    }if (gatorId < root->gatorID) {
        root->left = insertStudent(root->left, name, gatorId);
    } else if (gatorId > root->gatorID) {
        root->right = insertStudent(root->right, name, gatorId);
    } else {
        cout << "unsuccessful" << endl;
        return root;
    }
    // balance  tree
    int balance = currentTreeBalance(root);
    if (balance < -1) {
        if (currentTreeBalance(root->right) > 0) {
            root->right = treeRotateRight(root->right);
        }
        return treeRotateLeft(root);
    } else if (balance > 1) {
        if (currentTreeBalance(root->left) < 0) {
            root->left = treeRotateLeft(root->left);
        }
        return treeRotateRight(root);
    }
    return root;
}

//working on balancing the tree, start from the root, going right and left and counting ndes on each side using height function
int currentTreeBalance(TreeNode* &root){
    int balance = 0;
    if(root == nullptr){
        balance = 0;
    }else{//get heigt function to see tree level then number
        balance = getTreeHeight(root->left) - getTreeHeight(root->right); //should return if the tree is unbalanced
    }
    return balance;
}

//rotation prototypes, used geekforgeeks for these 2 functions
TreeNode* treeRotateRight(TreeNode* two){
    //get the balance of the tree, if left side is heavier, rotate using reursion till balance is 0?
    TreeNode* one = two->left;//start position
    TreeNode* three = one->right;
    //move right
    one->right = two;
    two->left  = three;
    return one;
}

TreeNode* treeRotateLeft(TreeNode* one){
        //if right subtree is heavier, use recusrion to move nodes left till balacce is 0
    TreeNode* two = one->right;
    TreeNode* three = two->left;
    //move leftward
    two->left = one;
    one->right = three;
    return two;
}

TreeNode* findInorderSuccessor(TreeNode* root){
    //traverse the right subtree from the leftmost child node
    TreeNode* inorderSuccessor = root->right;
    while (inorderSuccessor->left != nullptr){
        inorderSuccessor = inorderSuccessor->left;
    }
    return inorderSuccessor;
}

    //protoype for getting tree levels
void getTreeLevelCount(TreeNode* root){
    int treeLevelCount = getTreeHeight( root);//this is causing issues
    cout  << treeLevelCount << endl;
}

void clear(TreeNode* &root){
    //destroy all nodes of the tree startign from root, then left to right
    if(root != nullptr){
        clear(root->left);
        clear(root->right);
        delete root;
        root = nullptr;
    }
}

//amman psudocode for recursive removal, help for remove Command, also follows edugaotor struct
TreeNode* removeHelperFunction(TreeNode* &root, const string &gatorID, bool  &success) {
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return root;
    } else if (gatorID < root->gatorID) {
        root->left = removeHelperFunction(root->left, gatorID, success);
    } else if (gatorID > root->gatorID) {
        root->right = removeHelperFunction(root->right, gatorID, success);
    } else {
        if ((root->left == nullptr) or (root->right == nullptr)){
            TreeNode *temp = root->left ? root->left : root->right;
            if (temp == nullptr){
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
            success = true;
        } else {
            TreeNode *temp = findInorderSuccessor(root);
            root->gatorID = temp->gatorID;
            root->name = temp->name;
            root->right = removeHelperFunction(root->right, temp->gatorID, success);
            int balance = currentTreeBalance(root);
            // If tree is right heavy negative = right heavy positive = left heavy
            if (balance < -1) {
                // If tree's right subtree is left heavy do left right
                if (currentTreeBalance(root->right) > 0) {
                    root->right = treeRotateRight(root->right);
                    return treeRotateLeft(root);
                } else {//left rotate
                    return treeRotateLeft(root);
                }
            }// Elseif tree is left heavy
            else if (balance > 1) {
                // If tree's left subtree is right heavy
                if (currentTreeBalance(root->left) < 0) {//left right
                    root->left = treeRotateLeft(root->left);
                    return treeRotateLeft(root);
                } else {
                    return treeRotateRight(root);
                }
            }
        }
       // return root;
    }
    return  root;
}

//actual remove command
void remove(const string &gatorID) {
    bool success = false;
    root = removeHelperFunction(root, gatorID, success);
    if (success) {
        //cout << "are you in remove" << endl;
        cout << "successful" << endl;
    }
}

void insert(string name, string gatorID){
    regex name_("^[a-zA-Z ]+$");
    regex id_("^[0-9]{8}$");
    if (regex_match(name, name_)){
        if (regex_match(gatorID, id_)){
            root = insertStudent(root, name, gatorID); // inserted if the name and id are
        }
    }else{
        cout << "unsuccessful" << endl;
    }
}

//helper for removing inorder, if root= null,return nothigng,search from target node from left to right
void removeInorderHelperFunction(TreeNode* &root, int &y, int &count) {
    if (root == nullptr) {
        return;
    }// traverse left tree
    removeInorderHelperFunction(root->left, y, count);
    if (count == y){
        bool success = false;//still giving issues
        removeHelperFunction(root, root->gatorID, success);
        if (success){
            cout << "successful" << endl;
        }
        y = INT_MAX;//makes sure not to delte too many nodes from tree
        return;
    }
    count++;
    // travrse right tree
    removeInorderHelperFunction(root->right, y, count);
}

void removeInorder(int y) {
    int count = 0;
    removeInorderHelperFunction(root, y, count);
}

void printPostOrderHelperFunction(TreeNode* &root, bool &first) {
    if (root != nullptr) {
    printPostOrderHelperFunction(root->left, first);
    printPostOrderHelperFunction(root->right, first);
    if (!first) {
        cout << ", ";
    }
    first = false;
    cout << root->name;
    }
}

//actual postorder command
void printPostorder() {
    bool first = true;
    printPostOrderHelperFunction(root, first);
    cout << endl;
}

void printPreorderHelperFunction(TreeNode* &root, bool &first) {
    if (root != nullptr) {
    if (!first) {
        cout << ", ";
    }
    first = false;
    cout << root->name;
    printPreorderHelperFunction(root->left, first);
    printPreorderHelperFunction(root->right, first);
    }
}
//preorder command
void printPreorder() {
    bool first = true;
    printPreorderHelperFunction(root, first);
    cout << endl;
}

//need to make print inoder helper for command
void printInorderHelpFunction(TreeNode* &root, bool &first) {
    if (root != nullptr) {
    printInorderHelpFunction(root->left, first);
    if (!first) {
        cout << ", ";
    }
    first = false;
    cout << root->name;
    printInorderHelpFunction(root->right, first);
    }
}

//for testing command
void printInorder() {
    bool first = true;
    printInorderHelpFunction(root, first);
    cout << endl;
}

void searchIDHelperFunction(TreeNode* &root, const string &gatorID){
    if (root == nullptr){
        //cout << "are you in search id << endl;
       cout << "unsuccessful" << endl;
       return;
    }if (root->gatorID == gatorID){
        cout << root->name << endl;
    } else if (gatorID > root->gatorID){
        return searchIDHelperFunction(root->right, gatorID);
    } else if (gatorID < root->gatorID){
        return searchIDHelperFunction(root->left, gatorID);
    }
}

void searchID(const string &gatorID){
    searchIDHelperFunction(root, gatorID);
}

void searchNameHelperFunction(TreeNode* &root, const string &name, bool &found){
    if (root == nullptr){
        return;
    }if (root->name == name){
        found = true;
        cout << root->gatorID << endl;
    }
    searchNameHelperFunction(root->left, name, found);
    searchNameHelperFunction(root->right, name, found);
}

//prototype for command test
void searchName(const string &name){
    bool found = false;
    searchNameHelperFunction(root, name, found);
    if (!found){
        //cout << "are you in search name";
        cout << "unsuccessful" << endl;
    }
}

};
