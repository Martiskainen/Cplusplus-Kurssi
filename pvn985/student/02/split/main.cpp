#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::vector<std::string> split(const std::string& input,
                               const char& delimiter,
                               bool ignore_empty = false)
{
    vector<string> result;
    string sentence = input;
    string word = "";

    while ( sentence.find(delimiter) != string::npos )
    {
        word = sentence.substr(0, sentence.find(delimiter));
        sentence = sentence.substr(sentence.find(delimiter) + 1,
                                   sentence.size());
        if ( not (word.empty() and ignore_empty) )
        {
            result.push_back(word);
        }
    }

    result.push_back(sentence);

    return result;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
