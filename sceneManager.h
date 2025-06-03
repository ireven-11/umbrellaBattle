#pragma once

//シーン
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

	void reset();			//リセット処理
	void proceedStandby();
	void proceedPlay();
	void proceedResult();
	void proceedTitle();

	int GetsceneType_()const { return sceneType_; }

private:

	int sceneType_;	//シーンタイプ
};