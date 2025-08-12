#pragma once
#include<memory>

class CharaBase;

class ChargeEffect : public IEffect<CharaBase>
{
public:
	ChargeEffect();
	~ChargeEffect();

	void update(std::shared_ptr<CharaBase> chara);
	void draw();
	void stop();

private:
	void reset();

	int		effectHandle_;
	int		playingHandle_;
	VECTOR	position_;

	const float scale		= 0.75f;
	const float play_speed	= 5.0f;
	const float angle		= 1.0f;
};