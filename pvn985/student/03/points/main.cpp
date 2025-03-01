#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{

    string luettava_nimi = "";
    string luettava_rivi = "";
    string rivinimi = "";
    int rivipisteet = 0;
    int jakajakohta = 0;
    map<string, int> henkilot;

    cout << "Input file: ";
    cin >> luettava_nimi;
    ifstream luettava_olio(luettava_nimi);
    if (not luettava_olio)
    {
        cout << "Error! The file " << luettava_nimi << " cannot be opened.";
        exit(1);
    }
    cout << "Final scores: " << endl;

    while (getline(luettava_olio, luettava_rivi))
    {
        jakajakohta = luettava_rivi.find(':');
        rivinimi = luettava_rivi.substr(0, jakajakohta);
        rivipisteet = stoi(luettava_rivi.substr(jakajakohta + 1));
        if (henkilot[rivinimi])
            henkilot[rivinimi] += rivipisteet;
        else
            henkilot[rivinimi] = rivipisteet;
    }

    for (auto pair : henkilot)
    {
        cout << pair.first << ": " << pair.second << endl;
    }
}
