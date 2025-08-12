#include"DxLib.h"
#include"charaBase.h"
#include"playUI.h"

PlayUI::PlayUI(const char* fontName)
{
	fontHandle_ = CreateFontToHandle(fontName, 100, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	umbrella1_	= LoadGraph("graph/black.png");
	umbrella2_	= LoadGraph("graph/skyblue.png");
	umbrella3_	= LoadGraph("graph/orange.png");
	umbrella4_	= LoadGraph("graph/pink.png");
	hpEmpty_	= LoadGraph("graph/hpEmpty.png");
	hp_			= LoadGraph("graph/hp.png");

	hpPosition_			= hp__init_position;
	hpEmptyPosition_	= hp_empty_init_position;
	umbrellaPosition_	= umbrella_init_position;
}

PlayUI::~PlayUI()
{
	DeleteFontToHandle(fontHandle_);
	DeleteGraph(umbrella1_);
	DeleteGraph(umbrella2_);
	DeleteGraph(umbrella3_);
	DeleteGraph(umbrella4_);
	DeleteGraph(hpEmpty_);
	DeleteGraph(hp_);
}

void PlayUI::update(std::shared_ptr<CharaBase> chara, int playerNumber)
{
	//傘表示
	switch (playerNumber)
	{
	case 0:
		DrawExtendGraph(umbrellaPosition_.x  + (adjust_umbrella_x * (playerNumber + 1)), umbrellaPosition_.y,
			umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * (playerNumber + 1)), umbrellaPosition_.y + umbrella_height, umbrella1_, TRUE);
		break;

	case 1:
		DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * (playerNumber + 1)), umbrellaPosition_.y,
			umbrellaPosition_.x  + umbrella_width + (adjust_umbrella_x * (playerNumber + 1)), umbrellaPosition_.y + umbrella_height, umbrella2_, TRUE);
		break;

	case 2:
		DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * (playerNumber + 1)), umbrellaPosition_.y,
			umbrellaPosition_.x  + umbrella_width + (adjust_umbrella_x * (playerNumber + 1)), umbrellaPosition_.y + umbrella_height, umbrella3_, TRUE);
		break;

	case 3:
		DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * (playerNumber + 1)), umbrellaPosition_.y,
			umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * (playerNumber + 1)), umbrellaPosition_.y + umbrella_height, umbrella4_, TRUE);
		break;
	}
	
	//ゲージ表示
	DrawExtendGraph(hpEmptyPosition_.x + (adjust_hp_empty_x * (playerNumber + 1)), hpEmptyPosition_.y,
		hpEmptyPosition_.x+ hp_empty_width + (adjust_hp_empty_x * (playerNumber + 1)), hpEmptyPosition_.y + hp_empty_height, hpEmpty_, TRUE);
	DrawExtendGraphF(hpPosition_.x + (adjust_hp__x * (playerNumber + 1)), hpPosition_.y,
		hpPosition_.x + (chara->Gethp_() * hp__width) / max_hp + (adjust_hp__x * (playerNumber + 1)), hpPosition_.y + hp__height, hp_, TRUE);

	//ラッパ
	if (chara->Gethp_() <= 0)
	{
		DrawStringToHandle(umbrellaPosition_.x + (adjust_umbrella_x * (playerNumber + 1)), umbrellaPosition_.y, "ラッパ!!", GetColor(255, 50, 0), fontHandle_);
	}
	else
	{
		//～P表示
		DrawFormatStringToHandle(umbrellaPosition_.x + (adjust_umbrella_x * (playerNumber + 1)), umbrellaPosition_.y, GetColor(255, 255, 255), fontHandle_, "%dP", playerNumber + 1);
	}
}