#pragma once

class TitleUI
{
public:
	TitleUI(const char* fontName);
	~TitleUI();

	void update();

private:
	int	fontHandle_;		//フォントハンドル
	int	fontHandleSize200_;	//フォントハンドル
	int Logo_;

	const VECTOR start_text_position = VGet(635, 600, 0);
};