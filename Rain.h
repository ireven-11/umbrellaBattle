#pragma once

constexpr int max_raindrops = 200;

struct Raindrops
{
	VECTOR	position_;
	int		graphHandle_;
};

class Rain
{
public:
	Rain();
	~Rain();

	void update();
	void draw()const;
	void init();

private:
	void resetPosition(unsigned int index);

	Raindrops raindrop[max_raindrops];

	const double	graph_angle		= DX_PI / 4;
	const int		max_spawn_x		= 2100;
	const int		max_spawn_y		= 1200;
	const float		init_y			= -100.0f;
	const float		out_of_screen_x = -100.0f;
	const float		out_of_screen_y = 1200.0f;
	const float		adjust_spawn	= 550;
};