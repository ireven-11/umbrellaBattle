#include"DxLib.h"
#include"resultUI.h"
#include"DrawBrinkStringToHandle.h"

ResultUI::ResultUI(const char* fontName)
{
	fontHandle_ = CreateFontToHandle(fontName, 250, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	fontHandleSize100_ = CreateFontToHandle(fontName, 100, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

ResultUI::~ResultUI()
{
}

void ResultUI::update(short winPlayer)
{
	DrawFormatStringToHandle(winner_text_position_.x, winner_text_position_.y, GetColor(225, 225, 50), fontHandle_, "Winner %dP!!!", winPlayer);

	DrawBrinkStringToHandle(return_title_text_position_, "Enter‚Åƒ^ƒCƒgƒ‹‚Ö–ß‚é", GetColor(255, 255, 255), fontHandleSize100_);
}