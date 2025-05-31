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
void bubbleSort(int* arr, int n) {
	for (int i = 0; i < n - 1; i++) 
		for (int j = i + 1; j < n; j++)
			if (arr[i] > arr[j])
				swap(arr[i], arr[j]);
	
}

int main() {
	int arr[] = { 4,7,6,9,3,5,8,2 };
	bubbleSort(arr, 8);
	show(arr, 8);
	return 0;
}