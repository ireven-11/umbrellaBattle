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

	//インスタンス化
	shared_ptr<SceneManager>sceneManager = make_shared<SceneManager>();
	shared_ptr<Camera>camera = make_shared<Camera>();
	vector<shared_ptr<Player>>player;
	shared_ptr<Stage>stage = make_shared<Stage>();

private:
	void gameRoop(/*shared_ptr<SceneManager> sceneManager, shared_ptr<Player>player, shared_ptr<Camera>camera, shared_ptr<Stage> stage*/);
	void title(/*shared_ptr<SceneManager> sceneManager*/);
	void play(/*shared_ptr<Player>player, shared_ptr<SceneManager> sceneManager*/);
	void result(/*shared_ptr<SceneManager> sceneManager*/);
	void stanby(/*shared_ptr<SceneManager> sceneManager*/);
};