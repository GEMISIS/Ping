#pragma once

#include "paddle.h"

class paddle_player : public paddle
{
public:
	paddle_player(int playerNumber);
	void Update();
private:
	int playerNumber;
};