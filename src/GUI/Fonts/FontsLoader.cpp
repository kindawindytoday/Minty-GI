#include "FontsLoader.h"
#include <iostream>

bool FontsLoader::LoadFont(int resourceNum, float fontSize, ImFontConfig* fontConfig, int fontId, const ImWchar* fontRanges)
{
    void* fontData = 0;
    DWORD fontDataSize = 0;
    
    if (!ResourceLoader::Instance().LoadResourceToMemory(MAKEINTRESOURCEA(resourceNum), MAKEINTRESOURCEA(10), fontData, fontDataSize)) {
        printf("LOAD FONT ERROR! FONT #%i (%i)\n", resourceNum, GetLastError());
        return false;
    }
    //printf("Adding...\n");
    auto font = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fontData, fontDataSize, fontSize, fontConfig, fontRanges);

    this->FontsMap[fontId] = font;

    return true;
}
