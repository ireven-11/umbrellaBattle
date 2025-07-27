#pragma once
#include<memory>

class CharaBase;

class Effect
{
public:
	Effect();
	~Effect();

	void updateHit(std::shared_ptr<CharaBase> chara);
	void updateFall(std::shared_ptr<CharaBase> chara);
	void updateCharge(std::shared_ptr<CharaBase> chara);
	void draw();

private:
	int hit_;
	int fall_;
	int charge_;
	int playingHit_;
	int playingFall_;
	int playingCharge_;
	VECTOR hitPosition_;
	VECTOR fallPosition_;
	VECTOR chargePosition_;

	const short charge_speed	= 50;
	const float charge_scale	= 0.5f;
	const short hit_speed		= 4;
	const float hit_scale		= 0.5f;
	const short fall_speed		= 10;
	const float fall_scale		= 5.0f;
};