#include "Game.hpp"
#include <fstream>
#include <iostream>
#include <locale>
#include "TextAndIO.hpp"

int main(){
    std::wifstream file("dane.txt");
    Game game(file);
    game.addPlayer("Zbigniew");
    game.addPlayer("Agata");
    game.addPlayer("Jan");
    // IO console setup
    TextAndIO::setConsole_utf8();

    game.runGame();
    return 0;
}