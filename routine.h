#pragma once
#include<memory>
#include<vector>

const int max_player_number = 4;

class SceneManager;
class Player;
class Camera;
class Stage;
class StandbyUI;
class CharaBase;
class EffectManager;

class Routine
{
public:
	Routine();
	~Routine();

	void game();

	std::vector<std::shared_ptr<CharaBase>>players;

private:
	//インスタンス化
	std::shared_ptr<SceneManager>sceneManager	= std::make_shared<SceneManager>();
	std::shared_ptr<Camera>camera				= std::make_shared<Camera>();
	std::shared_ptr<Stage>stage					= std::make_shared<Stage>();
	std::shared_ptr<StandbyUI>standbyUI			= std::make_shared<StandbyUI>();
	std::vector<std::shared_ptr<EffectManager>> effectManager;
	
	void gameRoop();
	void title();
	void play();
	void result();
	void stanby();
	void reset();
	void joinPlayer();
	void joinCPU();

	bool	isjoiningPlayer[max_player_number];	//プレイヤー参加フラグ
	int		bgm_;

	const short bgm_volume = 100;
};