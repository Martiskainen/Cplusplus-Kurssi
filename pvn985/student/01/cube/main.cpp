#include <iostream>

using namespace std;

int main()
{
    int luku = 0;

    cout << "Enter a number: ";
    cin >> luku;

    if (luku == 0)
        cout << "The cube of " << luku << " is " << luku * luku * luku << ".";
    else if (luku <= 2147483647 / (luku * luku) && luku < 2147483647 / luku)
        cout << "The cube of " << luku << " is " << luku * luku * luku << ".";
    else
        cout << "Error! The cube of " << luku << " is not " << luku * luku * luku << "!";

    return 0;
}
