#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    string syote = "";
    int siemen = 0;
    default_random_engine eng;
    uniform_int_distribution<int>distr(lower, upper);

    cout << "Enter a seed value: ";
    cin >> siemen;
    eng.seed(siemen);
    while (syote != "q")
    {
        cout << endl << "Your drawn random number is " << distr(eng) << endl;
        cout << "Press q to quit or any other key to continue: ";
        cin >> syote;
    }
}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
