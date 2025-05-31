#include <iostream>
#include <vector>
using namespace std;

void classify(int arr[], int size)
{
    int j = size - 1;
    int i = 0;
    while (i < size && i <= j)
    {
        if (arr[i] % 2 == 0 && arr[j] % 2 != 0)
        {
            swap(arr[i], arr[j]);
            j--;
        }
        else if (arr[i] % 2 == 0 && arr[j] % 2 == 0)
        {
            while (arr[j] % 2 == 0 && j > 0)
                j--;
            swap(arr[i], arr[j]);
            j--;
        }
        i++;
    }
}

void selectionSort(int arr[], int size, int idx0)
{
    for (int i = idx0; i < size - 1; i++)
    {
        int idx = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[idx] < arr[j])
                idx = j;
        }
        swap(arr[idx], arr[i]);
    }
}
void print(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}
void classify_sort(int arr[], int size)
{
    classify(arr, size);
    int idx = 0, i = 0;
    while (i < size)
    {
        if (arr[i] % 2 == 0){
            idx = i;
        break;
        }      
        i++;
    }
    selectionSort(arr,size,idx);
    print(arr,size);
}

int main()
{
    int arr[] = {5, 6, 2, 3, 1, 9, 8, 4, 11};
    int arr1[] = {88, 8, 6, 2, 12};
    int arr2[] = {7, 9, 3, 5, 1, 15};

    // classify(arr, 9);
    // print(arr, 9);

    // selectionSort(arr, 9, 0);
    // print(arr, 9);

    classify_sort(arr,9);

    return 0;
}
