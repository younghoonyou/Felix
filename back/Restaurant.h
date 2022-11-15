#include <string>
#include <memory>
#ifndef __Restaurant_H__
#define __Restaurant_H__
class Restaurant{
private:
    static Restaurant *Instance;
    Restaurant(std::string acc_) : acc(acc_),balance(0){};
    float balance;
public:
    std::string acc;
    std::string RestId;
    static Restaurant *GetInstance(std::string acc_);
    std::string GetRestaurantAccount();
    float GetRestaurantBalance();
};
#endif