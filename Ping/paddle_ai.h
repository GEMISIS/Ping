#pragma once

#include "paddle.h"
#include "ball.h"

class paddle_ai : public paddle
{
public:
	paddle_ai(int playerNumber);
	void SetBall(ball* ballObject);
	void Update();
private:
	ball* ballObject;
	int playerNumber;
	float speed;
};