// #include <string>
#include "Customer.h"
#include "Restaurant.h"
#ifndef __Transaction_H__
#define __Transaction_H__

bool Pay(Customer **customer, Restaurant **restaurent, int price);

int Tip(int price, int option);

#endif