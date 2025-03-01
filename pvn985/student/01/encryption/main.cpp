#include <iostream>
#include <string>

using namespace std;

int main()
{
    string avain = "";
    int pituus = 0;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    int valid = 0;
    string sana = "";
    string korvaus = "";

    cout << "Enter the encryption key: ";
    cin >> avain;
    pituus = avain.length();
    if (pituus != 26)
    {
        cout << "Error! The encryption key must contain 26 characters.";
        valid = 1;
    }
    if (valid == 0)
    {
        for (i = 0; i < 26; i++)
        {
            if (avain[i] < 'a' || avain[i] > 'z')
                valid = 1;
        }
        if (valid == 1)
            cout << "Error! The encryption key must contain only lower case characters.";
    }
    if (valid == 0)
    {
        for (i = 0; i < 26; i++)
        {
            if (avain.find(alphabet[i]) < 26)
                valid = 0;
            else
            {
                valid = 1;
                i = 26;
            }
        }
        if (valid == 1)
            cout << "Error! The encryption key must contain all alphabets a-z.";
    }

    if (valid == 0)
    {
        cout << "Enter the text to be encrypted: ";
        cin >> sana;
        pituus = sana.length();

        for (i = 0; i < pituus; i++)
        {
            korvaus = avain[alphabet.find(sana[i])];
            sana.replace(i, 1, korvaus);
        }
    }

    if (valid == 0)
        cout << "Encrypted text: " << sana;
    else
        exit(1);

    return 0;
}
