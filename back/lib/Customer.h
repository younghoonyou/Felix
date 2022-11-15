#include "Restaurant.h"
#ifndef __Customer_H__
#define __Customer_H__
struct Customer{
    float balance;
    std::string acc;
    std::string userId;
    Customer(std::string userId_, std::string acc_, float balance_);
};

bool CheckCustomerBalance(float price, Customer **customer);

#endif