/* Project: Orienteering
 * Description: Implementation of class Point functions
 * that retreive Point's information from private members:
 * - x coordinate
 * - y coordinate
 * - height
 * - marker
 * - name
 *
 * Program author
 * Name: Misa Martiskainen
 * Student number: 153429347
 * Username: pvn985
 * E-Mail: misa.martiskainen@tuni.fi
 *
 * */

#include "point.hh"

// Constructor definition
Point::Point(const string& name, int x, int y, int height, char marker) :
    name_(name), x_(x), y_(y), height_(height), marker_(marker)
{

}

int Point::get_x() const
{
    return x_;
}

int Point::get_y() const
{
    return y_;
}

int Point::get_height() const
{
    return height_;
}

char Point::get_marker() const
{
    return marker_;
}

string Point::get_name() const
{
    return name_;
}
