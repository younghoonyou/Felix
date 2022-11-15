#include "../lib/Customer.h"

Customer::Customer(std::string userId_, std::string acc_, float balance_){
    this->acc = acc_;
    this->balance = balance_;
    this->userId = userId_;
}

bool CheckCustomerBalance(float price, Customer **customer){
    Customer *check = (*customer);
    int remain = check->balance;
    return (remain - price> 0);
}