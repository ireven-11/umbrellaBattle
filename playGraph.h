#pragma once

class PlayGraph
{
public:
	PlayGraph();
	~PlayGraph();

	void update();

private:
	int countDownMovie_;	//�J�E���g�_�E������
	int screenHandle_;		//�X�N���[���n���h��
};