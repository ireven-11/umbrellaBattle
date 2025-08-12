#pragma once

class ResultUI
{
public:
	ResultUI(const char* fontName);
	~ResultUI();

	void update(short winPlayer);

private:
	int	fontHandle_;		//フォントハンドル
	
	const VECTOR winner_text_position_ = VGet(450.0f, 150.0f, 0.0f);
};