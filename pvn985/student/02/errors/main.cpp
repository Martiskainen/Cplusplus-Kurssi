#include <iostream>
#include <string>

using namespace std;


const int MAX_GUESSES = 10;

// Prints empty lines at the beginning of execution
void clean_screen();


// Prints string using '_' in the places of letters not guessed
void print_game_status();


void clean_screen() {
    // Cleaning screen by printing 100 empty lines.
    for ( int i = 0; i < 100; ++i ) {
        cout << '\n';
    }
}


bool is_word_earlier_guessed(string secret, string guessed) {
    // Going through all the characters in secret string.
    for ( string::size_type index = 0; index <= secret.size(); ++index ) {
        // If such a character in secret string is met that is not in
        // guessed letters, it can be immediately concluded that
        // the whole secret word has not yet guessed.
        if ( guessed.find(secret.at(index)) == string::npos ) {
            return false;
        }
    }

    // When all the secret string has been gone through, and each character
    // was found from guessed string, it must hold that the whole
    // secret word has been guessed.
    return true;
}


void print_game_status(string secret, string guessed) {
    // The characters of a string can be gone through also with such a for loop
    // that looks like "for x in y" structure in Python.
    // This is an alternative for the for loop with index variable
    // used in previous function.
    for ( char secret_char: secret ) {
        if ( guessed.find(secret_char) == string::npos ) {
            cout << "_";
        } else {
            cout << secret_char;
        }
    }

    cout << endl;
}

// Checks if all the letters include in the list of guessed letters
bool is_word_already_guessed(string secret, string guessed)
{
    int pituus = secret.length();

    for (int i = 0; i < pituus; i++)
    {
        if (guessed.find(secret[i]) == string::npos)
            return false;
    }

    return true;
}

int main() {
    string secret_word = "";
    string guessed_letters = "";
    int guesses_used = 0;

    cout << "Give a word to be guessed: ";
    getline(cin, secret_word);

    clean_screen();

    while ( is_word_already_guessed(secret_word, guessed_letters) == false
           && guesses_used < MAX_GUESSES ) {

        cout << endl
             << "Game status: ";

        print_game_status( secret_word, guessed_letters );

        if ( guessed_letters.size() > 0 ) {
            cout << "You have used " << guesses_used
                 << " guesses!"
                 << endl
                 << "You have guessed letters: " << guessed_letters
                 << endl;
        }

        string guess = "";
        cout << "Guess a letter: ";
        getline(cin, guess);



        if (is_word_already_guessed(secret_word, guessed_letters) == true)
        {
            break;
        }


        if ( guess.size() != 1 ) {
            cout << "You failed: give exactly one letter!"
                 << endl;
            continue;

        } else if ( guessed_letters.find(guess) != string::npos ) {

            cout << "You failed: you had already guessed the letter " << guess << "!"
                 << endl;
            continue;
        }

        guessed_letters += guess;

        if ( secret_word.find(guess) == string::npos ) {
            cout << "Guessed letter does not include the word!" << endl;
        }

        ++guesses_used;
    }

    if ( guesses_used == MAX_GUESSES) {
        cout << endl
             << "Guesses expired!"
             << endl;

    } else {

        cout << endl
             << "Right guess. You used " << guesses_used
             << " guesses!"
             << endl;
    }
}
