/* Project: Orienteering
 * Description: Datastructure that represents an orienteering map and
 * handles information of points and routes
 * Function: Program asks for a file to read. File data is split
 * and added into a class of which you can print:
 * - a map of points on map
 * - routes
 * - route points
 * - route length
 * - height of greatest rise after given point, untill decline,
 *   on all routes with that rise, and prints the route names
 *   zero rise is skipped
 *
 * Program author
 * Name: Misa Martiskainen
 * Student number: 153429347
 * Username: pvn985
 * E-Mail: misa.martiskainen@tuni.fi
 *
 * Notes:
 * Used STL data structures: map, vector
 * Used STL algorithms: pow, find_if, round
 * Used STL smart pointer: shared_ptr
 * Used STL string: string
 * */

#include "orienteeringmap.hh"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

OrienteeringMap::OrienteeringMap() :
    width_(0), height_(0), all_points_(), all_routes_()
{

}

OrienteeringMap::~OrienteeringMap()
{

}

void OrienteeringMap::set_map_size(int width, int height)
{
    width_ = width;
    height_ = height;
}

void OrienteeringMap::add_point(const string& name, int x, int y, int height,
                                char marker)
{
    // Create a shared pointer to a Point
    // and store it in the all_points_ map with the given name.
    all_points_[name] = make_shared<Point>(name, x, y, height, marker);
}

// Retrieve start and end points for connect_route
shared_ptr<Point> OrienteeringMap::get_point(string name) {
    // Check if a point with the given name exists in all_points_
    if (all_points_.find(name) != all_points_.end()) {
        return all_points_[name];
    }
    return nullptr;
}

bool OrienteeringMap::connect_route(string from, string to, string route_name)
{
    // Retrieve the shared pointers to the starting
    // and ending points of the route
    shared_ptr<Point> from_point = get_point(from);
    shared_ptr<Point> to_point = get_point(to);

    // If not found -> return false
    if (!from_point || !to_point) {
        return false;
    }

    // Check if route exists in the map all_routes_
    if (all_routes_.find(route_name) == all_routes_.end()) {
        // Create a new shared pointer to a Route
        // and store it in the all_routes_ map with the given route name
        all_routes_[route_name] = make_shared<Route>();
    }

    // If the route is empty, add the "from" point first
    if (all_routes_[route_name]->route.empty()) {
        all_routes_[route_name]->route.push_back(from_point);
    }

    // Add the 'to' point after 'from' point
    all_routes_[route_name]->route.push_back(to_point);
    return true;
}

void OrienteeringMap::print_map() const
{
    cout << " ";
    for (int x = 1; x <= width_; ++x) {
        if (x < 10)
        {
            cout << "  " << x; // Column number
        }
        else
        {
            cout << " " << x; // Column number
        }
    }
    cout << endl;

    // Print each row
    for (int y = 1; y <= height_; ++y) {
        if (y < 10)
        {
            cout << " " << y << "  ";  // Row number
        }
        else
        {
            cout  << y << "  ";  // Row number
        }
        for (int x = 1; x <= width_; ++x) {
            bool found = false;
            // Print point marker if on point
            // Iterate point names and pointers in all_points map
            for (const auto& [name, point_p] : all_points_) {
                // Check if marker on point
                if (point_p->get_x() == x && point_p->get_y() == y) {
                    cout << point_p->get_marker() << "  ";  // Print marker
                    found = true;
                    break;
                }
            }
            // Print dot if no marker on point
            if (!found) {
                cout << ".  ";
            }
        }
        cout << endl;
    }
}

void OrienteeringMap::print_routes() const
{
    cout << "Routes:" << endl;
    // Iterate through all routes in all_routes_
    for (const auto& [name, route] : all_routes_) {
        cout << " - " << name << endl;
    }
}

void OrienteeringMap::print_points() const
{
    cout << "Points:" << endl;
    // Iterate through all points in all_points_
    for (const auto& [name, point] : all_points_) {
        cout << " - "
             << name
             << " : "
             << point->get_marker()
             << endl;
    }
}

