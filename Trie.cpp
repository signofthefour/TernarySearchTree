
// C++ implementation of search and insert 
// operations on Trie 
#include <bits/stdc++.h> 
using namespace std; 
  
const int ALPHABET_SIZE = 26; 
  
// trie node 
struct TrieNode 
{ 
    struct TrieNode *children[ALPHABET_SIZE];
  
    // isEndOfWord is true if the node represents 
    // end of a word 
    bool isEndOfWord; 
}; 
  
// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
    struct TrieNode *pNode =  new TrieNode; 
  
    pNode->isEndOfWord = false; 
  
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = NULL; 
  
    return pNode; 
} 
  
// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
    std::for_each(key.begin(), key.end(), [](char & c){
	    c = ::tolower(c);
    });
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a'; 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
} 
  
// Returns true if key presents in trie, else 
// false 
int searchUtil(struct TrieNode *&root, string key) 
{ 
    TrieNode *pCrawl = root; 

    std::for_each(key.begin(), key.end(), [](char & c){
        c = ::tolower(c);
    });
    for (int i = 0; i < key.length(); i++) 
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]) {
            return -1;
        }
        pCrawl = pCrawl->children[index];
    }
    if (pCrawl == NULL)
        if (pCrawl->isEndOfWord == true) {
            return 0;
        } else return 1;
    }

void search(TrieNode* rootTree, string text) {
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
        TrieNode* root = rootTree;
        int res = searchUtil(root, word);
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
            res = searchUtil(root, nextWord);
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
  
// Driver 
int main(int argc, char** argv) { 
    std::ifstream ifs;
    ifs.open(argv[1], std::ifstream::in);
    std::string temp;
    // Input keys (use only 'a' through 'z' 
    // and lower case) 

    TrieNode *root = getNode();
    while (getline(ifs, temp)) {
        int n = temp.length();
        char word[n + 1];
        strcpy(word, temp.c_str());
        insert(root, temp);
    }
  
    // Construct trie 
    // Search for different keys 
    std::ifstream textStream;
    textStream.open(argv[2], std::ifstream::in);
    std::string text;
    std::string tmp;
    while (getline(textStream, tmp)) {
        text += ' ' + tmp; 
    }
    search(root, text);
    return 0; 
} 
