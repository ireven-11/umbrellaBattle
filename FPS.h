#pragma once

class FPS
{
public:
	FPS();
	~FPS();

	void init();
	bool update();
	void draw();
	void wait();

private:
	int		startTime_;		//測定開始時刻
	int		count_;			//カウンタ
	float	currentFPS_;	//fps

	static const int n = 60;	//平均を取るサンプル数
	static const int fps = 60;	//設定したFPS
	const VECTOR drawingPosition = VGet(0.0f, 0.0f, 0.0f);//描画座標
};