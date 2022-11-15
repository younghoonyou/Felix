#include "Restaurant.h"
Restaurant *Restaurant::Instance = NULL;
Restaurant *Restaurant::GetInstance(std::string acc_){
    if(!Instance){
        Instance = new Restaurant(acc_);
    }
    return Instance;
}
std::string Restaurant::GetRestaurantAccount(){
    return this->acc;
}
float Restaurant::GetRestaurantBalance(){
    return this->balance;
}