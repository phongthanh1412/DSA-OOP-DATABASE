#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

struct TrieNode {
    TrieNode* child[26];
    bool isWord;

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            child[i] = NULL;
        }
        isWord = false;
    }
};
// Add one word into the Trie

void insert(TrieNode* pRoot, const string& word) {
    TrieNode* node = pRoot;
    for (char c : word) {
        int idx = c - 'a';
        if (!node->child[idx]) {
            node->child[idx] = new TrieNode();
        }
        node = node->child[idx];
    }
    node->isWord = true;
}

// Check whether the given word exists in the Trie (return a TrieNode* value)
TrieNode* findPrefixNode(TrieNode* root, const string& prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        int idx = c - 'a';
        if (!node->child[idx]) {
            return NULL;
        }
        node = node->child[idx];
    }
    return node;
}

// Check whether the given word exists in the Trie (return a boolean value)
bool isExisted(TrieNode* pRoot, const string& word) {
    TrieNode* node = pRoot;
    for (char c : word) {
        int idx = c - 'a';
        if (!node->child[idx]) {
            return false;
        }
        node = node->child[idx];
    }
    return node->isWord;
}

// Check if the current node has children or not
bool isLeaf(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->child[i]) {
            return false;
        }
    }
    return true;
}

// Print words in the Trie 
void printWords(vector<string> list, string prefix) {
    if (list.empty()) cout << "Your prefix (word) does not exist in Trie.\n" << endl;
    else {
        cout << "Words with prefix '" << prefix << "':" << endl;
        for (const string& word : list) {
            cout << word << endl;
        }
    }
}

// Read dictionary to create list of words
TrieNode* readWordList(string fileName) {
    ifstream inFile(fileName);
    if (inFile.eof()) {
        cout << "File is not found.";
        return NULL;
    }
    string line;
    TrieNode* dictionary = new TrieNode();
    while (inFile >> line) {
        insert(dictionary, line);
    }
    inFile.close();
    return dictionary;
}

// Read all words in test.txt to create test cases
void readTest(string fileName, vector<string>& prefixes) {
    ifstream inFile(fileName);
    if (inFile.eof()) {
        cout << "Test cases are not found.";
        return;
    }
    string line;
    while (inFile >> line) {
        prefixes.push_back(line);
    }
    inFile.close();
}

// Look up k words in the Trie
void lookUpWords(TrieNode* node, string& currentWord, vector<string>& list, int k, int& count_comparisons) {
    count_comparisons++;
    if (!node || list.size() >= k) return;

    count_comparisons++;
    if (node->isWord) {
        list.push_back(currentWord);
        count_comparisons++;
        if (list.size() >= k) return;
    }

    for (int i = 0; count_comparisons++, i < 26; i++) {
        count_comparisons++;
        if (node->child[i]) {
            currentWord.push_back('a' + i);
            lookUpWords(node->child[i], currentWord, list, k, count_comparisons);
            currentWord.pop_back();
            count_comparisons++;
            if (list.size() >= k) {
                return;
            }
        }
    }
}

