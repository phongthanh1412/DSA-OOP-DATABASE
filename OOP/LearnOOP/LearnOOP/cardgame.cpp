#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <iostream>
using namespace std;

class CardUtils {
public:
    static int cardToNumber(const string& card);
    static string numberToCard(int num);
    static int factorial(int n);
};

class PermutationUtils {
public:
    static vector<int> numberToPermutation(int k, int n);
    static int permutationToNumber(const vector<int>& perm);
};

class An {
public:
    vector<string> pick(const vector<string>& X);
};

class Binh {
public:
    string guess(const vector<string>& Y);
};

// Implementation of CardUtils
int CardUtils::cardToNumber(const string& card) {
    string rank = card.substr(0, card.length() - 1);
    char suit = card.back();

    int rankNum;
    if (rank == "J") rankNum = 9;
    else if (rank == "Q") rankNum = 10;
    else if (rank == "K") rankNum = 11;
    else if (rank == "A") rankNum = 12;
    else rankNum = stoi(rank) - 2;

    int suitNum;
    if (suit == 'P') suitNum = 0;
    else if (suit == 'C') suitNum = 1;
    else if (suit == 'T') suitNum = 2;
    else suitNum = 3;

    return rankNum * 4 + suitNum;
}

string CardUtils::numberToCard(int num) {
    int rankNum = num / 4;
    int suitNum = num % 4;

    string rank;
    if (rankNum == 9) rank = "J";
    else if (rankNum == 10) rank = "Q";
    else if (rankNum == 11) rank = "K";
    else if (rankNum == 12) rank = "A";
    else rank = to_string(rankNum + 2);

    char suit;
    if (suitNum == 0) suit = 'P';
    else if (suitNum == 1) suit = 'C';
    else if (suitNum == 2) suit = 'T';
    else suit = 'H';

    return rank + suit;
}

int CardUtils::factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}

// Implementation of PermutationUtils
vector<int> PermutationUtils::numberToPermutation(int k, int n) {
    vector<int> numbers(n);
    for (int i = 0; i < n; i++) numbers[i] = i;
    vector<int> perm;

    k = k % CardUtils::factorial(n);
    for (int i = 0; i < n; i++) {
        int fact = CardUtils::factorial(n - 1 - i);
        int index = k / fact;
        k = k % fact;
        perm.push_back(numbers[index]);
        numbers.erase(numbers.begin() + index);
    }
    return perm;
}

int PermutationUtils::permutationToNumber(const vector<int>& perm) {
    int n = perm.size();
    int result = 0;
    for (int i = 0; i < n; i++) {
        int smaller = 0;
        for (int j = i + 1; j < n; j++)
            if (perm[j] < perm[i]) smaller++;
        result += smaller * CardUtils::factorial(n - 1 - i);
    }
    return result;
}

// Implementation of An
vector<string> An::pick(const vector<string>& X) {
    vector<int> cardNumbers(6);
    for (int i = 0; i < 6; i++)
        cardNumbers[i] = CardUtils::cardToNumber(X[i]);

    vector<pair<int, int>> indexed(6);
    for (int i = 0; i < 6; i++)
        indexed[i] = { cardNumbers[i], i };
    sort(indexed.begin(), indexed.end());

    int hiddenNumber = cardNumbers[indexed[5].second];
    vector<int> perm = PermutationUtils::numberToPermutation(hiddenNumber, 5);

    vector<string> result(5);
    for (int i = 0; i < 5; i++)
        result[i] = X[indexed[perm[i]].second];

    return result;
}

// Implementation of Binh
string Binh::guess(const vector<string>& Y) {
    vector<int> cardNumbers(5);
    for (int i = 0; i < 5; i++)
        cardNumbers[i] = CardUtils::cardToNumber(Y[i]);

    vector<pair<int, int>> indexed(5);
    for (int i = 0; i < 5; i++)
        indexed[i] = { cardNumbers[i], i };
    sort(indexed.begin(), indexed.end());

    vector<int> perm(5);
    for (int i = 0; i < 5; i++)
        perm[indexed[i].second] = i;

    int hiddenNumber = PermutationUtils::permutationToNumber(perm);
    return CardUtils::numberToCard(hiddenNumber);
}

#include "main.h"
//// Example usage
//int main() {
//    vector<string> cards = {"3P", "4C", "5T", "6H", "7P", "8C"};
//
//    An an;
//    vector<string> selected = an.pick(cards);
//
//    Binh binh;
//    string guessedCard = binh.guess(selected);
//
//    cout << "Guessed card: " << guessedCard << endl;
//    return 0;
//}
