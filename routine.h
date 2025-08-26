#pragma once
#include<memory>
#include<vector>

const int max_player_number = 2;

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
class ResultGraph;
class SandBag;
class PlayGraph;

class Routine
{
public:
	Routine();
	~Routine();

	void game();

	std::vector<std::shared_ptr<CharaBase>>players;

private:
	//�C���X�^���X��
	std::shared_ptr<SceneManager>sceneManager	= std::make_shared<SceneManager>();
	std::shared_ptr<Camera>camera				= std::make_shared<Camera>();
	std::shared_ptr<Stage>stage					= std::make_shared<Stage>();
	std::shared_ptr<StandbyUI>standbyUI			= std::make_shared<StandbyUI>("April Gothic one Regular");
	std::vector<std::shared_ptr<EffectManager>>effectManager;
	std::shared_ptr<TitleUI>titleUI				= std::make_shared<TitleUI>("April Gothic one Regular");
	std::shared_ptr<TitleGraph>titleGraph		= std::make_shared<TitleGraph>();
	std::shared_ptr<PlayUI>playUI				= std::make_shared<PlayUI>("April Gothic one Regular");
	std::shared_ptr<ResultUI>resultUI			= std::make_shared<ResultUI>("April Gothic one Regular");
	std::shared_ptr<ResultGraph>resultGraph		= std::make_shared<ResultGraph>();
	std::vector<std::shared_ptr<CharaBase>>sandBag;
	std::shared_ptr<PlayGraph>playGraph			/*= std::make_shared<PlayGraph>("April Gothic one Regular")*/;

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

	bool	isjoiningPlayer[max_player_number];	//�v���C���[�Q���t���O
	int		bgm_;								//bgm
	short	winPlayer_;							//�������v���C���[
	VECTOR	cameraUpPosition_;					//�J�����A�b�v���W
	bool	wasPlayingSE_;						//���ʉ��𗬂�����
	int		crap_;								//����
	int		fanfare_;							//�t�@���t�@�[��
	int		bgmPractice_;						//���Kbgm
	int		decideSound_;						//���艹
	int		screenHandle_;						//�X�N���[���n���h��
	int		movieHandle_;						//����n���h��
	
	const short bgm_volume		= 90;
	const short crap_volume		= 180;
	const short fanfare_volume	= 200;
	const short decide_volume	= 150;
};