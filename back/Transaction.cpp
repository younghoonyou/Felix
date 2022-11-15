#include "Transaction.h"

bool Pay(Customer **customer,Restaurant **restaurent, int price)
{
    Customer *cust = (*customer);
    Restaurant *rest = (*restaurent);
    std::string restAcc = rest->GetRestaurantAccount();
    price = Tip(price, 1);
    if (CheckCustomerBalance(price, &cust)){
        cust->balance -= price;
        return true;
    }
    return false;
}

int Tip(int price, int option)
{
    switch (option)
    {
    case 0:
        break;
    case 1:
        price *= 1.15;
        break;
    case 2:
        price *= 1.20;
        break;
    case 3:
        price *= 1.25;
        break;
    }
    return price;
}