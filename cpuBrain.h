#pragma once
#include<memory>
#include<vector>

class CharaBase;
class Routine;

class CPUBrain
{
public:
	CPUBrain();
	~CPUBrain();

	void update(CharaBase* charaBase, Routine* routine);

private:
	bool	isTarget_;
	int		randomTarget_;
};