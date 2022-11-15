#include <string>
#include <memory>
#ifndef __Restaurant_H__
#define __Restaurant_H__
class Restaurant{
private:
    static Restaurant *Instance;
    Restaurant(std::string acc_) : balance(0) ,acc(acc_){};
    Restaurant(std::string RestId_, std::string acc_, float balance_) : balance(balance_), acc(acc_), RestId(RestId_){};
    float balance;

public:
    std::string acc;
    std::string RestId;
    static Restaurant *GetInstance(std::string RestId_, std::string acc_, float balance_);
    std::string GetRestaurantAccount();
    float GetRestaurantBalance();
};
#endif