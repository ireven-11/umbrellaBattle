#pragma once
#include<memory>

using namespace std;

class SceneManager;

class Routine
{
public:
	Routine();
	~Routine();

	void game();

private:
	void gameRoop(shared_ptr<SceneManager> sceneManager);
	void title();
	void play();
	void result();
};