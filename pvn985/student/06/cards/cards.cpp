#include <iostream>
#include "cards.hh"

using namespace std;

Cards::Cards(): top_(nullptr)
{
    std::cout << "constructor" << std::endl;
}

Cards::~Cards()
{
    std::cout << "destructor" << std::endl;
}

void Cards::add(int id)
{
    shared_ptr<Card_data> new_card =
        make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

bool Cards::remove(int &id)
{
    if (top_ == nullptr)
    {
        return false;
    }
    id = top_->data;
    top_ = top_->next;

    return true;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    shared_ptr<Card_data> current = top_;
    int nr = 1;

    while (current != nullptr)
    {
        s << nr << ": " << current->data << endl;
        current = current->next;
        ++nr;
    }
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    recursive_print(top_, s);
}

bool Cards::top_to_bottom()
{
    if (top_ == nullptr)
    {
        return false;
    }
    if (top_->next == nullptr)
    {
        return true;
    }
    shared_ptr<Card_data> first = top_;
    top_ = top_->next;
    shared_ptr<Card_data> last = top_;
    while (last->next != nullptr)
    {
        last = last->next;
    }
    last->next = first;
    first->next = nullptr;

    return true;
}

void Cards::reverse()
{
    shared_ptr<Card_data> reversed_deck_top = nullptr;

    while (top_ != nullptr)
    {
        shared_ptr<Card_data> moved_card = top_;
        top_ = top_->next;
        if (reversed_deck_top == nullptr)
        {
            moved_card->next = nullptr;
            reversed_deck_top = moved_card;
        }
        else
        {
            moved_card->next = reversed_deck_top;
            reversed_deck_top = moved_card;
        }
    }
    top_ = reversed_deck_top;
}

int Cards::recursive_print(std::shared_ptr<Card_data> printable, std::ostream &s)
{
    if (printable == nullptr)
    {
        return 1;
    }

    int running_nr = recursive_print(printable->next, s);
    s << running_nr << ": " << printable-> data << endl;

    return running_nr + 1;
}
