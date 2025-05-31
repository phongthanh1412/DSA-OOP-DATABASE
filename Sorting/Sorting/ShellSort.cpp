#include<iostream>
using namespace std;

void ShellSort(int arr[], int n) {
	int val = 0, i = 0, j = 0;
	for (int exp = n / 2; exp > 0; exp /= 2) {
		for (i = exp; i < n; i++) {
			val = arr[i];
			for (j = i; j >= exp && arr[j - exp] > val; j -= exp)
				arr[j] = arr[j - exp];
			arr[j] = val;
		}
	}

}

void show(int* arr, int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}

int main() {
	int arr[] = { 4,7,6,9,3,5,8,2 };
	ShellSort(arr, 8);
	show(arr, 8);

	return 0;
}