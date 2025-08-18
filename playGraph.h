#pragma once

class PlayGraph
{
public:
	PlayGraph();
	~PlayGraph();

	void update();

private:
	int countDownMovie_;	//カウントダウン動画
	int screenHandle_;		//スクリーンハンドル
};