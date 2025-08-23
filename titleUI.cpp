#include"DxLib.h"
#include"titleUI.h"
#include"DrawBrinkStringToHandle.h"

TitleUI::TitleUI(const char* fontName)
{
    fontHandle_         = CreateFontToHandle(fontName, 100, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
    fontHandleSize200_  = CreateFontToHandle(fontName, 159, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

TitleUI::~TitleUI()
{
    DeleteFontToHandle(fontHandle_);
    DeleteFontToHandle(fontHandleSize200_);
}

void TitleUI::update()
{
    DrawStringToHandle(475, 300, "UmbreRumble", GetColor(255, 255, 255), fontHandleSize200_);

    DrawBrinkStringToHandle(start_text_position, "Enterでプレイスタート", GetColor(255, 50, 0), fontHandle_);
}