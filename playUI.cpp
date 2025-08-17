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
	AbuttonUI_	= LoadGraph("graph/A.png");
	LstickUI_	= LoadGraph("graph/Lstick.png");
	LTbuttonUI_ = LoadGraph("graph/LT.png");
	RTbuttonUI_ = LoadGraph("graph/RT.png");

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
	DeleteGraph(AbuttonUI_);
	DeleteGraph(LstickUI_);
	DeleteGraph(LTbuttonUI_);
	DeleteGraph(RTbuttonUI_);
}

void PlayUI::update(std::shared_ptr<CharaBase> chara, int playerNumber)
{
	playerUI(chara, playerNumber);

	buttonUI();
}

void PlayUI::buttonUI()
{
	DrawExtendGraph(A_ui_position.x, A_ui_position.y, A_ui_position.x + button_ui_width, A_ui_position.y + button_ui_height, AbuttonUI_, TRUE);
	DrawExtendGraph(Lstick_ui_position.x, Lstick_ui_position.y, Lstick_ui_position.x + button_ui_width, Lstick_ui_position.y + button_ui_height, LstickUI_, TRUE);
	DrawExtendGraph(LT_ui_position.x, LT_ui_position.y, LT_ui_position.x + button_ui_width, LT_ui_position.y + button_ui_height / 2, LTbuttonUI_, TRUE);
	DrawExtendGraph(RT_ui_position.x, RT_ui_position.y, RT_ui_position.x + button_ui_width, RT_ui_position.y + button_ui_height / 2, RTbuttonUI_, TRUE);
}

void PlayUI::playerUI(std::shared_ptr<CharaBase> chara, int playerNumber)
{
	//傘表示
	switch (playerNumber)
	{
	case 1:
		DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
			umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, umbrella1_, TRUE);
		break;

	case 2:
		DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
			umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, umbrella2_, TRUE);
		break;

	case 3:
		DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
			umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, umbrella3_, TRUE);
		break;

	case 4:
		DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
			umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, umbrella4_, TRUE);
		break;
	}

	//ゲージ表示
	DrawExtendGraph(hpEmptyPosition_.x + (adjust_hp_empty_x * playerNumber), hpEmptyPosition_.y,
		hpEmptyPosition_.x + hp_empty_width + (adjust_hp_empty_x * playerNumber), hpEmptyPosition_.y + hp_empty_height, hpEmpty_, TRUE);
	DrawExtendGraphF(hpPosition_.x + (adjust_hp__x * playerNumber), hpPosition_.y,
		hpPosition_.x + (chara->Gethp_() * hp__width) / max_hp + (adjust_hp__x * playerNumber), hpPosition_.y + hp__height, hp_, TRUE);

	//ラッパ
	if (chara->Gethp_() <= 0)
	{
		DrawStringToHandle(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y, "ラッパ!!", GetColor(255, 50, 0), fontHandle_);
	}
	else
	{
		//～P表示
		DrawFormatStringToHandle(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y, GetColor(255, 255, 255), fontHandle_, "%dP", playerNumber);
	}
}