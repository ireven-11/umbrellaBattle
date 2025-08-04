#pragma once
#include<memory>

class CharaBase;

class FallEffect : public IEffect<CharaBase>
{
public:
	FallEffect();
	~FallEffect();

	void update(std::shared_ptr<CharaBase> chara);
	void draw();

private:
	void reset();

	int		effectHandle_;
	int		playingHandle_;
	VECTOR	position_;

	const float scale			= 1.0f;
	const float play_speed		= 1.0f;
	const float angle			= 1.0f;
	const float play_position_y = -7.5f;
};