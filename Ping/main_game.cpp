#include "main_game.h"
#include "main_menu.h"

void main_game::Initialize(sf::RenderWindow* window)
{
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");
	this->score1 = new Score(*font, 64U);
	this->score2 = new Score(*font, 64U);

	this->pausedText = new sf::Text("Paused\nPress Escape to Quit", *font, 64U);
	this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
	this->pausedText->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->score2->setPosition(window->getSize().x - this->score2->getGlobalBounds().width, 0);

	this->player1 = new paddle_player(0);
	switch (this->aiDifficulty)
	{
	case 0:
		this->player2 = new paddle_ai(1, 1);
		break;
	case 1:
		this->player2 = new paddle_ai(1, 2);
		break;
	case 2:
		this->player2 = new paddle_ai(1, 3);
		break;
	case 3:
		this->player2 = new paddle_player(1);
		break;
	}
	this->ballObject = new ball(this->score1, this->score2, this->player1, this->player2);
	if (typeid(*this->player2) == typeid(paddle_ai))
	{
		(reinterpret_cast<paddle_ai*>(this->player2))->SetBall(this->ballObject);
	}
	this->ballObject->Reset(window);

	this->paused = false;
	this->enterKey = false;
}
void main_game::Update(sf::RenderWindow* window)
{
	this->startElapsed = this->startCountdown.getElapsedTime();
	if (this->startElapsed.asSeconds() > 4)
	{
		if (this->paused)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
			{
				this->paused = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				coreState.SetState(new main_menu());
			}
		}
		else
		{
			this->ballObject->Update(window);
			this->player1->Update();
			if (typeid(*this->player2) == typeid(paddle_ai))
			{
				(reinterpret_cast<paddle_ai*>(this->player2))->Update();
			}
			else if (typeid(*this->player2) == typeid(paddle_player))
			{
				(reinterpret_cast<paddle_player*>(this->player2))->Update();
			}
			this->score1->Update();
			this->score2->Update();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
			{
				this->paused = true;
				this->pausedText->setString("         Paused\nPress Escape to Quit");
				this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
				this->pausedText->setPosition(800 / 2, 600 / 2);
			}
		}
	}
	else
	{
		switch ((int)this->startElapsed.asSeconds())
		{
		case 0:
			this->pausedText->setString("3");
			break;
		case 1:
			this->pausedText->setString("2");
			break;
		case 2:
			this->pausedText->setString("1");
			break;
		default:
			this->pausedText->setString("Go!");
			break;
		}
		this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
		this->pausedText->setPosition(800 / 2 + 16, 600 / 2 - 64);
	}
	this->enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);
}
void main_game::Render(sf::RenderWindow* window)
{
	sf::Color color(255, 255, 255, 0);
	switch (lastScorer)
	{
	case 1:
		color.r = 50;
		color.g = 0;
		color.b = 0;
		break;
	case 2:
		color.r = 0;
		color.g = 0;
		color.b = 50;
		break;
	default:
		color.r = 0;
		color.g = 0;
		color.b = 0;
		break;
	}
	window->clear(color);

	window->draw(*this->ballObject);
	window->draw(*this->player1);
	window->draw(*this->player2);
	window->draw(*this->score1);
	window->draw(*this->score2);

	this->startElapsed = this->startCountdown.getElapsedTime();
	if (this->paused || this->startElapsed.asSeconds() < 4)
	{
		window->draw(*this->pausedText);
	}
}
void main_game::Destroy(sf::RenderWindow* window)
{
	delete this->player1;
	delete this->player2;
	delete this->ballObject;
	delete this->score1;
	delete this->score2;

	delete this->font;
}
