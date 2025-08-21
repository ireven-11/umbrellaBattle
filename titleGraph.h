#pragma once

class TitleGraph
{
public:
	TitleGraph();
	~TitleGraph();

	void update();

private:
	void reset();

	int		umbrella1Handle_;		//�P�P
	int		umbrella2Handle_;		//�P�Q
	VECTOR	umbrellaPosition_[4];	//�P���W
	int		screenHandle_;			//�X�N���[���n���h��
	int		movieHandle_;			//����n���h��

	const int		umbrella_width	= 500;	//�P��
	const int		umbrella_height	= 400;	//����
	const VECTOR	umbrella1_init_position = VGet(550, 60, 0);	//�������傫���Ђ傤
	const VECTOR	umbrella2_init_position = VGet(850, 60, 0);	//�������傫���Ђ傤
}; 