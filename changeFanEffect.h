#pragma once
#include<memory>

class CharaBase;

class ChangeFanEffect : public IEffect<CharaBase>
{
public:
	ChangeFanEffect();
	~ChangeFanEffect();

	void update(std::shared_ptr<CharaBase> chara);
	void draw();
	void stop();

private:
	void reset();

	int		effectHandle_;
	int		playingHandle_;
	VECTOR	position_;

	const float scale		= 3.0f;
	const float play_speed	= 5.0f;
};