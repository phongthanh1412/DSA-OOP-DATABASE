#include <iostream>
#include <cstring>
using namespace std;

void computeLPSArray(char pattern[], int lps[], int size) {
    lps[0] = 0;
    int length = 0, i = 1;
    while (i < size) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if (length != 0) length = lps[length - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearching(char pattern[], char text[]) {
    int M = strlen(pattern);
    int N = strlen(text);
    int* lps = new int[M];
    computeLPSArray(pattern, lps, M);
    int i = 0, j = 0;
    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == M) {
            cout << "Pattern was found at index: " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < N && pattern[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    delete[] lps;
}

int main() {
    char text[] = "AABAACAADAABAABA";
    char pattern[] = "AABA";
    KMPSearching(pattern, text);
    return 0;
}