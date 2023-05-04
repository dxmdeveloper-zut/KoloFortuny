#include "TextAndIO.hpp"
#include <codecvt>
#include <string.h>
#include <cwchar>

void TextAndIO::setConsole_utf8(){
    std::ios_base::sync_with_stdio(false);
    std::cout.imbue(std::locale("C.utf8"));
    std::cin.imbue(std::locale("C.utf8"));
    std::wcin.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t> ));
    std::wcout.imbue(std::locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t> ));
}
bool TextAndIO::isWCharVowel(wchar_t ch){
    return wcschr(L"aąeęiouóy", towlower(ch)) ? true : false;
}

wchar_t TextAndIO::getInputWChar()
{
    std::wstring letter;
    std::wcin >> letter;
    
    while (letter.length() != 1)
    {
        std::cout << std::endl << "Type a single letter and press <enter>: ";
        std::wcin >> letter;
    }

    return letter[0];

}

static std::string _setColorEsc(const TextAndIO::RGB& color, char mode){
    char command[] = "\033[%hhu;2;%hhu;%hhu;%hhum";
    sprintf(command, command, mode, color.red, color.green, color.blue);
    std::string text(command);
    return text;
}
std::string TextAndIO::setTextColorEsc(const TextAndIO::RGB& color){
    return _setColorEsc(color, 38);
}
std::string TextAndIO::setBackgroundColorEsc(const TextAndIO::RGB& color){
    return _setColorEsc(color, 48);
}
std::string TextAndIO::resetStylesEsc(){
    return "\033[0m";
}

std::wstring TextAndIO::wcstolower(std::wstring wcstr){
    for(auto &chr : wcstr){
        chr = towlower(chr);
    }
    return wcstr;
}