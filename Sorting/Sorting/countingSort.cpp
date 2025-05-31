#include<iostream>
using namespace std;

void countingSort(int arr[], int n) {

	int maxi = arr[0], mini = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > maxi)
			maxi = arr[i];
		else mini = arr[i];
	}

	int m = maxi - mini + 1;
	int* output = new int[n];
	int* count = new int[m];

	for (int i = 0; i < m; i++)
		count[i] = 0;

	for (int i = 0; i < n; i++)
		count[arr[i] - mini]++;

	for (int i = 1; i < m; i++)
		count[i] += count[i - 1];

	for (int i = 0; i < n; i++) {
		output[count[arr[i] - mini] - 1] = arr[i];
		count[arr[i] - mini]--;
	}

	for (int i = 0; i < n; i++)
		arr[i] = output[i];

	delete[]count;
	delete[]output;
}

void show(int arr[], int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}

int main() {
	int arr[] = { 4,7,6,9,3,5,8,2 };
	countingSort(arr, 8);
	show(arr, 8);
	return 0;
}