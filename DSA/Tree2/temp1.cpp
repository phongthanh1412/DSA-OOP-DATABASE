#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct compressedNode {
    vector<compressedNode*> children;
    vector<string> edgeLabel;
    bool isWord;

    compressedNode(bool isWord = false) {
        this->isWord = isWord;
        children.resize(26, NULL);
        edgeLabel.resize(26);
    }
};

compressedNode* createTrie() {
    return new compressedNode();
}

string strCopy(const string& str, int index) {
    return str.substr(index);
}

void insert(compressedNode* pRoot, const string& word) {
    compressedNode* current = pRoot;
    int wordIndex = 0;

    while (wordIndex < word.length()) {
        int charIndex = word[wordIndex] - 'a';

        // Kiểm tra xem cạnh hiện tại có tồn tại không
        if (!current->edgeLabel[charIndex].empty()) {
            string label = current->edgeLabel[charIndex];
            int labelIndex = 0;

            // Duyệt qua cạnh hiện tại để tìm đoạn khớp
            while (wordIndex < word.length() && labelIndex < label.length() &&
                   word[wordIndex] == label[labelIndex]) {
                ++wordIndex;
                ++labelIndex;
            }

            // Nếu đã duyệt hết cạnh (khớp hoàn toàn)
            if (labelIndex == label.length()) {
                current = current->children[charIndex];
            } else {
                // Xử lý trường hợp tách nút:
                string remainingLabel = label.substr(labelIndex);
                compressedNode* splitNode = new compressedNode();

                // Tạo một nút mới để lưu đoạn chưa khớp
                splitNode->edgeLabel[remainingLabel[0] - 'a'] = remainingLabel;
                splitNode->children[remainingLabel[0] - 'a'] = current->children[charIndex];

                // Cập nhật cạnh hiện tại
                current->children[charIndex] = splitNode;
                current->edgeLabel[charIndex] = label.substr(0, labelIndex);

                // Thêm đoạn còn lại của từ
                if (wordIndex < word.length()) {
                    string remainingWord = word.substr(wordIndex);
                    splitNode->edgeLabel[remainingWord[0] - 'a'] = remainingWord;
                    splitNode->children[remainingWord[0] - 'a'] = new compressedNode(true);
                } else {
                    splitNode->isWord = true;
                }
                return;
            }
        } else {
            // Nếu cạnh không tồn tại, thêm đoạn từ còn lại
            current->edgeLabel[charIndex] = word.substr(wordIndex);
            current->children[charIndex] = new compressedNode(true);
            return;
        }
    }

    // Đánh dấu từ đã kết thúc tại nút cuối
    current->isWord = true;
}


compressedNode* findPrefixNode(compressedNode* pRoot, const string& prefix) {
    compressedNode* trav = pRoot;
    int i = 0;

    while (i < prefix.length() && !trav->edgeLabel[prefix[i] - 'a'].empty()) {
        int index = prefix[i] - 'a';
        string label = trav->edgeLabel[index];
        int j = 0;

        while (j < label.length() && i < prefix.length() && label[j] == prefix[i]) {
            ++i;
            ++j;
        }

        if (j < label.length()) return NULL;
        trav = trav->children[index];
    }

    return i == prefix.length() ? trav : NULL;
}

void lookUpWords(compressedNode* node, string& currentWord, vector<string>& list, int k, int& count_comparisons) {
    count_comparisons++;
    if (!node || list.size() >= k) return;

    if (node->isWord) {
        list.push_back(currentWord);
        count_comparisons++;
        if (list.size() >= k) return;
    }

    
    for (int i = 0; count_comparisons++, i < 26; ++i) {
        count_comparisons++;
        if (node->children[i]) {
            currentWord += node->edgeLabel[i];
            lookUpWords(node->children[i], currentWord, list, k, count_comparisons);
            currentWord.erase(currentWord.size() - node->edgeLabel[i].size());
            count_comparisons++;
            if (list.size() >= k) return;
        }
    }
}

void readTest(string fileName, vector<string>& prefixes) {
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "Test 'a's not found.\n";
        return;
    }

    string line;
    while (inFile >> line) {
        prefixes.push_back(line);
    }
}

compressedNode* readWordList(string fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "File not found.\n";
        return NULL;
    }

    compressedNode* dictionary = createTrie();
    string line;
    while (inFile >> line) {
        insert(dictionary, line);
    }
    return dictionary;
}

void calculateForLookUp(compressedNode* pRoot) {
    int k;
    cout << "Enter the number of words to suggest: ";
    cin >> k;

    int testcases[] = { 100, 500, 1000 };
    vector<string> prefixes; // Initialise prefixes
    readTest("test.txt", prefixes);

    for (int prefixes_size : {100, 500, 1000}) {
        cout << "Testing with " << prefixes_size << " prefixes:\n";

        auto start = high_resolution_clock::now();
        for (int i = 0; i < prefixes_size; ++i) {
            compressedNode* node = findPrefixNode(pRoot, prefixes[i]);
            if (node) {
                vector<string> list;
                string currentWord = prefixes[i];
                int count_comparisons = 0;
                lookUpWords(node, currentWord, list, k, count_comparisons);
            }
        }
        auto end = high_resolution_clock::now();
        cout << "Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

        int total_comparisons = 0;
        for (int i = 0; i < prefixes_size; ++i) {
            compressedNode* node = findPrefixNode(pRoot, prefixes[i]);
            if (node) {
                vector<string> list;
                string currentWord = prefixes[i];
                int count_comparisons = 0;
                lookUpWords(node, currentWord, list, k, count_comparisons);
                total_comparisons += count_comparisons;
            }
        }
        cout << "Total number of comparisons: " << total_comparisons << endl;
        cout << "-------------------------------------------------\n";
    }
}

int main() {
    compressedNode* pRoot = readWordList("dictionary.txt");
    if (!pRoot) return 1;

    vector<string> prefixes;
    readTest("test.txt", prefixes);

    calculateForLookUp(pRoot);

    return 0;
}
