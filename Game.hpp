#pragma once

#include <cstddef>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "Player.hpp"

class Game {
    public:

    Game(std::wifstream &file);
    ~Game();
    void runGame();
    void addPlayer(std::string name);

    // -1 bankrut
    // 0 strata kolejki
    static constexpr int rewards[] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 };

    private:
    std::vector<Player> players;
    std::vector<std::wstring> dictionary;
    size_t wordIndex = 0;
    int round = 0;
    bool *checkedLettersMap = nullptr; 

    void loadDictionary(std::wifstream &file);
    void deleteCheckedMap();
    void allocCheckedMap();
    

    // text print
    void printCorrectLetterText() const;
    void printIncorrectLetterText() const;
    void printPlayers() const;
    void printWinText(int kwota) const;
    std::wstring getMask() const;

    wchar_t giveChoice() const;
    wchar_t guessVowelGetInput(const std::wstring &correctWord) const;

    void spinAndGuessVowelAIO(const std::wstring &correctword, Player *cuPlayer);

    /// @return prize
    int spin();
};
