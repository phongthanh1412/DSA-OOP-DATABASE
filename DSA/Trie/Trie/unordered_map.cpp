#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
using namespace std::chrono;
using namespace std;

// Build the prefix map from the dictionary
unordered_map<string, vector<string>> buildPrefixMap(string fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "File is not found." << endl;
        return {};
    }

    unordered_map<string, vector<string>> prefixMap;
    string word;
    while (inFile >> word) {
        string prefix;
        for (char c : word) {
            prefix += c;
            prefixMap[prefix].push_back(word);
        }
    }
    inFile.close();
    return prefixMap;
}

// Read all test cases from file
template<typename T>
void readTest(string fileName, T& prefixes) {
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "Test cases are not found." << endl;
        return;
    }
    string line;
    while (inFile >> line) {
        prefixes.push_back(line);
    }
    inFile.close();
}

// Get suggestions for a prefix
vector<string> lookUpWords(const unordered_map<string, vector<string>>& prefixMap, const string& prefix, int k, int& count_comparisons) {
    count_comparisons++;
    if (prefixMap.find(prefix) != prefixMap.end()) {
        const vector<string>& suggestions = prefixMap.at(prefix);
        return vector<string>(suggestions.begin(), suggestions.begin() + min(k, (int)suggestions.size()));
    }
    return {};
}

// Print the suggestions
void printWords(const vector<string>& list, const string& prefix) {
    if (list.empty()) {
        cout << "Your prefix does not exist in the dictionary.\n" << endl;
    }
    else {
        cout << "Words with prefix '" << prefix << "':" << endl;
        for (const string& word : list) {
            cout << word << endl;
        }
    }
}

// Calculate total time and comparisons for look-up
void calculateForLookUp(const unordered_map<string, vector<string>>& prefixMap) {
    int k = 0;
    cout << "Enter the number of words to be suggested: ";
    cin >> k;
    cout << "-------------------------------------------------\n";

    int testcase[] = { 100,500,1000 };
    vector<string> prefixes;
    readTest("test.txt", prefixes);

    for (int i = 0; i < 3; i++) {
        int prefixes_size = testcase[i];
        cout << "Testing with " << prefixes_size << " prefixes:" << endl;

        // Calculate total time for suggesting k words from the dictionary 
        auto start = high_resolution_clock::now();
        for (int j = 0; j < prefixes_size && j < (int)prefixes.size(); j++) {
            const string& prefix = prefixes[j];
            int count_comparisons = 0;
            lookUpWords(prefixMap, prefix, k, count_comparisons);
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << "Total time to find words with " << prefixes_size << " prefixes: " << duration << " ms" << endl;

        // Calculate total number of comparisons for suggesting k words from the dictionary 
        int total_comparisons = 0;
        for (int j = 0; j < prefixes_size && j < (int)prefixes.size(); j++) {
            const string& prefix = prefixes[j];
            int count_comparisons = 0;
            lookUpWords(prefixMap, prefix, k, count_comparisons);
            total_comparisons += count_comparisons;
        }
        cout << "Total number of comparisons: " << total_comparisons << endl;
        cout << "-------------------------------------------------\n";
    }
}

void checkLookUpWords(const unordered_map<string, vector<string>>& prefixMap) {
    int k = 0;
    cout << "Enter number of words to be suggested: ";
    cin >> k;

    string prefix;
    cout << "Enter a prefix: ";
    cin >> prefix;

    int count_comparisons = 0; // Initialize count comparisons
    vector<string> suggestions = lookUpWords(prefixMap, prefix, k, count_comparisons);
    printWords(suggestions, prefix);
}

bool isExist(const unordered_map<string, vector<string>>& prefixMap, const string& word) {
    string prefix;
    for (char c : word) {
        prefix += c;
        if (prefixMap.find(prefix) == prefixMap.end()) {
            return false;  
        }
    }

    const vector<string>& words = prefixMap.at(prefix);
    return find(words.begin(), words.end(), word) != words.end();
}

void addWord(unordered_map<string, vector<string>>& prefixMap, const string& word) {

    string prefix;
    for (char c : word) {
        prefix += c;
        prefixMap[prefix].push_back(word);
    }
    cout << "Word '" << word << "' has been added to the dictionary." << endl;
}

void deleteWord(unordered_map<string, vector<string>>& prefixMap, const string& wordDelete) {

    string prefix;
    if (!isExist(prefixMap, wordDelete)) {
        cout << "The word '" << wordDelete << "' does not exist in the Trie.\n";
        return;
    }
    for (char c : wordDelete) {
        prefix += c;
        auto& words = prefixMap[prefix];
        auto it = find(words.begin(), words.end(), wordDelete);
        if (it != words.end()) {
            words.erase(it);
        }
    }
    cout << "Word '" << wordDelete << "' has been deleted from the dictionary." << endl;
}

int main() {

    unordered_map<string, vector<string>> prefixMap = buildPrefixMap("word_alpha.txt");

    if (prefixMap.empty()) {
        return 1;
    }

    cout << "TEST WITH ONE TEST CASE: \n";
    // Look up words
    checkLookUpWords(prefixMap);

    // Add a word to the Trie
    string wordToAdd;
    cout << "Enter a word to add to the dictionary: ";
    cin >> wordToAdd;
    addWord(prefixMap, wordToAdd);

    // Delete a word from Trie 
    string wordToRemove;
    cout << "Enter a word to remove from the dictionary: ";
    cin >> wordToRemove;
    deleteWord(prefixMap, wordToRemove);
    

    cout << "-----------------------------------------------------------\n";
    cout << "-----------------------------------------------------------\n";
    cout << "TEST WITH LISTS OF TEST CASES TO CALCULATE TIME AND COMPARISIONS: \n";
    for (int i = 0; i < 4; i++) {
        // Calculate time for looking up in 4 situations: 1, 5, 10, 15 words
        calculateForLookUp(prefixMap);
    }  
    
    return 0;
}