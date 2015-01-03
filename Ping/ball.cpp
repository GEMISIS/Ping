#include "ball.h"

ball::ball(Score* score1, Score* score2, paddle_player* player1, paddle_player* player2)
{
	this->Load("ball.png");
	this->score1 = score1;
	this->score2 = score2;
	this->player1 = player1;
	this->player2 = player2;

	this->buffer = new sf::SoundBuffer();
	this->buffer->loadFromFile("Sounds/bounce.wav");
	this->sound = new sf::Sound(*this->buffer);
}

void ball::Update(sf::RenderWindow* window)
{
	if (this->CheckCollision(this->player1) || this->CheckCollision(this->player2))
	{
		this->velocity.x *= -1;
		this->sound->play();
	}
	if (this->getPosition().y < 0 || this->getPosition().y + this->getGlobalBounds().height > window->getSize().y)
	{
		this->velocity.y *= -1;
		this->sound->play();
	}

	if (this->getPosition().x < this->player1->getGlobalBounds().width - 5)
	{
		this->score2->IncrementScore();
		this->Reset(window);
	}
	if (this->getPosition().x + this->getGlobalBounds().width > window->getSize().x - this->player2->getGlobalBounds().width + 5)
	{
		this->score1->IncrementScore();
		this->Reset(window);
	}
	Entity::Update();
}

void ball::Reset(sf::RenderWindow* window)
{
	this->velocity.x = 1.0f;
	this->velocity.y = 1.0f;
	this->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	this->player1->setPosition(0, window->getSize().y / 2 + this->player1->getGlobalBounds().height / 4);
	this->player2->setPosition(window->getSize().x - this->player2->getGlobalBounds().width, window->getSize().y / 2 + this->player2->getGlobalBounds().height / 4);
}

ball::~ball()
{
	delete this->sound;
	delete this->buffer;
}