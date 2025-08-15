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
class TitleUI;
class TitleGraph;
class PlayUI;
class ResultUI;

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
	std::shared_ptr<StandbyUI>standbyUI			= std::make_shared<StandbyUI>("April Gothic one Regular");
	std::vector<std::shared_ptr<EffectManager>>effectManager;
	std::shared_ptr<TitleUI>titleUI				= std::make_shared<TitleUI>("April Gothic one Regular");
	std::shared_ptr<TitleGraph>titleGraph		= std::make_shared<TitleGraph>();
	std::shared_ptr<PlayUI>playUI				= std::make_shared<PlayUI>("April Gothic one Regular");
	std::shared_ptr<ResultUI>resultUI			= std::make_shared<ResultUI>("April Gothic one Regular");

	void gameRoop();
	void title();
	void play();
	void result();
	void stanby();
	void reset();
	void joinPlayer();
	void joinCPU();
	void allReset();
	void judgeWinner();

	bool	isjoiningPlayer[max_player_number];	//プレイヤー参加フラグ
	int		bgm_;								//bgm
	short	winPlayer_;							//勝ったプレイヤー
	VECTOR	cameraUpPosition_;					//カメラアップ座標
	
	const short bgm_volume = 100;
};