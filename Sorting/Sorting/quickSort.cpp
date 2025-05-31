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

int partition(int* arr, int first, int last) {
	int left = first, right = last - 1;
	int pivot = arr[last];
	while (true) {
		while (left <= right && arr[left] < pivot)
			left++;
		while (left <= right && arr[right] > pivot)
			right--;
		if (left >= right)
			break;
		swap(arr[left], arr[right]);
		left++;
		right--;
	}
	swap(arr[left], arr[last]);
	return left;
}
void quickSort(int* arr, int first, int last) {
	if (first < last) {
		int pos = partition(arr, first, last);
		quickSort(arr, first, pos - 1);
		quickSort(arr, pos + 1, last);
	}
}

int main() {
	int arr[] = { 4,7,6,9,3,5,8,2 };
	quickSort(arr, 0, 7);
	show(arr, 8);
	return 0;
}