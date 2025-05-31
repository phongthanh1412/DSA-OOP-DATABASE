#include <iostream>
using namespace std;

int sumDigits(int n)
{
    if (n < 10)
        return n;
    return n % 10 + sumDigits(n / 10);
}

int sumToOneDigit(int n)
{
    if (n < 10)
        return n;
    return sumToOneDigit(sumDigits(n));
}

int reverse(int n, int rev)
{
    if (n == 0)
        return rev;
    return reverse(n / 10, rev * 10 + n % 10);
}
int findReverse(int n)
{
    return reverse(n, 0);
}
int main()
{
    cout << sumDigits(457);
    cout << endl;
    cout << sumToOneDigit(457);
    cout << endl;
    cout << findReverse(457);
    return 0;
}