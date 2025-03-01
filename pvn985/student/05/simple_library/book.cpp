#include "book.hh"
#include <iostream>

const int LOAN_PERIOD = 28;

Book::Book(const string& author, const string& title) :
    author_(author), title_(title)
{

}

Book::~Book()
{

}

void Book::loan(const Date& loan_date)
{
    if (is_loaned_)
    {
        cout << "Already loaned: cannot be loaned" << endl;
        return;
    }

    is_loaned_ = true;
    loan_date_ = loan_date;
    due_date_ = loan_date;
    due_date_.advance(LOAN_PERIOD);
}

void Book::renew()
{
    if (is_loaned_)
    {
        due_date_.advance(LOAN_PERIOD);
    }
    else
    {
        cout << "Not loaned: cannot be renewed" << endl;
    }
}

void Book::give_back()
{
    is_loaned_ = false;
}

void Book::print() const
{
    cout << author_ << " : " << title_ << endl;
    if (is_loaned_)
    {
        cout << "- loaned: ";
        loan_date_.print();
        cout << "- to be returned: ";
        due_date_.print();
    }
    else
    {
        cout << "- available" << endl;
    }
}
