#include"DxLib.h"
#include"playGraph.h"
#include"PlayTransparentMovie.h"

PlayGraph::PlayGraph(const char* fontName)
{
	SetFontUseAdjustSizeFlag(FALSE);//CreateFontToHandleのフォントの自動補正の設定をする関数(補正のせいでフォントの大きさがバグる可能性あり)。TRUE:補正する,FALSE:補正しない
	fontHandle_			= CreateFontToHandle(fontName, 180, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	fontHandleSize300_	= CreateFontToHandle(fontName, 300, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	countDownMovie_		= LoadGraph("movie/countdown.mp4");
	//countDownMovie_ = LoadGraph("movie/3tr165スワイプトランジション.mp4");
	screenHandle_		= MakeScreen(1920, 1080, TRUE);
	movieWidht_			= init_movie_width;
	movieHeight_		= init_movie_height;
	moviePosition_		= init_movie_position;
	onCountDown_		= true;
	expandMovieCount_	= 0;
	startSound_			= LoadSoundMem("sound/startBattle.mp3");
	ChangeVolumeSoundMem(start_sound_volume, startSound_);
	trumpet_			= LoadGraph("graph/trumpetBlack.png");
	beat_				= LoadGraph("graph/beat.png");
}

PlayGraph::~PlayGraph()
{
	DeleteGraph(countDownMovie_);
	DeleteFontToHandle(fontHandle_);
	DeleteSoundMem(startSound_);
}

void PlayGraph::update()
{
	//動画を流す
	if (onCountDown_)
	{
		PlayTransparentMovie(countDownMovie_, screenHandle_, 1, movieWidht_, movieHeight_, moviePosition_, false);

		//カウントが一定になるとカウントダウン動画を拡大させる
		++expandMovieCount_;
		if (CheckHitKey(KEY_INPUT_RETURN) && expandMovieCount_ < max_expand_count)//カウントスキップ
		{
			expandMovieCount_ += max_expand_count;
			SeekMovieToGraph(countDownMovie_, 7250);
		}
		if (expandMovieCount_ > max_expand_count)
		{
			moviePosition_.x	-= expand_speed_x;
			movieWidht_			+= expand_speed_x;
			movieHeight_		+= expand_speed_y;

			//画面よりでかくなりそうだったら戻す
			if (movieWidht_ > 1920)
			{
				movieWidht_ = 1920;
			}
			if (movieHeight_ > 1080)
			{
				movieHeight_ = 1080;
			}
			if (moviePosition_.x < 0)
			{
				moviePosition_.x = 0;
			}
		}
		else if (expandMovieCount_ < max_expand_count / 2 - 20)
		{
			//簡単なゲーム説明
			DrawStringToHandle(explane_rule_position.x, explane_rule_position.y, "ラッパ傘にならずに", GetColor(255, 50, 50), fontHandle_);
			DrawExtendGraph(trumpet_position.x, trumpet_position.y, trumpet_position.x + trumpet_width, trumpet_position.y + trumpet_height, trumpet_, TRUE);
			DrawStringToHandle(batu_position.x, batu_position.y, "→ ×", GetColor(255, 50, 50), fontHandleSize300_);
		}
		else
		{
			DrawStringToHandle(explane_rule_position.x - 100, explane_rule_position.y, "相手を倒して生き残れ!", GetColor(255, 50, 50), fontHandle_);
			DrawExtendGraph(beat_position.x, beat_position.y, beat_position.x + beat_width, beat_position.y + beat_height, beat_, TRUE);
		}

		//カウントダウン終了
		if (!GetMovieStateToGraph(countDownMovie_))
		{
			onCountDown_ = false;
			PlaySoundMem(startSound_, DX_PLAYTYPE_BACK, TRUE);
		}
	}
}