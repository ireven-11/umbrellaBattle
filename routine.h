#pragma once
#include<memory>

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
	void gameRoop(shared_ptr<SceneManager> sceneManager, shared_ptr<Player>player, shared_ptr<Camera>camera, shared_ptr<Stage> stage);
	void title(shared_ptr<SceneManager> sceneManager);
	void play(shared_ptr<Player>player, shared_ptr<SceneManager> sceneManager);
	void result(shared_ptr<SceneManager> sceneManager);
	void stanby(shared_ptr<SceneManager> sceneManager);
};