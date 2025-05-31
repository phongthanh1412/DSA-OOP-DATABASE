#include<iostream>
using namespace std;

void insertionSort(int* arr, int n) {
	int i = 0, j = 0, val = 0;
	for (i = 1; i < n; i++) {
		val = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > val) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = val;
	}

}

void show(int* arr, int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}

int main() {
	int arr[] = { 4,7,6,9,3,5,8,2 };
	insertionSort(arr, 8);
	show(arr, 8);
	return 0;
}