void OrienteeringMap::print_route(const string &name) const
{
    // Find the route with the given name in the map all_routes_
    auto route_map_elem = all_routes_.find(name);
    // Check if the given route name does not exist in the map all_routes_
    if (route_map_elem == all_routes_.end()) {
        cout << "Error: Route named " << name << " can't be found" << endl;
        return;
    }

    // Retrieve the Route struct associated with the key in route_map
    const auto& route = route_map_elem->second;

    // Loop through all points in the route, start from the first point
    for (size_t i = 0; i < route->route.size(); ++i) {
        const auto& point = route->route[i];

        // Print first point without an arrow
        if (i == 0) {
            cout << point->get_name() << endl;
        }
        // Print subsequent points with an arrow
        else {
            cout << " -> " << point->get_name() << endl;
        }
    }
}

// Prints length of given route
void OrienteeringMap::route_length(const string &name) const
{
    // Get map element in map of of all_routes_ with given name
    auto route_map_elem = all_routes_.find(name);

    // Check if the route with the given name does not exist in all_routes_
    if (route_map_elem == all_routes_.end()) {
        cout << "Error: Route named " << name << " can't be found" << endl;
        return;
    }

    // Get route pointer from the map element
    const auto& route_p = route_map_elem->second;
    double total_length = 0.0;

    // Get a reference to the vector of points in the current route
    const auto& points = route_p->route;

    // Iterate through the route points starting from the second point
    for (size_t i = 1; i < points.size(); ++i) {
        auto point1 = points[i - 1];
        auto point2 = points[i];

        // Skip iteration if either point1 or point2 is a null pointer
        if (!point1 || !point2) continue;

        // Retrieve the x and y coordinates of the points
        int x1 = point1->get_x(), y1 = point1->get_y();
        int x2 = point2->get_x(), y2 = point2->get_y();

        // Calculate and accumulate the Euclidean distance
        // between consecutive points
        total_length += sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    // Print route name and length
    cout << "Route " << name << " length was ";
    if (total_length >= 10) {
        // Round to nearest integer when 10 or higher
        cout << static_cast<int>(round(total_length)) << endl;
    } else {
        // Keep 1 decimal
        cout << fixed << setprecision(1) << total_length << endl;
    }
}

// Prints the height of greatest rise after given point, untill decline,
// on all routes with that rise, and prints the route names
// zero rise is skipped
void OrienteeringMap::greatest_rise(const string& point_name) const {
    // Check if the given point exists in all_points_
    if (all_points_.find(point_name) == all_points_.end()) {
        // Print an error and return if not found
        cout << "Error: Point named " << point_name << " can't be found" << endl;
        return;
    }

    int start_height = all_points_.at(point_name)->get_height();
    int greatest_rise = 0;
    vector<string> best_routes;

    // Iterate through all routes in the all_routes_ map
    for (const auto& [route_name, route] : all_routes_)
    {
        // Find the iterator pointing to the first occurrence of
        // point_name in the route
        auto point_p = find_if(route->route.begin(), route->route.end(),
                          [&point_name](const shared_ptr<Point>& p)
                          { return p->get_name() == point_name; });
        // If the point is not found in the route, skip to the next route
        if (point_p == route->route.end()) {
            continue;
        }

        int current_lowest = start_height;
        int current_rise = 0;

        // Iterate through the remaining points in the route,
        // starting from the next point
        for (++point_p; point_p != route->route.end(); ++point_p) {
            // Retrieve next height in route
            int next_height = (*point_p)->get_height();

            if (next_height < current_lowest) {
                // Stop when a decline happens
                break;
            }

            // Calculate the rise in height
            // from the starting point to the current point.
            current_rise = next_height - current_lowest;

            // Check if the current rise is greater
            // than the previously recorded greatest rise.
            if (current_rise > greatest_rise) {
                // Update greatest_rise to the new highest rise found
                greatest_rise = current_rise;
                // Clear the list of best routes
                best_routes.clear();
                // Add new route in best_routes
                best_routes.push_back(route_name);
            // Check if the current rise is equal greatest rise
            } else if (current_rise == greatest_rise) {
                // Add new route in best_routes
                best_routes.push_back(route_name);
            }
        }
    }
    // Check if there is any rise greater than zero after the given point
    if (greatest_rise > 0) {
        cout << "Greatest rise after point " << point_name << ", "
             << greatest_rise << " meters, is on route(s):" << endl;
        // Iterate through all routes in the best_routes list
        for (const auto& route : best_routes) {
            cout << " - " << route << endl;
        }
    } else {
        cout << "No route rises after point " << point_name << endl;
    }
}
