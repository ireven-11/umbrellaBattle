#include"DxLib.h"
#include"resultUI.h"

ResultUI::ResultUI(const char* fontName)
{
	fontHandle_ = CreateFontToHandle(fontName, 200, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

ResultUI::~ResultUI()
{
}

void ResultUI::update(short winPlayer)
{
	DrawFormatStringToHandle(winner_text_position_.x, winner_text_position_.y, GetColor(255, 255, 255), fontHandle_, "Winner %dP!!!", winPlayer);
}