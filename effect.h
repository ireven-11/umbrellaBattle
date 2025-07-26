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
};