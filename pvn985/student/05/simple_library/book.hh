#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"
#include <string>

using namespace std;

class Book
{
public:
    Book(const string& author, const string& title);
    ~Book();

    void loan(const Date& loan_date);

    void renew();

    void give_back();

    void print() const;

private:
    string author_;
    string title_;
    Date loan_date_;
    Date due_date_;
    bool is_loaned_ = false;
};

#endif // BOOK_HH
