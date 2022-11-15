#include "../lib/Restaurant.h"
Restaurant *Restaurant::Instance = NULL;
Restaurant *Restaurant::GetInstance(std::string RestId_, std::string acc_, float balance_)
{
    if(!Instance){
        Instance = new Restaurant(RestId_,acc_,balance_);
    }
    return Instance;
}
std::string Restaurant::GetRestaurantAccount(){
    return this->acc;
}
float Restaurant::GetRestaurantBalance(){
    return this->balance;
}