#pragma once

class TitleUI
{
public:
	TitleUI(const char* fontName);
	~TitleUI();

	void update();

private:
	int	fontHandle_;		//�t�H���g�n���h��
	int	fontHandleSize200_;	//�t�H���g�n���h��

	const VECTOR start_text_position = VGet(650, 750, 0);
};