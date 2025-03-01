/* Golf
 *
 * Kuvaus:
 *   Ohjelma lukee golf-tuloksia syötetiedostosta, jonka rivit
 * ovat muotoa:
 * paikkakunta;kerhon_nimi;pelaajan_nimi;tulos.
 * Ohjelma tarkistaa, että tiedoston kultakin riviltä löytyy edellä
 * mainitut neljä datakenttää.
 *   Tiedostosta löytyvät tiedot kerätään sopivaan tietorakenteeseen, joka
 * koostuu STL:n säiliöistä ja tietueista. Tämän jälkeen käyttäjä voi
 * tehdä hakuja tietorakenteeseen käyttämällä komentoja places, clubs,
 * rounds, played ja compare. Komennoilla on eri määrä parametreja,
 * ja ohjelma tarkistaa, että käyttäjä antoi oikean määrän parametreja
 * ja että parametrit (paikkakunta, kerho, pelaaja)
 * löytyvät tietorakenteesta.
 *   Ohjelman toiminnan voi lopettaa komennolla quit.
 *
 * Ohjelman kirjoittaja
 * Nimi: Misa Martiskainen
 * Opiskelijanumero: 153429347
 * Käyttäjätunnus: pvn985
 * E-Mail: misa.martiskainen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * Käytetyt STL-rakenteet: pair, sort, tuple, vector
 *
 * */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>

using namespace std;

// Create names for opened file line indexes
enum FILE_INDEXES {LOCATION, CLUB, PLAYER, SCORE, FIELDS};

// Create struct for Round data to combine player with score
struct Round
{
    string name;
    int score;
};

// Create alias for location data type
using Data = map<string, map<string, vector<Round>>>;

// Receive string and delimiter
// Create vector, split string by delimiter, save to vector
// Return created vector
vector<string> split(const string& str, const char& delim)
{
    vector<string> result = {""};
    bool insideQuotation = false;
    for (char currentChar : str)
    {
        if (currentChar == '"')
        {
            insideQuotation = not insideQuotation;
        }
        else if (currentChar == delim and not insideQuotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(currentChar);
        }
    }
    return result;
}

// Receive location Data struct
// Ask for input_file, open input_file
// Print error based on input or if failed to open file
// Return false if failed to open file
// Create vector, send lines and delimiters to split()
// Receive split line from split and save to vector
// Save split line to Data struct as vector
// Return true if file opened
bool read_input_file(Data& data)
{
    vector<string> split_row;
    string row = "";
    string file_name = "";
    string location = "";
    string club = "";
    string name = "";
    int score = 0;

    cout << "Input file: ";
    getline(cin, file_name);
    ifstream file_stream(file_name);
    if (not file_stream)
    {
        cout << "Error: The specified file cannot be opened!";
        return false;
    }
    while (getline(file_stream, row))
    {
        split_row = split(row, ';');
        if (split_row.size() != FIELDS)
        {
            cout << "Error: The specified file has an erroneous line!";
            return false;
        }
        for (string& field : split_row)
        {
            if (field.empty())
            {
                cout << "Error: A line has an empty value!";
                return false;
            }
        }
        location = split_row.at(LOCATION);
        club = split_row.at(CLUB);
        name = split_row.at(PLAYER);
        score = stoi(split_row.at(SCORE));
        data[location][club].push_back({name, score});
    }
    file_stream.close();

    return true;
}

// Receive location data
// Print locations and clubs in alphabetical order or error based on input
void places(const Data& all_locations, const vector<string>& split_input)
{
    size_t allowed_fields = 1;
    int first_field = 0;

    if(split_input.size() != allowed_fields ||
        split_input.at(first_field) != "places")
    {
        cout << "Error: In command: places" << endl;
    }
    else
    {
        for (auto& location : all_locations)
        {
            cout << location.first << endl;

            for (auto& club : location.second)
            {
                cout << "--" << club.first << endl;
            }
        }
    }
}

// Receive location data and split input
// Check split input format and print clubs or errors based on input
void clubs(const Data& all_locations, const vector<string>& split_input)
{
    bool found = false;
    size_t allowed_fields = 2;
    int first_field = 0;
    int second_field = 1;

    if(split_input.at(first_field) != "clubs" ||
        split_input.size() != allowed_fields)
    {
        found = true;
        cout << "Error: In command: clubs" << endl;
    }
    else
    {
        for (auto& location : all_locations)
        {
            if (location.first == split_input.at(second_field))
            {
                found = true;
                for (auto& club : location.second)
                {
                    cout << "--" << club.first << endl;
                }
            }
        }
    }
    if (not found)
    {
        cout << "Error: The given location not found!" << endl;
    }
}

