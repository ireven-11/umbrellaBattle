#pragma once
#include<memory>

class CPUBrain;

class CPU:public CharaBase
{
public:
	CPU(const int join_number);
	~CPU();

	void update(Routine* routine, std::shared_ptr<Stage> stage)override;

private:
	void wind()override;

	//�u���C����錾
	std::shared_ptr<CPUBrain> brain_ = std::make_shared<CPUBrain>();
};