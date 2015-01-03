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
	this->player2 = new paddle_ai(1, 3);
	this->ballObject = new ball(this->score1, this->score2, this->player1, this->player2);
	this->player2->SetBall(this->ballObject);

	this->ballObject->Reset(window);

	this->paused = false;
	this->enterKey = false;
}
void main_game::Update(sf::RenderWindow* window)
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
		this->player2->Update();
		this->score1->Update();
		this->score2->Update();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
		{
			this->paused = true;
		}
	}

	this->enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);
}
void main_game::Render(sf::RenderWindow* window)
{
	window->draw(*this->ballObject);
	window->draw(*this->player1);
	window->draw(*this->player2);
	window->draw(*this->score1);
	window->draw(*this->score2);

	if (this->paused)
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
