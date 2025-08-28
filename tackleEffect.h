#pragma once
//#include<memory>

class CharaBase;

class TackleEffect : public IEffect<CharaBase>
{
public:
	TackleEffect();
	~TackleEffect();

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
};