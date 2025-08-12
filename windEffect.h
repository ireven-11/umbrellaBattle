#pragma once
#include<memory>

class CharaBase;

class WindEffect : public IEffect<CharaBase>
{
public:
	WindEffect();
	~WindEffect();

	void update(std::shared_ptr<CharaBase> chara);
	void draw();
	void stop();

private:
	void reset();

	int		effectHandle_;
	int		playingHandle_;
	VECTOR	position_;

	const float scale		= 1.8f;
	const float play_speed	= 2.0f;
};