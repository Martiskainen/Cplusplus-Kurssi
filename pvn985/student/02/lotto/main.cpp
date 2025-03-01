#include <iostream>

using namespace std;

unsigned long int factorial(unsigned long int luku)
{
    unsigned long int tod = luku;

    while (--luku > 0)
        tod *= luku;
    return tod;
}

int main()
{
    unsigned long int tod = 0;
    unsigned long int kaikki = 0;
    unsigned long int valinta = 0;
    unsigned long int vahennys = 1;

    cout << "Enter the total number of lottery balls: ";
    cin >> kaikki;

    cout << "Enter the number of drawn balls: ";
    cin >> valinta;
    if (valinta < 1 || kaikki < 1)
    {
        cout << "The number of balls must be a positive number.";
        exit(1);
    }
    if (valinta > kaikki)
    {
        cout << "The maximum number of drawn balls is the total amount of balls.";
        exit(1);
    }

    if (kaikki != valinta)
        vahennys = kaikki - valinta;
    tod = factorial(kaikki) /(factorial(vahennys) * factorial(valinta));
    cout << "The probability of guessing all " << valinta << " balls correctly is 1/" << tod;

    return 0;

}
