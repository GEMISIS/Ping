#include "paddle_ai.h"

paddle_ai::paddle_ai(int playerNumber, int difficulty)
{
	this->playerNumber = playerNumber;
	this->ballObject = ballObject;
	switch (difficulty)
	{
	case 1:
		this->speed = 0.80f;
		break;
	case 2:
		this->speed = 1.00f;
		break;
	default:
		this->speed = 1.5f;
		break;
	}

	switch (this->playerNumber)
	{
	case 0:
		this->Load("paddle1.png");
		break;
	default:
		this->Load("paddle2.png");
		break;
	}
}

void paddle_ai::SetBall(ball* ballObject)
{
	this->ballObject = ballObject;
}

void paddle_ai::Update()
{
	if (this->ballObject != NULL)
	{
		if (this->getPosition().y + this->getGlobalBounds().height / 2 < this->ballObject->getPosition().y)
		{
			this->velocity.y = this->speed;
		}
		if (this->getPosition().y + this->getGlobalBounds().height / 2 > this->ballObject->getPosition().y)
		{
			this->velocity.y = -this->speed;
		}
	}
	Entity::Update();

	if (this->getPosition().y < 0)
	{
		this->move(0, this->speed);
	}
	if (this->getPosition().y + this->getGlobalBounds().height > 600)
	{
		this->move(0, -this->speed);
	}
}
