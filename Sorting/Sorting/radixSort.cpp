#include<iostream>
using namespace std;

int getMax(int arr[], int n) {
	int maxi = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > maxi)
			maxi = arr[i];
	return maxi;
}

void countSort(int arr[], int n, int exp) {
	int* output = new int[n];
	int count[10] = { 0 };

	for (int i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	for (int i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (int i = 0; i < n; i++)
		arr[i] = output[i];

	delete[]output;
}

void radixSort(int arr[], int n) {
	int maxi = getMax(arr, n);
	for (int exp = 1; maxi / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}

void show(int arr[], int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}

int main() {
	int arr[] = { 4,7,6,9,3,5,8,2 };
	radixSort(arr, 8);
	show(arr, 8);
	return 0;
}