#include "player.hh"
#include <iostream>

Player::Player(const string& name) :
    name_(name), points_(0)
{

}

Player::~Player()
{

}

string Player::get_name() const
{
    return name_;
}

void Player::add_points(int points)
{
    points_ += points;
    if (points_ > 50)
    {
        points_ = 25;
        cout << name_ << " gets penalty points!" << endl;
    }
}

int Player::get_points()
{
    return points_;
}

bool Player::has_won()
{
    return points_ == 50;
}