// Receive location data and split input
// Check split input format and print errors based on input
// Create vector, save asked player round data to vector
// Print vector
void rounds(const Data& all_locations, const vector<string>& split_input)
{
    vector<pair<int, string>> scores;
    bool found = false;
    size_t allowed_fields = 2;
    int first_field = 0;
    int second_field = 1;

    if(split_input.at(first_field) != "rounds" ||
        split_input.size() != allowed_fields)
    {
        found = true;
        cout << "Error: In command: rounds" << endl;
    }
    else
    {
        for (auto& location : all_locations)
        {
            for (auto& club : location.second)
            {
                if (club.first == split_input.at(second_field))
                {
                    found = true;
                    for (auto& player : club.second)
                    {
                        scores.push_back(make_pair(player.score, player.name));
                    }
                }
            }
        }
        if (found)
        {
            sort(scores.begin(), scores.end());
            for (auto& pair : scores)
            {
                cout << pair.second << " : ";
                if (pair.first> 0)
                    cout << "+" << pair.first << endl;
                else
                    cout << pair.first << endl;
            }
        }
    }
    if (not found)
    {
        cout << "Error: The given club not found!" << endl;
    }
}

// Receive player rounds and scores
// return average of scores based on number of rounds
float handicap(const size_t& rounds, vector<int>& scores)
{
    float sum = 0;
    size_t i = 0;
    size_t min_rounds = 3;
    size_t max_rounds = 5;
    float average = 0;

    if (rounds >= min_rounds && rounds <= max_rounds)
    {
        for (i = 0; i < scores.size(); i++)
        {
            sum += scores.at(i);
        }
        average = sum / scores.size();
    }
    else if (rounds > max_rounds)
    {
        sort(scores.begin(), scores.end());
        for (i = 0; i < max_rounds; i++)
        {
            sum += scores.at(i);
        }
        average = sum / max_rounds;
    }
    return average;
}

// Receive location data and split input
// Check split input format and print errors based on input
// Create vector of tuples of player score in club and location
// Create vector for scores and sum up rounds
// Send sum of rounds and vector of scores to handicap()
// to get average of scores based on number of rounds
// Print average based on rounds and playerdata from vector tuple
void played(const Data& all_locations, const vector<string>& split_input)
{
    vector<tuple<int, string, string>> playerdata;
    vector<int> scores;
    bool found = false;
    size_t rounds = 0;
    size_t allowed_fields = 2;
    int first_field = 0;
    int second_field = 1;
    float average = 0;
    size_t min_rounds = 3;
    size_t max_rounds = 5;
    string input_name = "";

    if(split_input.at(first_field) != "played" ||
        split_input.size() != allowed_fields)
    {
        found = true;
        cout << "Error: In command: played" << endl;
    }
    else
    {
        input_name = split_input.at(second_field);
        for (auto& location : all_locations)
        {
            for (auto& club : location.second)
            {
                for (auto& player : club.second)
                {
                    if (player.name == input_name)
                    {
                        found = true;
                        playerdata.push_back(make_tuple(
                            player.score, club.first, location.first));
                        rounds++;
                        scores.push_back(player.score);
                    }
                }
            }
        }
        if (found)
        {
            if (rounds < min_rounds)
            {
                cout << input_name << " has too few rounds for a handicap:" <<
                    endl;
            }
            else if (rounds < max_rounds)
            {
                average = handicap(rounds, scores);
                cout << input_name << " has a HCP of " << average <<
                    " with following results:" << endl;
            }
            else
            {
                average = handicap(rounds, scores);
                cout << input_name << " has a HCP of " << average <<
                    " with following results:" << endl;
            }
            sort(playerdata.begin(), playerdata.end());
            for (auto& info : playerdata)
            {
                cout << get<2>(info) << " : " << get<1>(info) << " : ";
                if (get<0>(info) > 0)
                    cout << "+" << get<0>(info) << endl;
                else
                    cout << get<0>(info) << endl;
            }
        }
    }
    if (not found)
    {
        cout << "Error: The player hasn't played any rounds!" << endl;
    }
}

// Receive location data and player name
// Create vector of scores
// Send rounds and scores to handicap() and receive average
// Make and return a pair of average and rounds
pair<float, int> get_handicap(const Data& all_locations, const string& compare_name)
{
    vector<int> scores;
    size_t rounds = 0;
    float average = 0;

    for ( auto& location : all_locations )
    {
        for ( auto& club : location.second )
        {
            for (auto& player : club.second )
            {
                if (player.name == compare_name)
                {
                    rounds++;
                    scores.push_back(player.score);
                }
            }
        }
    }
    average = handicap(rounds, scores);
    return make_pair(average, rounds);
}

