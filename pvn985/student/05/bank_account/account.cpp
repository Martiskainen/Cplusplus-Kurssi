#include "account.hh"
#include <iostream>

using namespace std;

Account::Account(const std::string& owner, bool has_credit) :
    has_credit_(has_credit), owner_(owner)
{
    generate_iban();
}


// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::print()
{
    cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << endl;
}

void Account::set_credit_limit(int set_limit)
{
    if (has_credit_)
    {
        credit_limit_ = set_limit;
    }
    else
    {
        cout << "Cannot set credit limit: the account has no credit card" << endl;
    }
}

void Account::save_money(int save)
{
    balance_ += save;
}

void Account::take_money(int take)
{
    if (balance_ >= take || (has_credit_ && credit_limit_ > abs(balance_ - take)))
    {
        balance_ -= take;
        cout << take << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << endl;
    }
    else
    {
        cout << "Cannot take money: balance underflow\n";
    }
}

void Account::transfer_to(Account& to_account, int transfer_amount)
{
    if (balance_ >= transfer_amount || (has_credit_ && credit_limit_ > abs(balance_ - transfer_amount)))
    {
        balance_ -= transfer_amount;
        to_account.save_money(transfer_amount);
        cout << transfer_amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << endl;
    }
    else
    {
        cout << "Cannot take money: balance underflow" << endl;
    }
}

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
