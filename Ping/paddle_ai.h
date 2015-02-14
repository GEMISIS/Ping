#pragma once

#include "paddle.h"
#include "ball.h"

#define AI_BALL_BOUNDS 10.0f

class paddle_ai : public paddle
{
public:
	paddle_ai(int playerNumber, int difficulty);
	void SetBall(ball* ballObject);
	void Update();
private:
	sf::Vector2f target;
	ball* ballObject;
	int playerNumber;
	float speed;

	bool ballAway();
	void SelectTarget();
};