
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;


int main()
{
    string luettava_nimi = "";

    cout << "Input file: ";
    cin >> luettava_nimi;
    ifstream luettava_olio(luettava_nimi);
    if (not luettava_olio)
    {
        cout << "Error! The file " << luettava_nimi << " cannot be opened.";
        exit(1);
    }

    map<string, set<int>> sanasto;
    string rivi = "";
    unsigned int rivinumero = 1;

    while (getline(luettava_olio, rivi))
    {

        string sana = "";

        istringstream rivivirta(rivi);
        while( rivivirta >> sana )
        {
            sanasto[sana].insert(rivinumero);
        }
        ++rivinumero;
    }

    map<string, set<int>>::iterator sana_iteraattori = sanasto.begin();

    for ( ; sana_iteraattori != sanasto.end() ; ++sana_iteraattori )
    {
        cout << sana_iteraattori->first << " ";

        cout << sana_iteraattori ->second.size() << ": ";

        set<int>::iterator rivi_iteraattori = sana_iteraattori->second.begin();

        for ( ; rivi_iteraattori != sana_iteraattori->second.end() ; ++rivi_iteraattori)
        {
            if ( rivi_iteraattori != sana_iteraattori->second.begin() )
            {
                cout << ", ";
            }
            cout << *rivi_iteraattori;
        }
        cout << endl;
    }


}
