#pragma once

class PlayGraph
{
public:
	PlayGraph();
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

	const int		init_movie_width		= 750;				//���揉����
	const int		init_movie_height		= 460;				//���揉������
	const VECTOR	init_movie_position		= VGet(1220, 0, 0);	//�������W
	const int		max_expand_count		= 200;				//�ő�g��J�E���g
	const short		expand_speed_x			= 20;				//�g��X�s�[�hx
	const short		expand_speed_y			= 10;				//�g��X�s�[�hy
};