#include "queue.hh"
#include <iostream>
// Implement the member functions of Queue here
using namespace std;

Queue::Queue(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::enqueue(const string &reg)
{
    shared_ptr<Vehicle> new_vehicle = make_shared<Vehicle>();

    new_vehicle->reg_num = reg;
    if (color_ == "GREEN: ")
    {
        cout << color_ << "The vehicle " << reg << " need not stop to wait" << endl;
    }
    else
    {
        if (!first_)
        {
            first_ = new_vehicle;
            last_ = new_vehicle;
        }
        else
        {
            last_->next = new_vehicle;
            last_ = new_vehicle;

        }
    }
}

void Queue::switch_light()
{
    if (color_ == "GREEN: ")
    {
        color_ = "RED: ";
    }
    else
    {
        color_ = "GREEN: ";
    }
    if (!first_)
    {
        cout << color_ << "No vehicles waiting in traffic lights" << endl;
    }
    else
    {
        cout << color_ << "Vehicle(s) ";
        while (passed_in_cycle_ < cycle_ && first_)
        {
            cout << first_->reg_num << " ";
            first_ = first_->next;
            passed_in_cycle_++;
        }
        cout << "can go on" << endl;
        color_ = "RED: ";
    }
    if (!first_)
    {
        last_ = first_;
    }
    passed_in_cycle_ = 0;
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    shared_ptr<Vehicle> tmp = first_;

    if (!first_)
    {
        cout << color_ << "No vehicles waiting in traffic lights" << endl;
    }
    else
    {
        cout << color_ << "Vehicle(s) ";
        while (tmp != nullptr)
        {
            cout << tmp->reg_num << " ";
            tmp = tmp->next;
        }
        cout << "waiting in traffic lights" << endl;
    }
}
