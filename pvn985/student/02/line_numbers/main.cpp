#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string luettava_nimi = "";
    string kirjoitettava_nimi = "";
    string luettava_rivi = "";
    string kirjoitettava_rivi = "";
    int i = 1;
    string rivinumero = "";

    cout << "Input file: ";
    cin >> luettava_nimi;
    cout << "Output file: ";
    cin >> kirjoitettava_nimi;

    ifstream luettava_olio(luettava_nimi);
    if (not luettava_olio)
    {
        cout << "Error! The file " << luettava_nimi << " cannot be opened.";
        exit(1);
    }
    ofstream kirjoitettava_olio(kirjoitettava_nimi);
    while (getline(luettava_olio, luettava_rivi))
    {
        if (luettava_rivi[0] != 10)
        {
            rivinumero = to_string(i);
            luettava_rivi.insert(0, " ");
            luettava_rivi.insert(0, rivinumero);
            kirjoitettava_olio << luettava_rivi << endl;
            i++;
        }
        else
        {
            kirjoitettava_olio << endl;
        }
    }
    kirjoitettava_olio.close();
    luettava_olio.close();

    return 0;
}
