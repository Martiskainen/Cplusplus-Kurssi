#include <iostream>

using namespace std;

int main()
{
    int i;
    int luku;

    cout << "How many numbers would you like to have? ";
    cin >> luku;

    for (i = 1; i <= luku; i++)
    {
        if (i == luku)
        {
            if (i % 3 == 0 && i % 7 == 0)
                cout << "zip boing";
            else if (i % 3 == 0)
                cout << "zip";
            else if (i % 7 == 0)
                cout << "boing";
            else
                cout << i;
        }
        else
        {
            if (i % 3 == 0 && i % 7 == 0)
                cout << "zip boing" << endl;
            else if (i % 3 == 0)
                cout << "zip" << endl;
            else if (i % 7 == 0)
                cout << "boing" << endl;
            else
                cout << i << endl;
        }
    }

    return 0;
}
