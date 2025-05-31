#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

bool isPrime(int num)
{
    if (num < 2)
        return false;
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

void sorting(vector<int> &numbers)
{
    for (int i = 0; i < numbers.size() - 1; i++)
    {
        for (int j = i + 1; j < numbers.size(); j++)
        {
            if (numbers[i] > numbers[j])
            {
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }
}

void readData(string fileName, vector<int> &numbers)
{
    fstream ifile;
    ifile.open(fileName, ios::in);
    if (ifile.eof())
    {
        cout << "File is not found." << endl;
        return;
    }

    int number;
    while (!ifile.eof())
    {
        ifile >> number;
        if (isPrime(number))
            numbers.push_back(number);
    }

    sorting(numbers);
    ifile.close();
}
void writeTotal(vector<int> &numbers, string outFileName)
{
    fstream ofile;
    ofile.open(outFileName, ios::out);
    if (ofile.eof())
    {
        cout << "File is not found.";
        return;
    }

    for (int i = 0; i < numbers.size(); i++)
    {
        ofile << numbers[i] << " ";
        cout << numbers[i] << " ";
    }

    ofile.close();
}
int main()
{
    vector<int> numbers;
    readData("28tech_number.txt", numbers);
    writeTotal(numbers, "28tech_prime.txt");
    return 0;
}