#include "Game.hpp"
#include "TextAndIO.hpp"
#include "Player.hpp"
#include <cstddef>
#include <cstdio>
#include <cwchar>
#include <exception>
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>

const wchar_t unmaskedCharacters[] = L"~`;':[{}]-_+=\\|/?<,.>()!@#$%^&* ";

template<typename T>
static T getRandomInt(T min, T max){
    static std::random_device rd;
    std::uniform_int_distribution<T> dist(min, max);
    std::mt19937 mt(rd());
    return dist(mt);
}


Game::Game(std::wifstream &file){
    this->loadDictionary(file);
}

Game::~Game(){
   this->deleteCheckedMap();
}

void Game::deleteCheckedMap(){
     if(this->checkedLettersMap) 
        delete [] this->checkedLettersMap;
}
void Game::allocCheckedMap(){
    if(this->checkedLettersMap)
        this->deleteCheckedMap();
    this->checkedLettersMap = new bool[383](); // Unicode Latin Extended-A
}

void Game::runGame(){
    // main loop
    for(;;this->round = 0){
        // choosing random word
        this->wordIndex = getRandomInt<size_t>(0, this->dictionary.size() -1); 
        std::wstring correctWord = TextAndIO::wcstolower(this->dictionary[this->wordIndex]);
        // checked letters map renew
        this->allocCheckedMap();

        // --- round loop ---
        for(bool isWordGuessed = false; !isWordGuessed; this->round++){
            Player *cuPlayer = &this->players[this->round % this->players.size()];
            //display players
            this->printPlayers();
            std::wcout << this->getMask() << std::endl << std::endl;
            
            switch(this->giveChoice()){
                case L'1':{
                    // 1. Zgaduj hasło
                    std::wstring guess;
                    std::wcin.ignore();
                    std::getline(std::wcin, guess);
                    if(TextAndIO::wcstolower(guess) == correctWord){
                        this->printWinText(cuPlayer->getMoney());
                        *cuPlayer>>=cuPlayer->getMoney();
                        isWordGuessed = true;
                    }
                } break;

                case L'2':{
                    this->spinAndGuessVowelAIO(correctWord, cuPlayer);
                } break;

                case L'e':{
                    std::cout << "Dziękujemy za grę!\n";
                    exit(0);
                } break;
            }
        }
        for(auto &player : players){
            player&=0;
        }
    }
}

void Game::spinAndGuessVowelAIO(const std::wstring &correctword, Player *cuPlayer){
    int reward = this->spin();
    switch(reward){
        case -1: 
            cuPlayer->setMoney(0);
            std::cout << "Bankrut!!!\n"; 
            break;
        case  0:
            std::cout << "Utrata kolejki\n";
            break;
        default: {
            std::cout << "grasz o " << reward << "\n";
            std::cout << "podaj spółgłoskę: ";
            wchar_t letter = this->guessVowelGetInput(correctword);

            this->checkedLettersMap[letter] = true;
            std::wstring::difference_type n = 0;
            if((n = std::count(correctword.begin(),correctword.end(), letter))){
                this->printCorrectLetterText();
                *cuPlayer += reward * n;
            }
            else {
                this->printIncorrectLetterText();
            }
        } break;
    }
}

wchar_t Game::guessVowelGetInput(const std::wstring &correctWord) const {
    wchar_t letter = towlower(TextAndIO::getInputWChar());
                            
    while(true){
        if(TextAndIO::isWCharVowel(letter))
            std::cout << "Podano samogłoskę! ";
        else if (letter > 383)
            std::cout << "Twoja litera nie jest obsługiwana. ";
        else if (this->checkedLettersMap[letter] && correctWord.find(std::wstring()+letter) != -1)
            std::cout << "Litera została już wcześniej odgadnięta! ";
        else 
            break; // correct letter => exit loop
        
        std::cout << "Spróbuj jeszcze raz.";
        letter = towlower(TextAndIO::getInputWChar());
    }
    return letter;
}

void Game::loadDictionary(std::wifstream &file){
    std::wstring line;
    while(std::getline(file, line, L'\n')){
        /*for(wchar_t c : line){
            std::wcout << c;
        }*/
        if(line.length() > 2){
            this->dictionary.push_back(line); 
        }
    }
}

void Game::addPlayer(std::string name){
    Player player(name); // no dynamic allocation in class player
    this->players.push_back(player);
}

void Game::printIncorrectLetterText() const {
    std::cout << TextAndIO::setTextColorEsc({255, 0, 0});
    std::cout << "-------------------------------------------------------\n";
    std::cout << "=================    !!! ŹLE !!!    ===================\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << TextAndIO::resetStylesEsc();
}

void Game::printCorrectLetterText() const{
    std::cout << TextAndIO::setTextColorEsc({5, 255, 20});
    std::cout << "-------------------------------------------------------\n";
    std::cout << "====================    DOBRZE    =====================\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << TextAndIO::resetStylesEsc();
}

void Game::printPlayers() const{
    size_t i = 0;
    for(auto &player : this->players){
        if(this->round % this->players.size() == i){
            std::cout << TextAndIO::setTextColorEsc({0,0,255});
            std::cout << player << std::endl;
            std::cout << TextAndIO::resetStylesEsc();
        }
        else std::cout << player << std::endl;
        i++;
    }
}

void Game::printWinText(int kwota) const {
    std::cout << TextAndIO::setTextColorEsc({5, 255, 20});
    std::cout << "\n\n-------------------------------------------------------\n";
    std::cout << "===============  Gratulacje, Wygrałeś  ================\n\n";
    std::cout << "|+| przyznana kwota to: " << kwota << " eurogąbek!!!\n";
    std::cout << "-------------------------------------------------------\n\n";
    std::cout << TextAndIO::resetStylesEsc();
}

std::wstring Game::getMask() const {
    std::wstring mask = this->dictionary[this->wordIndex];
    for(auto &c : mask){
        //wchar_t is unsigned
        if(c < 382)
            if(!this->checkedLettersMap[towlower(c)] && !wcschr(unmaskedCharacters, c)) 
                c = '_';
    }
    return mask;
}

wchar_t Game::giveChoice() const {
    std::cout   <<  "1. Zgaduj hasło" 
    << std::endl << "2. Zakręć kołem" 
    << std::endl << "e. Wyjdź z gry\n";

    wchar_t choice = towlower(TextAndIO::getInputWChar());
    while(!std::wcschr(L"12e", choice)){
        std::cout << "Dokonałeś złego wyboru! spróbuj jeszcze raz\n";
        choice = towlower(TextAndIO::getInputWChar());
    }
    return choice;
}

int Game::spin(){    
    size_t r = getRandomInt<size_t>(0, sizeof(this->rewards) / sizeof(this->rewards[0]) - 1);

    return rewards[r];
}