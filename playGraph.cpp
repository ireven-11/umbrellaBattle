#include"DxLib.h"
#include"playGraph.h"
#include"PlayTransparentMovie.h"

PlayGraph::PlayGraph(const char* fontName)
{
	fontHandle_			= CreateFontToHandle(fontName, 180, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	countDownMovie_		= LoadGraph("movie/countdown.mp4");
	screenHandle_		= MakeScreen(1920, 1080, TRUE);
	movieWidht_			= init_movie_width;
	movieHeight_		= init_movie_height;
	moviePosition_		= init_movie_position;
	onCountDown_		= true;
	expandMovieCount_	= 0;
	startSound_			= LoadSoundMem("sound/startBattle.mp3");
	ChangeVolumeSoundMem(start_sound_volume, startSound_);
}

PlayGraph::~PlayGraph()
{
	DeleteGraph(countDownMovie_);
	DeleteFontToHandle(fontHandle_);
	DeleteSoundMem(startSound_);
}

void PlayGraph::update()
{
	//����𗬂�
	if (onCountDown_)
	{
		PlayTransparentMovie(countDownMovie_, screenHandle_, movieWidht_, movieHeight_, moviePosition_, false);

		//�J�E���g�����ɂȂ�ƃJ�E���g�_�E��������g�傳����
		++expandMovieCount_;
		if (CheckHitKey(KEY_INPUT_RETURN) && expandMovieCount_ < max_expand_count)//�J�E���g�X�L�b�v
		{
			expandMovieCount_ += max_expand_count;
			SeekMovieToGraph(countDownMovie_, 7500);
		}
		if (expandMovieCount_ > max_expand_count)
		{
			moviePosition_.x	-= expand_speed_x;
			movieWidht_			+= expand_speed_x;
			movieHeight_		+= expand_speed_y;

			//��ʂ��ł����Ȃ肻����������߂�
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
		else
		{
			//�ȒP�ȃQ�[������
			DrawStringToHandle(explane_rule_position.x, explane_rule_position.y, "���b�p�ɂȂ炸�ɑ����\n    ���Ƃ��Đ����c��!!", GetColor(255, 50, 50), fontHandle_);
		}

		//�J�E���g�_�E���I��
		if (!GetMovieStateToGraph(countDownMovie_))
		{
			onCountDown_ = false;
			PlaySoundMem(startSound_, DX_PLAYTYPE_BACK, TRUE);
		}
	}
}