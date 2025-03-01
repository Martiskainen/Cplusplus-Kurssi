#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// Prints the elements in the parameter vector ints.
void print_integers(const std::vector< int >& ints)
{
    for(auto elem : ints) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.
void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(vector< int >& ints)
{
    int edellinen = ints.front();

    for(int alkio : ints)
    {
        if(edellinen != alkio)
            return false;
        edellinen = alkio;
    }

    return true;
}

bool is_ordered_non_strict_ascending(vector< int >& ints)
{
    int edellinen = ints.front();

    for(int alkio : ints)
    {
        if(edellinen > alkio)
            return false;
        edellinen = alkio;
    }

    return true;
}

bool is_arithmetic_series(vector< int >& ints)
{
    int eka = ints.front();
    int toka = ints[1];
    int erotus = toka - eka;
    int i = 0;

    for(int alkio : ints)
    {
        if (i > 0)
        {
            eka = toka;
            toka = alkio;
            if (alkio - eka != erotus)
                return false;
        }
        i++;
    }

    return true;
}

bool is_geometric_series(vector< int >& ints)
{
    int eka = ints.front();
    int toka = ints[1];
    int suhde = 0;
    int i = 0;

    if (eka == 0)
        return false;
    for(int alkio : ints)
    {
        if (i == 1)
        {
            toka = alkio;
            suhde = toka / eka;
        }
        if (i > 1)
        {
            eka = toka;
            toka = alkio;
            if (toka / eka != suhde)
                return false;
        }
        i++;
    }

    return true;
}

void triple_integers(vector< int >& ints)
{
    int i = 0;
    int koko = ints.size();

    while(i < koko)
    {
        ints[i] *= 3;
        i++;
    }
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 4;
    std::cin >> how_many;

    if(how_many <= 0) {
        return EXIT_FAILURE;
    }

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers)) {
        std::cout << "All the integers are the same" << std::endl;
    } else {
        std::cout << "All the integers are not the same" << std::endl;
    }

    if(is_ordered_non_strict_ascending(integers)) {
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    } else {
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;
    }

    if(is_arithmetic_series(integers)) {
        std::cout << "The integers form an arithmetic series" << std::endl;
    } else {
        std::cout << "The integers do not form an arithmetic series" << std::endl;
    }

    if(is_geometric_series(integers)) {
        std::cout << "The integers form a geometric series" << std::endl;
    } else {
        std::cout << "The integers do not form a geometric series" << std::endl;
    }

    triple_integers(integers);
    std::cout << "Tripled values: ";
    print_integers(integers);

    return EXIT_SUCCESS;
}

