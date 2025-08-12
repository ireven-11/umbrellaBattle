#include"DxLib.h"
#include"titleUI.h"

TitleUI::TitleUI(const char* fontName)
{
    fontHandle_ = CreateFontToHandle(fontName, 70, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

TitleUI::~TitleUI()
{

}

void TitleUI::update()
{
    DrawString(200, 200, "‚½‚¢‚Æ‚é", GetColor(255, 255, 255));

    DrawStringToHandle(500, 600, "Enter TO START", GetColor(255, 50, 0), fontHandle_);
}