#include "paddle_player.h"

paddle_player::paddle_player(int playerNumber)
{
	this->playerNumber = playerNumber;
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

void paddle_player::Update()
{
	switch (this->playerNumber)
	{
	case 0:
		this->velocity.y = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) * PADDLE_SPEED;
		break;
	default:
		this->velocity.y = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) * PADDLE_SPEED;
		break;
	}
	Entity::Update();

	if (this->getPosition().y < 0)
	{
		this->move(0, PADDLE_SPEED);
	}
	if (this->getPosition().y + this->getGlobalBounds().height > 600)
	{
		this->move(0, -PADDLE_SPEED);
	}
}
