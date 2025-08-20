#include"DxLib.h"
#include"charaBase.h"
#include"playUI.h"

PlayUI::PlayUI(const char* fontName)
{
	fontHandle_			= CreateFontToHandle(fontName, 100, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	fontHandleSize60_	= CreateFontToHandle(fontName, 60, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	fontHandleSize30_	= CreateFontToHandle(fontName, 300, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
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
	trumpet_[0] = LoadGraph("graph/trumpetBlack.png");
	trumpet_[1] = LoadGraph("graph/trumpetSkyBlue.png");
	trumpet_[2] = LoadGraph("graph/trumpetOrange.png");
	trumpet_[3] = LoadGraph("graph/trumpetPink.png");

	hpPosition_			= hp__init_position;
	hpEmptyPosition_	= hp_empty_init_position;
	umbrellaPosition_	= umbrella_init_position;
}

PlayUI::~PlayUI()
{
	DeleteFontToHandle(fontHandle_);
	DeleteFontToHandle(fontHandleSize60_);
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
	DrawExtendGraph(LT_ui_position.x, LT_ui_position.y, LT_ui_position.x + button_ui_width, LT_ui_position.y + button_ui_height, LTbuttonUI_, TRUE);
	DrawExtendGraph(RT_ui_position.x, RT_ui_position.y, RT_ui_position.x + button_ui_width, RT_ui_position.y + button_ui_height, RTbuttonUI_, TRUE);

	DrawStringToHandle(action_text_position.x, action_text_position.y, ":�A�N�V����", GetColor(255, 255, 255), fontHandleSize60_);
	DrawStringToHandle(move_text_position.x, move_text_position.y, ":�ړ�", GetColor(255, 255, 255), fontHandleSize60_);
	DrawStringToHandle(left_turn_text_position.x, left_turn_text_position.y, ":����]", GetColor(255, 255, 255), fontHandleSize60_);
	DrawStringToHandle(right_turn_text_position.x, right_turn_text_position.y, ":�E��]", GetColor(255, 255, 255), fontHandleSize60_);
}


/**
 * 3D��Ԃɕ�������t�H���g�n���h�����g�p���ĕ`�悵�܂��B
 *
 * ������͎w�肳�ꂽ�ʒu�Ƀr���{�[�h�`���ŕ\������܂��B
 * �w�肳�ꂽ�t�H���g�n���h�����g�p���ĕ������`�悵�܂��B
 *
 * @param pos �������\������3D���W
 * @param str �\�����镶����
 * @param color �����F(0xRRGGBB�`��)
 * @param font_handle �g�p����t�H���g�̃n���h��
 * @param edge_color �G�b�W�̐F(0xAARRGGBB�`��)�B�f�t�H���g��0(�G�b�W�Ȃ�)
 * @param size �`�悷��r���{�[�h�̃T�C�Y�B
 */
static void DrawString3DToHandle(const VECTOR& pos, const char* str, // NOLINT(clang-diagnostic-unused-function)
	const unsigned int color, const int font_handle,
	const unsigned int edge_color = 0, const float size = 0.01f)
{
	int size_x, size_y, line_count;
	GetDrawStringSizeToHandle(&size_x, &size_y, &line_count, str, static_cast<int>(strlen(str)), font_handle);
	const int draw_screen = MakeScreen(size_x, size_y, TRUE);
	{
		const auto prev_draw_screen_setting = GetUseSetDrawScreenSettingReset();
		SetUseSetDrawScreenSettingReset(FALSE);
		{
			SetDrawScreen(draw_screen);
			DrawStringToHandle(0, 0, str, color, font_handle, edge_color);
			SetDrawScreen(DX_SCREEN_BACK);
		}
		SetUseSetDrawScreenSettingReset(prev_draw_screen_setting);
	}

	const auto billboard_size = static_cast<float>(size_x) * size;
	DrawBillboard3D(pos, 0.5f, 0.5f, billboard_size, 0, draw_screen, TRUE);
	DeleteGraph(draw_screen);
}


void PlayUI::playerUI(std::shared_ptr<CharaBase> chara, int playerNumber)
{
	//��@�̎���P�\��
	if (chara->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(chara->Getstate_()))
	{
		switch (playerNumber)
		{
		case 1:
			DrawString3DToHandle(VGet(chara->Getposition_().x, chara->Getposition_().y + 10.0f, chara->Getposition_().z), "1P", GetColor(255, 255, 255), fontHandleSize30_, GetColor(0, 0, 0), 0.01f);
			break;

		case 2:
			DrawString3DToHandle(VGet(chara->Getposition_().x, chara->Getposition_().y + 10.0f, chara->Getposition_().z), "2P", GetColor(255, 255, 255), fontHandleSize30_, GetColor(0, 0, 0), 0.01f);
			break;

		case 3:
			DrawString3DToHandle(VGet(chara->Getposition_().x, chara->Getposition_().y + 10.0f, chara->Getposition_().z), "3P", GetColor(255, 255, 255), fontHandleSize30_, GetColor(0, 0, 0), 0.01f);
			break;

		case 4:
			DrawString3DToHandle(VGet(chara->Getposition_().x, chara->Getposition_().y + 10.0f, chara->Getposition_().z), "4P", GetColor(255, 255, 255), fontHandleSize30_, GetColor(0, 0, 0), 0.01f);
			break;
		}
	}
	//���b�p
	if (chara->Gethp_() <= 0)
	{
		//�P�\��
		switch (playerNumber)
		{
		case 1:
			DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
				umbrellaPosition_.x + umbrella_width * 1.5f + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, trumpet_[0], TRUE);
			break;

		case 2:
			DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
				umbrellaPosition_.x + umbrella_width * 1.5f + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, trumpet_[1], TRUE);
			break;

		case 3:
			DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
				umbrellaPosition_.x + umbrella_width * 1.5f + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, trumpet_[2], TRUE);
			break;

		case 4:
			DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
				umbrellaPosition_.x + umbrella_width * 1.5f + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, trumpet_[3], TRUE);
			break;
		}
		//DrawStringToHandle(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y, "���b�p!!", GetColor(255, 50, 0), fontHandle_);
	}
	else
	{
		//�P�\��
		switch (playerNumber)
		{
		case 1:
			DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
				umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, umbrella1_, TRUE);
			DrawString3DToHandle(VGet(chara->Getposition_().x, chara->Getposition_().y + 5.0f, chara->Getposition_().z), "1P", GetColor(255, 255, 255), fontHandleSize30_, GetColor(0,0,0), 0.01f);
			break;

		case 2:
			DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
				umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, umbrella2_, TRUE);

			DrawString3DToHandle(VGet(chara->Getposition_().x, chara->Getposition_().y + 5.0f, chara->Getposition_().z), "2P", GetColor(255, 255, 255), fontHandleSize30_, GetColor(0, 0, 0), 0.01f);
			break;

		case 3:
			DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
				umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, umbrella3_, TRUE);

			DrawString3DToHandle(VGet(chara->Getposition_().x, chara->Getposition_().y + 5.0f, chara->Getposition_().z), "3P", GetColor(255, 255, 255), fontHandleSize30_, GetColor(0, 0, 0), 0.01f);
			break;

		case 4:
			DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
				umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, umbrella4_, TRUE);
			DrawString3DToHandle(VGet(chara->Getposition_().x, chara->Getposition_().y + 5.0f, chara->Getposition_().z), "4P", GetColor(255, 255, 255), fontHandleSize30_, GetColor(0, 0, 0), 0.01f);
			break;
		}
		//�`P�\��
		DrawFormatStringToHandle(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y, GetColor(255, 255, 255), fontHandle_, "%dP", playerNumber);
	}

	//�Q�[�W�\��
	DrawExtendGraph(hpEmptyPosition_.x + (adjust_hp_empty_x * playerNumber), hpEmptyPosition_.y,
		hpEmptyPosition_.x + hp_empty_width + (adjust_hp_empty_x * playerNumber), hpEmptyPosition_.y + hp_empty_height, hpEmpty_, TRUE);
	DrawExtendGraphF(hpPosition_.x + (adjust_hp__x * playerNumber), hpPosition_.y,
		hpPosition_.x + (chara->Gethp_() * hp__width) / max_hp + (adjust_hp__x * playerNumber), hpPosition_.y + hp__height, hp_, TRUE);
}