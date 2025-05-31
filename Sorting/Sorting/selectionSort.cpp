#include<iostream>
using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
void show(int* arr, int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}
void selectionSort(int* arr, int n) {
	int mini = 0;
	for (int i = 0; i < n - 1; i++) {
		mini = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[mini] > arr[j]) {
				mini = j;
			}
		}
		swap(arr[mini], arr[i]);
	}
}

int main() {
	int arr[] = { 4,7,6,9,3,5,8,2 };
	selectionSort(arr, 8);
	
	show(arr, 8);
	return 0;
}