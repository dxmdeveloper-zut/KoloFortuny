#include "Game.hpp"
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <codecvt>
#include "TextAndIO.hpp"

int main(){
    std::wifstream file("dane.txt");
    file.imbue(std::locale(std::locale("C.utf8"), new std::codecvt_utf8<wchar_t>));

    Game game(file);
    game.addPlayer("Zbigniew");
    game.addPlayer("Agata");
    game.addPlayer("Jan");
    // IO console setup
    TextAndIO::setConsole_utf8();

    game.runGame();
    return 0;
}