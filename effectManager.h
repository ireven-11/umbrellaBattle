#pragma once
#include<vector>
#include<memory>

template<typename T>
class IEffect;
class CharaBase;

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	void update(std::shared_ptr<CharaBase> charaBase);
	void draw();
	void stop();

	std::vector<std::shared_ptr<IEffect<CharaBase>>> effects;

private:

};