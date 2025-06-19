#pragma once

class StandbyUI
{
public:
	StandbyUI();
	~StandbyUI();

	void update(bool isjoiningPlayer[], const int max_player_number);

private:
	void playerJoin(bool isjoiningPlayer[], const int max_player_number);
};