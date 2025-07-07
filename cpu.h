#pragma once
#include<memory>

class CPUBrain;

class CPU:public CharaBase
{
public:
	CPU(const int join_number);
	~CPU();

	void update(Routine* routine)override;

private:
	//ƒuƒŒƒCƒ“‚ğéŒ¾
	shared_ptr<CPUBrain> brain_ = make_shared<CPUBrain>();
};