#pragma once
#include<memory>
#include<vector>

using namespace std;

const int max_player_number = 4;

class SceneManager;
class Player;
class Camera;
class Stage;
class StandbyUI;

class Routine
{
public:
	Routine();
	~Routine();

	void game();

private:
	//インスタンス化
	shared_ptr<SceneManager>sceneManager = make_shared<SceneManager>();
	shared_ptr<Camera>camera = make_shared<Camera>();
	vector<shared_ptr<Player>>players;
	shared_ptr<Stage>stage = make_shared<Stage>();
	shared_ptr<StandbyUI>standbyUI = make_shared<StandbyUI>();

	void gameRoop();
	void title();
	void play();
	void result();
	void stanby();
	void reset();
	void joinPlayer();

	bool isjoiningPlayer[max_player_number];	//プレイヤー参加フラグ
};