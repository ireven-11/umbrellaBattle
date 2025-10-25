#include"DxLib.h"
#include"Rain.h"
#include"RotationVectorY.h"

Rain::Rain()
{
	int rainGraph = LoadGraph("graph/rain.png");

	for (int i = 0; i < max_raindrops; i++)
	{
		raindrop[i].graphHandle_	= rainGraph;
		raindrop[i].position_		= VGet(GetRand(max_spawn_x) + adjust_spawn, -GetRand(max_spawn_y), 0.0f);
	}
}

Rain::~Rain()
{
	for (int i = 0; i < max_raindrops; i++)
	{
		DeleteGraph(raindrop[i].graphHandle_);
	}
}

void Rain::init()
{
	for (int i = 0; i < max_raindrops; i++)
	{
		resetPosition(i);
	}
}

void Rain::update()
{
	VECTOR moveVector	= VGet(-10.0f, 10.0f, 0.0f);
	moveVector			= RotationVectorY(moveVector, graph_angle);
	for (int i = 0; i < max_raindrops; i++)
	{
		raindrop[i].position_ = VAdd(raindrop[i].position_, moveVector);

		//外に出てたら
		const bool isOutScreen = raindrop[i].position_.x < out_of_screen_x || raindrop[i].position_.y > out_of_screen_y;
		if (isOutScreen)
		{
			resetPosition(i);
		}
	}
}

void Rain::resetPosition(unsigned int index)
{
	//ｙは画面の外から出したいので出した乱数にマイナスをかける
	raindrop[index].position_ = VGet(GetRand(max_spawn_x) + adjust_spawn, -GetRand(max_spawn_y), 0.0f);
}

void Rain::draw()const
{
	for (int i = 0; i < max_raindrops; i++)
	{
		DrawRotaGraph(raindrop[i].position_.x, raindrop[i].position_.y, 0.1f, graph_angle, raindrop[i].graphHandle_, TRUE);
	}
}