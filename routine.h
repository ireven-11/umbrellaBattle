#pragma once
#include<memory>
#include<vector>

using namespace std;

class SceneManager;
class Player;
class Camera;
class Stage;

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
	vector<shared_ptr<Player>>player;
	shared_ptr<Stage>stage = make_shared<Stage>();

	void gameRoop();
	void title();
	void play();
	void result();
	void stanby();
};