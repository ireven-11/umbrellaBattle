#pragma once
#include<memory>

class CharaBase;

class RespawnEffect : public IEffect<CharaBase>
{
public:
	RespawnEffect();
	~RespawnEffect();

	void update(std::shared_ptr<CharaBase> chara);
	void draw();

private:
	void reset();

	int		effectHandle_;
	int		playingHandle_;
	VECTOR	position_;

	const float scale		= 1.0f;
	const float play_speed	= 3.0f;
};