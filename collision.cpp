#include"DxLib.h"
#include"collision.h"
#include"calculateDistance.h"
#include"charaBase.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::players(VECTOR player1, VECTOR player2)
{
	if (CalculateDistance<float>(player1, player2) < collision_radius * 2)
	{
		return true;
	}
	
	return false;
}