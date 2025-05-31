#include<iostream>

#define maxSize 10
using namespace std;

struct hashTable {
	int* arr;
	int tableSize;

	hashTable() {
		tableSize = maxSize;
		arr = new int[tableSize];
		for (int i = 0; i < tableSize; i++)
			arr[i] = NULL;
	}

	int hashFunction1(int key) {
		return key % maxSize;
	}
	int hashFunction2(int key) {
		return (key * tableSize - 1) % maxSize;
	}

	// Linear probing 
	void insert1(int val) {
		int i = hashFunction1(val);
		while (arr[i] != NULL) {
			i = (i + 1) % maxSize;
		}
		arr[i] = val;
	}
	//  Quadratic probing 
	void insert2(int val) {
		int i = hashFunction1(val);
		int factor = 1;
		while (arr[i] != NULL) {
			i = (i + factor * factor) % maxSize;
			factor++;
		}
		arr[i] = val;
	}
	//  Double hashing
	void insert3(int val) {
		int i1 = hashFunction1(val);
		int i2 = hashFunction2(val);
		int factor = 1;
		while (arr[i1] != NULL) {
			i1 = (i1 + factor * i2) % maxSize;
			factor++;
		}
		arr[i1] = val;
	}

	void showHashTable() {
		for (int i = 0; i < tableSize; i++)
			if (arr[i] == NULL)
				cout << i << endl;
			else
				cout << i << " --> " << arr[i] << endl;
	}

	void search1(int val) {
		int i = hashFunction1(val);
		while (arr[i] != NULL && arr[i] != val)
			i = (i + 1) % maxSize;
		if (arr[i] == val)
			cout << val << " is found";
		else
			cout << val << " is not found";
	}
	void search2(int val) {
		int i = hashFunction1(val);
		int factor = 1;
		while (arr[i] != NULL && arr[i] != val) {
			i = (i + factor * factor) % maxSize;
			factor++;
		}
		if (arr[i] == val)
			cout << val << " is found";
		else
			cout << val << " is not found";
	}
	void search3(int val) {
		int i1 = hashFunction2(val);
		int i2 = hashFunction2(val);
		int factor = 1;
		while (arr[i1] != NULL && arr[i1] != val) {
			i1 = (i1 + factor * i2) % maxSize;
			factor++;
		}
		if (arr[i1] == val)
			cout << val << " is found";
		else
			cout << val << " is not found";
	}

	void Free() {
		delete[]arr;
	}
};

int main() {
	hashTable table;
	int a[] = { 25,34,99,54,88,95,47,48 };
	for (int i = 0; i < 8; i++)
		table.insert1(a[i]);
	table.showHashTable();

	/*int val = 0;
	cin >> val;
	table.search1(val);*/

	table.Free();
	return 0;
}