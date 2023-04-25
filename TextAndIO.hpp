#include <iostream>
#include <string>

namespace TextAndIO {
    typedef struct RGB {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    } RGB;

    bool isWCharVowel(wchar_t ch); // samogłoska
    void setConsole_utf8();
    wchar_t getInputWChar();

    std::string setTextColorEsc(const TextAndIO::RGB& color);
    std::string setBackgroundColorEsc(const TextAndIO::RGB& color);
    std::string resetStylesEsc();

    std::wstring wcstolower(std::wstring wcstr);
}
