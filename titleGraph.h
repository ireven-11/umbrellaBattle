#pragma once

class TitleGraph
{
public:
	TitleGraph();
	~TitleGraph();

	void update();

private:
	void reset();

	int	logo_;

	const VECTOR logo_max_pos = VGet(1475.0f, 600.0f, 0.0f);
	const VECTOR logo_min_pos = VGet(375.0f, 50.0f, 0.0f);
}; 