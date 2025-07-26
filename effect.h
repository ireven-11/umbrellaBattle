#pragma once

class Effect
{
public:
	Effect();
	~Effect();

	void update();
	void draw();

private:
	int hit_;
	int fall_;

};