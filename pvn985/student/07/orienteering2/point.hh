/* Project: Orienteering
 * Description: Datastructure that represents points
 * and handles following information of point:
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

#ifndef POINT_HH
#define POINT_HH
#include <string>

using namespace std;

class Point
{
public:
    // Constructor declaration
    Point(const string& name, int x, int y, int height, char marker);

    // Member function declarations
    void set_xy(int x, int y);
    int get_x() const;
    int get_y() const;
    int get_height() const;
    char get_marker() const;
    string get_name() const;

private:
    string name_;
    int x_;
    int y_;
    int height_;
    char marker_;
};

#endif // POINT_HH
