#pragma once
#include<memory>

class CharaBase;

class HitEffect : public IEffect<CharaBase>
{
public:
	HitEffect();
	~HitEffect();

	void update(std::shared_ptr<CharaBase> chara);
	void draw();
	void stop();

private:
	void reset();

	int		effectHandle_;
	int		playingHandle_;
	VECTOR	position_;

	const float scale			= 0.5f;
	const float play_speed		= 2.0f;
	const float angle			= 1.0f;
};