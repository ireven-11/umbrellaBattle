#include"DxLib.h"
#include"charaBase.h"
#include"playUI.h"
#include"DrawExtendBrinkGraph.h"
#include"routine.h"

PlayUI::PlayUI(const char* fontName)
{
	fontHandle_			= CreateFontToHandle(fontName, 100, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	fontHandleSize60_	= CreateFontToHandle(fontName, 45, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	fontHandleSize30_	= CreateFontToHandle(fontName, 300, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	umbrella1_			= LoadGraph("graph/black.png");
	umbrella2_			= LoadGraph("graph/skyblue.png");
	umbrella3_			= LoadGraph("graph/orange.png");
	umbrella4_			= LoadGraph("graph/pink.png");
	hpEmpty_			= LoadGraph("graph/hpEmpty.png");
	hp_					= LoadGraph("graph/hp.png");
	AbuttonUI_			= LoadGraph("graph/A.png");
	LstickUI_			= LoadGraph("graph/Lstick.png");
	LTbuttonUI_			= LoadGraph("graph/LT.png");
	RTbuttonUI_			= LoadGraph("graph/RT.png");
	trumpet_[0]			= LoadGraph("graph/trumpetBlack.png");
	trumpet_[1]			= LoadGraph("graph/trumpetSkyBlue.png");
	trumpet_[2]			= LoadGraph("graph/trumpetOrange.png");
	trumpet_[3]			= LoadGraph("graph/trumpetPink.png");
	fanGraph_			= LoadGraph("graph/fan.png");
	coolTimeGage_		= LoadGraph("graph/coolTimeGage.png");
	windGraph_			= LoadGraph("graph/wind.png");

	hpPosition_			= hp__init_position;
	hpEmptyPosition_	= hp_empty_init_position;
	umbrellaPosition_	= umbrella_init_position;
	for (auto i = 0; i < 4; i++)
	{
		coolTime_[i]		= 0;
		canSetCoolTime_[i]	= true;
	}
}

PlayUI::~PlayUI()
{
	DeleteFontToHandle(fontHandle_);
	DeleteFontToHandle(fontHandleSize60_);
	DeleteFontToHandle(fontHandleSize30_);
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
	for (auto i = 0; i < 4; i++)
	{
		DeleteGraph(trumpet_[i]);
	}
	DeleteGraph(fanGraph_);
	DeleteGraph(coolTimeGage_);
	DeleteGraph(windGraph_);
}

void PlayUI::reset()
{
	hpPosition_			= hp__init_position;
	hpEmptyPosition_	= hp_empty_init_position;
	umbrellaPosition_	= umbrella_init_position;
	for (auto i = 0; i < max_player_number; i++)
	{
		coolTime_[i]		= 0;
		canSetCoolTime_[i]	= true;
	}
}

void PlayUI::update(std::shared_ptr<CharaBase> chara, int playerNumber)
{
	playerUI(chara, playerNumber);

	buttonUI();
}

void PlayUI::buttonUI()
{
	DrawBox(frame_box_position.x, frame_box_position.y, frame_box_position.x + frame_box_width_height.x, frame_box_position.y + frame_box_width_height.y, GetColor(255, 255, 255), FALSE);
	DrawBox(frame_box_position.x, frame_box_position.y * 3.3f, frame_box_position.x + frame_box_width_height.x, frame_box_position.y * 3.3f + frame_box_width_height.y * 1.5f, GetColor(255, 255, 255), FALSE);
	DrawExtendGraph(A_ui_position.x, A_ui_position.y, A_ui_position.x + button_ui_width, A_ui_position.y + button_ui_height, AbuttonUI_, TRUE);
	DrawExtendGraph(A_ui_wind_position.x, A_ui_wind_position.y, A_ui_wind_position.x + button_ui_width, A_ui_wind_position.y + button_ui_height, AbuttonUI_, TRUE);
	DrawExtendGraph(Lstick_ui_position.x, Lstick_ui_position.y, Lstick_ui_position.x + button_ui_width, Lstick_ui_position.y + button_ui_height, LstickUI_, TRUE);
	DrawExtendGraph(LT_ui_position.x, LT_ui_position.y, LT_ui_position.x + button_ui_width, LT_ui_position.y + button_ui_height, LTbuttonUI_, TRUE);
	DrawExtendGraph(RT_ui_position.x, RT_ui_position.y, RT_ui_position.x + button_ui_width, RT_ui_position.y + button_ui_height, RTbuttonUI_, TRUE);
	DrawExtendGraph(control_umbrella_position.x, control_umbrella_position.y, control_umbrella_position.x + button_ui_width * 1.75f, control_umbrella_position.y + button_ui_height * 1.75f, umbrella4_, TRUE);
	DrawExtendGraph(fan_graph_position.x, fan_graph_position.y, fan_graph_position.x + fan_graph_widht_height.x, fan_graph_position.y + fan_graph_widht_height.y, fanGraph_, TRUE);

	DrawStringToHandle(action_text_position.x, action_text_position.y, ":タックル", GetColor(255, 255, 255), fontHandleSize60_);
	DrawStringToHandle(move_text_position.x, move_text_position.y, ":移動", GetColor(255, 255, 255), fontHandleSize60_);
	DrawStringToHandle(left_turn_text_position.x, left_turn_text_position.y, ":左回り", GetColor(255, 255, 255), fontHandleSize60_);
	DrawStringToHandle(right_turn_text_position.x, right_turn_text_position.y, ":右回り", GetColor(255, 255, 255), fontHandleSize60_);
	DrawStringToHandle(wind_text_position.x, wind_text_position.y, ":送風", GetColor(255, 255, 255), fontHandleSize60_);
}

/**newbieからもらった関数
 * 3D空間に文字列をフォントハンドルを使用して描画します。
 *
 * 文字列は指定された位置にビルボード形式で表示されます。
 * 指定されたフォントハンドルを使用して文字列を描画します。
 *
 * @param pos 文字列を表示する3D座標
 * @param str 表示する文字列
 * @param color 文字色(0xRRGGBB形式)
 * @param font_handle 使用するフォントのハンドル
 * @param edge_color エッジの色(0xAARRGGBB形式)。デフォルトは0(エッジなし)
 * @param size 描画するビルボードのサイズ。
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
	//扇風機の時
	fanUI(chara, playerNumber);

	//ラッパ
	if (chara->Gethp_() <= 0)
	{
		trumpetUI(playerNumber);
	}
	else
	{
		//傘表示
		umbrellaUI(chara, playerNumber);
	}

	//ゲージ表示
	DrawExtendGraph(hpEmptyPosition_.x + (adjust_hp_empty_x * playerNumber), hpEmptyPosition_.y,
		hpEmptyPosition_.x + hp_empty_width + (adjust_hp_empty_x * playerNumber), hpEmptyPosition_.y + hp_empty_height, hpEmpty_, TRUE);
	if (chara->Gethp_() < max_hp / 3)
	{

		DrawExtendBrinkGraph(hpPosition_.x + (adjust_hp__x * playerNumber), hpPosition_.y,
			(chara->Gethp_() * hp__width) / max_hp, hp__height, hp_, TRUE, 4);
	}
	else
	{
		DrawExtendGraphF(hpPosition_.x + (adjust_hp__x * playerNumber), hpPosition_.y,
			hpPosition_.x + (chara->Gethp_() * hp__width) / max_hp + (adjust_hp__x * playerNumber), hpPosition_.y + hp__height, hp_, TRUE);
	}
}

void PlayUI::fanUI(std::shared_ptr<CharaBase> chara, int playerNumber)
{
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

		windGage(chara, playerNumber);
	}
}

void PlayUI::windGage(std::shared_ptr<CharaBase> chara, int playerNumber)
{
	for (auto i = 0; i < max_player_number; i++)
	{
		if (i + 1 == playerNumber)
		{
			//風クールタイム
			if (!chara->GetcanSpawnWind_())
			{
				if (canSetCoolTime_[i])
				{
					canSetCoolTime_[i] = false;
					coolTime_[i] = max_cool_time;
				}
				coolTime_[i] -= max_cool_time / max_wind_count;
			}
			else
			{
				canSetCoolTime_[i] = true;
				coolTime_[i] = 0;
			}
			DrawCircleGauge(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y, max_cool_time - coolTime_[i], coolTimeGage_, 0.0, 0.3);
		}
	}
	DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber) - 50, umbrellaPosition_.y - 50,
		umbrellaPosition_.x + (adjust_umbrella_x * playerNumber) + wind_width_height.x - 50, umbrellaPosition_.y + wind_width_height.y - 50, windGraph_, TRUE);
}

void PlayUI::trumpetUI(int playerNumber)
{
	//傘表示
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
	DrawStringToHandle(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber) + 15.0f, umbrellaPosition_.y - 10.0f, "復活不可...", GetColor(0, 191, 255), fontHandleSize60_);
}

void PlayUI::umbrellaUI(std::shared_ptr<CharaBase> chara, int playerNumber)
{
	switch (playerNumber)
	{
	case 1:
		DrawExtendGraph(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y,
			umbrellaPosition_.x + umbrella_width + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y + umbrella_height, umbrella1_, TRUE);
		DrawString3DToHandle(VGet(chara->Getposition_().x, chara->Getposition_().y + 5.0f, chara->Getposition_().z), "1P", GetColor(255, 255, 255), fontHandleSize30_, GetColor(0, 0, 0), 0.01f);
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
	//～P表示
	DrawFormatStringToHandle(umbrellaPosition_.x + (adjust_umbrella_x * playerNumber), umbrellaPosition_.y, GetColor(255, 255, 255), fontHandle_, "%dP", playerNumber);
}