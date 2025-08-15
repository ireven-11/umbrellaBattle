#pragma once

class ResultGraph
{
public:
	ResultGraph();
	~ResultGraph();

	void update();

private:
	int movieHandle_;	//動画ハンドル
	int screenHandle_;	//スクリーンハンドル
};