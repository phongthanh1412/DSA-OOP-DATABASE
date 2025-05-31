#include<iostream>
using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
void show(int arr[], int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}

void heapify(int arr[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1, right = 2 * i + 2;
	if (left < n && arr[left] > arr[largest]) largest = left;
	if (right < n && arr[right] > arr[largest]) largest = right;
	if (largest != i) {
		swap(arr[largest], arr[i]);
		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n) {
	// build heap
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(arr, n, i);
	}
	// sort
	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}
int main() {
	int arr[] = { 4,7,6,9,3,5,8,2 };
	heapSort(arr, 8);
	show(arr, 8);
	return 0;
}