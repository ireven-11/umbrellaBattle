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
	int		umbrella3Handle_;		//�P3
	int		umbrella4Handle_;		//�P�S
	int		hitHandle_[18];			//�q�b�g
	VECTOR	umbrellaPosition_[4];	//�P���W
	VECTOR	hitPosition_;			//�q�b�g���W
	
	const short hit_div_number	= 18;	//�q�b�g������
	const short hit_div_X		= 9;	//�q�b�g������x
	const short hit_div_y		= 2;	//�q�b�g������y
	const int	hit_size_x		= 516;	//�摜�̑傫��x
	const int	hit_size_y		= 528;	//�摜�̑傫��y
	const int	hit_width		= 100;	//�q�b�g�̕�
	const int	hit_height		= 100;	//�q�b�g��t����
	const int	hit_switch_time = 2;	//�q�b�g�ς�鎞��
};