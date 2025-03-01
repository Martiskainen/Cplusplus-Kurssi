#include <iostream>
#include <string>

using namespace std;

int main()
{
    string pitka = "";
    string lyhyt = "";
    int i = 0;
    int pituus = 0;
    string::size_type pituusmuunnos = 0;
    int kohta = 0;


    cout << "Enter a (longer) string: ";
    cin >> pitka;
    cout << "Enter a (shorter) string to be found: ";
    cin >> lyhyt;

    pituusmuunnos = pitka.length();
    pituus = pituusmuunnos;

    if (pitka.find(lyhyt) == string::npos)
        cout << "Not found";
    else
    {
        cout << "Found at ";
        cout << pitka.find(lyhyt);
        i = pitka.find(lyhyt);
        if (i < pituus - 1)
        {
            while (++i < pituus)
            {
                kohta = pitka.find(lyhyt, i);
                if(i == kohta)
                {
                    cout << ", " << kohta;
                }

            }
        }
    }
    return 0;
}
