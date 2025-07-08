#pragma once
#include<memory>

class CPUBrain;

class CPU:public CharaBase
{
public:
	CPU(const int join_number);
	~CPU();

	void update(Routine* routine, shared_ptr<Stage> stage)override;

private:
	//�u���C����錾
	shared_ptr<CPUBrain> brain_ = make_shared<CPUBrain>();
};