// Receive player names, averages and rounds
// Print player rounds and averages status based on rounds
// Print player comparison based on averages
void compare_print(const pair<float, int>& pair_first, const pair<float, int>& pair_second,
                   const string& name_first, const string& name_second)
{
    int no_rounds = 0;
    float average_first = pair_first.first;
    float average_second = pair_second.first;
    int rounds_first = pair_first.second;
    int rounds_second = pair_second.second;
    int min_rounds = 3;

    if (rounds_first == no_rounds)
    {
        cout << name_first << " has played no rounds of golf" << endl;
    }
    else if (rounds_first < min_rounds)
    {
        cout << name_first << " has played " << rounds_first <<
            " rounds of golf, but hasn't played enough for a handicap" << endl;
    }
    else
    {
        cout << name_first << " has played " << rounds_first <<
            " rounds of golf, with HCP of " << average_first << endl;
    }
    if (rounds_second == no_rounds)
    {
        cout << name_second << " has played no rounds of golf" << endl;
    }
    else if (rounds_second < min_rounds)
    {
        cout << name_second << " has played " << rounds_second <<
            " rounds of golf, but hasn't played enough for a handicap" << endl;
    }
    else
    {
        cout << name_second << " has played " << rounds_second <<
            " rounds of golf, with HCP of " << average_second << endl;
    }
    if (rounds_first < min_rounds && rounds_second < min_rounds)
    {
        cout << "Either hasn't played enough golf" << endl;
    }
    else if ((rounds_first >= min_rounds && rounds_second < min_rounds) ||
               (rounds_first >= min_rounds && rounds_second >= min_rounds &&
                    average_first < average_second))
    {
        cout << name_first << " has played better golf" << endl;
    }
    else if ((rounds_second >= min_rounds && rounds_first < min_rounds) ||
               (rounds_second >= min_rounds && rounds_first >= min_rounds &&
                average_second < average_first))
    {
        cout << name_second << " has played better golf" << endl;
    }
    else if (rounds_first >= min_rounds && rounds_second >= min_rounds &&
               average_first < average_second)
    {

    }
    else
    {
        cout << "Both have played as good golf" << endl;
    }
}

// Receive location data and split input
// Create vector of tuples and check inputs
// Send location data and player name to gethandicap()
// Get average and rounds from gethandicap()
// Send player names, averages and rounds to compare_print()
void compare(const Data& all_locations, const vector<string>& split_input)
{
    vector<tuple<int, string, string>> playerdata;
    vector<int> scores;
    size_t allowed_fields = 3;
    int first_field = 0;
    int second_field = 1;
    int third_field = 2;
    pair <float, int> pair_first = {};
    pair <float, int> pair_second = {};
    string first_player_name = "";
    string second_player_name = "";

    if(split_input.at(first_field) != "compare" ||
        split_input.size() != allowed_fields)
    {
        cout << "Error: In command: compare" << endl;
    }
    else
    {
        first_player_name = split_input.at(second_field);
        second_player_name = split_input.at(third_field);
        pair_first = get_handicap(all_locations, first_player_name);
        pair_second = get_handicap(all_locations, second_player_name);
        compare_print(pair_first, pair_second, first_player_name,
                      second_player_name);
    }
}

// Receive location data
// Ask input to choose function, print error based on input
// or send location data and split_input to chosen function
void menu(const Data& all_locations)
{
    string input = "";
    vector<string> split_input;
    char delimiter = ' ';
    size_t begin = 0;

    while (input != "quit")
    {
        cout << "> ";
        getline(cin, input);
        split_input = split(input, delimiter);
        if (input.find("places") == begin)
        {
            places(all_locations, split_input);
        }
        else if (input.find("clubs") == begin)
        {
            clubs(all_locations, split_input);
        }
        else if (input.find("rounds") == begin)
        {
            rounds(all_locations, split_input);
        }
        else if (input.find("played") == begin)
        {
            played(all_locations, split_input);
        }
        else if (input.find("compare") == begin)
        {
            compare(all_locations, split_input);
        }
        else if (input != "quit")
        {
            cout << "Error: Unknown command: " << input << endl;
        }
    }
}

// Declare location data object,
// Get values to location data from read_input_file()
// Send location data to menu
// Return 0 to end program
int main()
{
    Data all_locations;

    if (not read_input_file(all_locations))
    {
        return EXIT_FAILURE;
    }
    menu(all_locations);

    return 0;
}
