#pragma once

//�V�[��
enum
{
	TITLE,
	STANDBY,
	PLAY,
	RESULT
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void reset();			//���Z�b�g����
	void proceedStandby();
	void proceedPlay();
	void proceedResult();
	void proceedTitle();

	int GetsceneType_()const { return sceneType_; }

private:

	int sceneType_;	//�V�[���^�C�v
};