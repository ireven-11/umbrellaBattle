#pragma once

class ResultUI
{
public:
	ResultUI(const char* fontName);
	~ResultUI();

	void update(short winPlayer);

private:
	int	fontHandle_;		//�t�H���g�n���h��
	int fontHandleSize100_;	//�t�H���g�n���h��100
	
	const VECTOR winner_text_position_			= VGet(375.0f, 60.0f, 0.0f);
	const VECTOR return_title_text_position_	= VGet(550.0f, 800.0f, 0.0f);
};