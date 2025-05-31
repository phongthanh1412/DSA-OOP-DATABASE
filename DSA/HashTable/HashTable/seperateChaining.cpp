#include<iostream>

#define maxSize 9
using namespace std;

struct Node {

	int key;
	Node* next;

	Node(int key) {
		this->key = key;
		this->next = NULL;
	}

};

struct hashTable {
	Node* bucket[maxSize];

	hashTable() {
		for (int i = 0; i < maxSize; i++)
			bucket[i] = NULL;
	}

	int hashFunction(int key) {
		return key % maxSize;
	}

	void addNode(int i, int val) {
		Node* newNode = new Node(val);
		if (!bucket[i]) {
			bucket[i] = newNode;
			return;
		}
		else {
			Node* temp = bucket[i];
			while (temp->next)
				temp = temp->next;
			newNode->next = temp->next;
			temp->next = newNode;
		}
	}

	void insertIntoList(int key) {

		int i = hashFunction(key);
		addNode(i, key);
	}

	void showHashTable() {
		for (int i = 0; i < maxSize; i++) {
			cout << i;
			Node* temp = bucket[i];
			while (temp) {
				cout << " --> " << temp->key;
				temp = temp->next;
			}
			cout << endl;
		}
	}

	Node* searchNode(int val) {
		int i = hashFunction(val);
		if (!bucket[i])
			return NULL;
		else {
			Node* temp = bucket[i];
			while (temp && temp->key != val)
				temp = temp->next;
			return temp;
		}
	}

	void deleteNode(int val) {
		int i = hashFunction(val);
		if (!bucket[i])
			return;
		while (bucket[i] && bucket[i]->key == val) {
			Node* toDelete = bucket[i];
			bucket[i] = bucket[i]->next;
			delete toDelete;
		}
		Node* temp = bucket[i];
		while (temp && temp->next) {
			if (temp->next->key == val) {
				Node* toDelete = temp->next;
				temp->next = toDelete->next;
				toDelete->next = NULL;
				delete toDelete;
			}
		}
	}

	void Free() {
		for (int i = 0; i < maxSize; i++) {
			Node* temp = bucket[i];
			while (temp) {
				Node* toDelete = temp;
				temp = temp->next;
				delete toDelete;
			}
			bucket[i] = NULL;
		}
	}
};

int main() {
	hashTable table;
	int a[] = { 15, 11, 27, 8, 12 };
	for (int i = 0; i < 5; i++)
		table.insertIntoList(a[i]);
	table.showHashTable();

	int val = 0;
	cin >> val;
	table.deleteNode(val);
	table.showHashTable();
	/*Node* node = table.searchNode(val);
	cout << node->key;*/


	table.Free();
	return 0;
}