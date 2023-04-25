#pragma once
#include <string>

// No dynamic memory alloc
class Player {
    public:
    Player(std::string name);

    std::string getName() const;
    void addMoney(int money);
    void setMoney(int money);
    int getMoney() const;
    void moveMoneyToAccount();
    int getAccountMoney() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    private:
    std::string name;
    int money;
    int account;
};

std::ostream& operator<<(std::ostream& os, const Player& player);