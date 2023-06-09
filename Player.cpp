#include "Player.hpp"
#include <iostream>

Player::Player(std::string name) : name{name}{}

std::string Player::getName() const{
    return this->name;
}
void Player::addMoney(int money){
    this->money += money;
}
void Player::setMoney(int money){
    this->money = money;
}
int Player::getMoney() const{
    return this->money;
}
void Player::moveMoneyToAccount(){
    this->account = this->money;
    this->money = 0;
}
int Player::getAccountMoney() const{
    return this->account;
}

void Player::operator+=(int a){
    this->addMoney(a);
}
void Player::operator-=(int a){
    this->addMoney(a * -1);
}
void Player::operator&=(int a){
    this->setMoney(a);
}
void Player::operator>>=(int accountMoney){
    this->account += accountMoney;
}


std::ostream& operator << (std::ostream& os, const Player& player){
    os << player.getName() << ": " << player.getMoney() << "\tkonto: " << player.getAccountMoney();
    return os;
}