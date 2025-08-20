#pragma once

class PlayGraph
{
public:
	PlayGraph(const char* fontName);
	~PlayGraph();

	void update();

	bool GetonCountDown_()const { return onCountDown_; }

private:
	int		countDownMovie_;	//�J�E���g�_�E������
	int		screenHandle_;		//�X�N���[���n���h��
	int		movieWidht_;		//���敝
	int		movieHeight_;		//���捂��
	VECTOR	moviePosition_;		//������W
	bool	onCountDown_;		//�J�E���g�_�E�������ǂ���
	int		expandMovieCount_;	//�g��J�E���g
	int		fontHandle_;		//�t�H���g�n���h��
	int		startSound_;		//�X�^�[�g�T�E���h
	int		trumpet_;			//�g�����y�b�g�摜
	int		fontHandleSize300_;	//�t�H���g�n���h��300
	int		beat_;				//����|���摜

	const int		init_movie_width		= 750;				//���揉����
	const int		init_movie_height		= 460;				//���揉������
	const VECTOR	init_movie_position		= VGet(1220, 0, 0);	//�������W
	const int		max_expand_count		= 210;				//�ő�g��J�E���g
	const short		expand_speed_x			= 20;				//�g��X�s�[�hx
	const short		expand_speed_y			= 10;				//�g��X�s�[�hy
	const VECTOR	explane_rule_position	= VGet(440, 90, 0);	//���[���������W
	const short		start_sound_volume		= 150;				//�X�^�[�g�T�E���h�{�����[��
	const VECTOR	trumpet_position		= VGet(350, 300, 0);//�g�����y�b�g���W
	const float		trumpet_width			= 625.0f;
	const float		trumpet_height			= 325.0f;
	const VECTOR	batu_position			= VGet(900, 325, 0);
	const VECTOR	beat_position			= VGet(300, 325, 0);
	const float		beat_width				= 1325.0f;
	const float		beat_height				= 425.0f;
};