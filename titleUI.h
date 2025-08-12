#pragma once

class TitleUI
{
public:
	TitleUI(const char* fontName);
	~TitleUI();

	void update();

private:
	int	fontHandle_;		//フォントハンドル
};