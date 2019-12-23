#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>

using namespace std;

#define MAX  50

// Node of Ternary search tree
struct Node {
    char data;          // char in this node
    bool isEndOfWord;   // True if this node is contain a char in the end of one word
    Node *left, *eq, *right; // Point to the smaller, equa, right node respectively

    Node(char data);
};

// Create new Node in ternary search tree
Node::Node(char data) {
    this->data = data;
    this->isEndOfWord = false;
    this->eq = NULL;
    this->left = NULL;
    this->right = NULL;
}

void print(char* word) {
    std::cout << word << '\n';
}

class TernarySearchTree {
    Node* treeRoot;
    void traverseTSTUtil(Node* root, char* buffer, int depth, void (*op)(char*));
    void insertUtil(Node** root, char* word);
    int searchUtil(Node*& root, char* word);
public:
    void insert(char* word);
    void traverse(void (*op)(char*));
    void search(string text);
};

void TernarySearchTree::insert(char* word) {
    this->insertUtil(&(this->treeRoot), word);
}

void TernarySearchTree::traverse(void (*op)(char*)) {
    char BUFFER[MAX + 1];
    this->traverseTSTUtil(this->treeRoot, BUFFER, 0, op);
}

void TernarySearchTree::insertUtil(Node** root, char* word) {
    // Case: TST is empty
    if (*(root) == NULL) {
        *root  = new Node(*word);
    }
    // std::cout << (*root)->data <<'\n';
    // word < root->data: insert to the left
    if (*word < (*root)->data) {
        insertUtil(&((*root)->left), word);
    }

    // word > root->data: insert to the right
    else if (*word > (*root)->data) {
        insertUtil(&((*root)->right), word);
    }

    // word == root->data: insert to eq
    else {
        // current char in word is the same with the root's char in this position
        if (*(word  + 1)) {
            insertUtil(&((*root)->eq), word + 1);
        }
        // last character of word 
        else {
            (*root)->isEndOfWord = true;
        }
    }
}

void TernarySearchTree::traverseTSTUtil(Node* root, char* buffer, int depth, void (*op)(char*)) {
    if (root) {
        // travese to left
        traverseTSTUtil(root->left, buffer, depth, op);

        // store data to buffer
        buffer[depth] = root->data;

        if (root->isEndOfWord) {
            buffer[depth + 1] = '\0';
            op(buffer);
        }

        // traverse in eq
        traverseTSTUtil(root->eq, buffer, depth + 1, op);

        // traverse to right
        traverseTSTUtil(root->right, buffer, depth, op);
    }
}

void TernarySearchTree::search(string text) {
    stringstream ss(text);
    string temp;
    string key;
    int pos, tempLen, extractLen;

    while (ss >> temp) {
        pos = ss.tellg();
        tempLen = temp.length();
        char* word = new char[tempLen + 1];
        strcpy(word, temp.c_str());
        if ((64 >= word[0] && word[0] >= 33) || (91 <= word[0] && 96 >= word[0]) ||(123 <= word[0] && 126 <= word[0]))
            word += 1;
        if ((64 >= word[tempLen - 1] && word[tempLen - 1] >= 33) 
            || (91 <= word[tempLen - 1] && 96 >= word[tempLen - 1]) 
            ||(123 <= word[tempLen - 1] && 126 >= word[tempLen - 1]))
            word[tempLen - 1] = '\0';
        Node* root = this->treeRoot;
        int res = this->searchUtil(root, word);
        extractLen = 0;
        string key = temp;
        while (res == 1) {
            string next;
            ss >> next;
            int m = next.length();
            extractLen += m;
            char* nextWord = new char[m + 1];
            strcpy(nextWord, next.c_str());
            nextWord[m] = '\0';
            if ((64 >= nextWord[m - 1] && nextWord[m - 1] >= 33) 
                || (91 <= nextWord[m - 1] && 96 >= nextWord[m - 1]) 
                ||(123 <= nextWord[m - 1] && 126 >= nextWord[m -1]))
                nextWord[m - 1] = '\0';
            key += ' ' + string(nextWord);
            res = this->searchUtil(root, nextWord);
            if (nextWord) delete[] nextWord;
        }
        if (res == 0) {
            cout << setw(10) << "Found: " << key << '\n';
        }
        if (word) delete[] word;
        while(extractLen > 0) {
            ss.unget();
            --extractLen;
        }
    }
}

int TernarySearchTree::searchUtil(Node*& root, char* word) {
    while (root != NULL) {
        // search left
        if (*word < (root)->data) {
            root = root->left;
        }
        // search right
        else if (*word > (root)->data) {
            root = root->right;
        }
        
        // equa to
        else
        {
            if (*(word+1) == '\0') {
                if (root->isEndOfWord) {
                    return 0;
                }
                else if (root->eq->data == ' ') {
                    root = root->eq->eq;
                    return 1;
                }
                else return -1;
            }
            root = root->eq;
            word += 1;
        }
    }
    // to the end with nothing be found
    return -1;
}

int main(int argc, char** argv) {
    std::ifstream ifs;
    ifs.open(argv[1], std::ifstream::in);
    std::string temp;

    // Create TST
    TernarySearchTree* TST = new TernarySearchTree();
    while (getline(ifs, temp)) {
        int n = temp.length();
        char word[n + 1];
        strcpy(word, temp.c_str());
        TST->insert(word);
    }
    TST->traverse(print);
    std::ifstream textStream;
    textStream.open(argv[2], std::ifstream::in);
    std::string text;
    getline(textStream, text);
    TST->search(text);
    return 0;
}