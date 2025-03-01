#include <iostream>

using namespace std;

int main()
{
    int luku = 1;
    int eka = 1;
    int toka = 1;
    int ekatulos = 1;
    int tokatulos = 1;

    cout << "Enter a positive number: ";

    cin >> luku;
    if (luku > 0)
    {
        while (eka <= luku)
        {
            toka = eka;
            while (eka * toka <= luku)
            {
                if (eka * toka == luku)
                {
                    ekatulos = eka;
                    tokatulos = toka;
                }
                toka++;

            }
            eka++;
        }
        cout << luku << " = " << ekatulos << " * " << tokatulos;
    }
    else
        cout << "Only positive numbers accepted";

    return 0;
}
