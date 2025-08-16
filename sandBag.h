#pragma once

class Routine;
class Stage;

class SandBag : public CharaBase
{
public:
	SandBag(const int join_number);
	~SandBag();

	void update(Routine* routine, std::shared_ptr<Stage> stage)override;
	void draw()const override;

private:
	int modelHandle_;
};