// Calculate total time and number of comparisons
void calculateForLookUp(TrieNode* pRoot) {
    int k = 0;
    cout << "Enter the number of words be suggested: ";
    cin >> k;
    cout << "-------------------------------------------------\n";

    int testcase[] = { 100, 500, 1000 };
    vector<string> prefixes; // Initialise prefixes
    readTest("test.txt", prefixes);

    for (int i = 0; i < 3; i++) {
        int prefixes_size = testcase[i];
        cout << "Testing with " << prefixes_size << " prefixes:" << endl;

        // Calculate total time for suggesting k words from the dictionary 
        auto start = high_resolution_clock::now();
        for (int j = 0; j < prefixes_size; j++) {
            const string& prefix = prefixes[j];
            TrieNode* node = findPrefixNode(pRoot, prefix);
            if (node) {
                vector<string> list;
                string currentWord = prefix;
                int count_comparisons = 0;
                lookUpWords(node, currentWord, list, k, count_comparisons);
            }
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << "Total time to find words with " << prefixes_size << " prefixes: " << duration << " ms" << endl;

        // Calculate total number of comparisons for suggesting k words from the dictionary 
        int total_comparisons = 0;
        for (int j = 0; j < prefixes_size; j++) {
            const string& prefix = prefixes[j];
            TrieNode* node = findPrefixNode(pRoot, prefix);
            if (node) {
                vector<string> list;
                string currentWord = prefix;
                int count_comparisons = 0;
                lookUpWords(node, currentWord, list, k, count_comparisons);
                total_comparisons += count_comparisons;
            }
        }
        cout << "Total number of comparisons: " << total_comparisons << endl;
        cout << "-------------------------------------------------\n";
    }   
}

void checkLookUpWords(TrieNode* pRoot) {
    int k = 0;
    cout << "Enter number of words to be suggested: ";
    cin >> k;

    // Search for words in dictionary
    string prefix;
    cout << "Enter a prefix: ";
    cin >> prefix;

    TrieNode* node = findPrefixNode(pRoot, prefix);
    if (!node) {
        cout << "Your prefix does not exist in the Trie.\n" << endl;
        return;
    }

    vector<string> list;
    string currentWord = prefix;
    int count_comparisons = 0; // Initialize count comparisons

    lookUpWords(node, currentWord, list, k, count_comparisons);

    printWords(list, prefix); // Print words found with the prefix
}

void checkAddWord(TrieNode* pRoot) {

    string wordAdd;
    cout << "Enter a word you want to add: ";
    cin >> wordAdd;

    auto start = high_resolution_clock::now();
    insert(pRoot, wordAdd);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count(); // Calculate time
    cout << "Time to add " << "'" << wordAdd << "'" << ": " << duration << " ms" << endl;

    //Check add word successfully
    if (isExisted(pRoot, wordAdd))
        cout << "Word '" << wordAdd << "' has been added successfully to the Trie.\n";
    else cout << "Failed to add word '" << wordAdd << "' to the Trie.\n";
}

// Delete one word
bool deleteWord(TrieNode* node, const string& word, int depth = 0) {
    if (!node) {
        return false;
    }

    if (depth == word.size()) {
        if (!node->isWord) {
            return false;
        }
        node->isWord = false;
        return isLeaf(node);
    }

    int idx = word[depth] - 'a';
    bool is_child_deleted = deleteWord(node->child[idx], word, depth + 1);

    if (is_child_deleted) {
        delete node->child[idx];
        node->child[idx] = NULL;
        return isLeaf(node);
    }
    return false;
}

void checkDeleteWord(TrieNode* pRoot) {

    string wordDelete;
    cout << "Enter a word you want to delete: ";
    cin >> wordDelete;

    // Check the existence of the word in the Trie
    if (isExisted(pRoot, wordDelete)) {
        auto start = high_resolution_clock::now();
        deleteWord(pRoot, wordDelete);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count(); // Calculate time
        cout << "Time to delete " << "'" << wordDelete << "'" << ": " << duration << " ms" << endl;
    }
    else {
        cout << "The '" << wordDelete << "' does not exist in the Trie.\n";
        return;
    }
    // Check delete word successfully
    if (!isExisted(pRoot, wordDelete))
        cout << "Word '" << wordDelete << "' has been deleteded successfully from the Trie.\n";
    else cout << "Failed to delete word '" << wordDelete << "' from the Trie.\n";
}

// Clear memory
void release(TrieNode* pRoot) {
    for (int i = 0; i < 26; i++) {
        if (pRoot->child[i]) {
            release(pRoot->child[i]);
        }
    }
    delete pRoot;
}

int main() {
    TrieNode* pRoot = readWordList("dictionary.txt");

    //// Look up words
    //checkLookUpWords(pRoot);

    ////Add a word to the Trie
    //checkAddWord(pRoot);

    ////Delete a word from Trie 
    //checkDeleteWord(pRoot);

    // Calculate time for looking up
    calculateForLookUp(pRoot);

    //Clear memory
    release(pRoot);
    return 0;
}