#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

using namespace std;

class Player
{
public:
    Player(const string& name);
    ~Player();

    string get_name() const;

    void add_points(int points);
    int get_points();

    bool has_won();
private:
    string name_;
    int points_;
};

#endif // PLAYER_HH
