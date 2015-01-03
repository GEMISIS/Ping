#pragma once

#include "entity.h"

class paddle_player : public Entity
{
public:
	paddle_player(int playerNumber);
	void Update();
private:
	int playerNumber;
};