#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>
#include <iomanip>
using namespace std;

class Player {
private:
    int n;  

public:
    Player();
    Player(int initialValue);

    bool goFirst() const;
    int play() const;
    void playBack(int moveValue);

    void display() const;
};


Player::Player() : n(0) {}

Player::Player(int initialValue) : n(initialValue) {}

bool Player::goFirst() const {
    return false;
}

int Player::play() const {
    return n;
}

void Player::playBack(int moveValue) {
    n -= moveValue;
}

void Player::display() const {
    cout << "Player with n = " << n << endl;
}

#include "main.h"
//int main() {
//    Player p1;
//    p1.display();  
//
//    Player p2(10);
//    p2.display();  
//
//    cout << "Does player go first? " << boolalpha << p2.goFirst() << endl;
//    cout << "Player value: " << p2.play() << endl;
//
//    p2.playBack(3);
//    p2.display();  
//
//    return 0;
//}