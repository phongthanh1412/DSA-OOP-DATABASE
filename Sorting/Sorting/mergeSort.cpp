#include<iostream>
using namespace std;

void mergeArray(int* arr1, int n, int* arr2, int m, int* arr3) {
	int idx1 = 0, idx2 = 0, idx3 = 0;

	while (idx1 < n && idx2 < m) {
		if (arr1[idx1] < arr2[idx2])
			arr3[idx3++] = arr1[idx1++];
		else
			arr3[idx3++] = arr2[idx2++];
	}
	while (idx1 < n) {
			arr3[idx3++] = arr1[idx1++];
	}
	while (idx2 < m) {
			arr3[idx3++] = arr2[idx2++];
	}

}
int* mergeSort(int* arr, int left, int right) {
	if (left == right) {
		int* temp = new int[1];
		temp[0] = arr[left];
		return temp;
	}
	int mid = left + (right - left) / 2;
	int* arr1 = mergeSort(arr, left, mid);
	int* arr2 = mergeSort(arr, mid + 1, right);

	int n = mid - left + 1;
	int m = right - mid;

	int* arr3 = new int[n + m];
	mergeArray(arr1, n, arr2, m, arr3);

	delete[]arr1;
	delete[]arr2;

	return arr3;
}

void show(int* arr, int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}

int main() {
	int arr[] = { 4,7,6,9,3,5,8,2 };
	int* arr3 = mergeSort(arr, 0, 7);
	show(arr3, 8);
	delete[]arr3;
	return 0;
}