#include <iostream>
#include "main_menu.h"
#include "main_game.h"

void main_menu::Initialize(sf::RenderWindow* window)
{
	this->selected = 0;
	this->mode = 0;
	this->scale = 1;
	this->scaleInc = SCALE_SPEED;

	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");

	this->title = new sf::Text("Ping", *this->font, 256U);
	this->title->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
	this->title->setPosition(window->getSize().x / 2, window->getSize().y / 8);

	this->play = new sf::Text("<Easy>", *this->font, 128U);
	this->play->setOrigin(this->play->getGlobalBounds().width / 2, this->play->getGlobalBounds().height / 2);
	this->play->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->quit = new sf::Text("Quit", *this->font, 128U);
	this->quit->setOrigin(this->quit->getGlobalBounds().width / 2, this->quit->getGlobalBounds().height / 2);
	this->quit->setPosition(window->getSize().x / 2, window->getSize().y / 2 + this->play->getGlobalBounds().height);
}
void main_menu::Update(sf::RenderWindow* window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !this->upKey)
	{
		this->selected -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !this->downKey)
	{
		this->selected += 1;
	}
	if (this->selected > 1)
	{
		this->selected = 0;
	}
	if (this->selected < 0)
	{
		this->selected = 1;
	}

	if (this->selected == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && !this->leftKey)
		{
			this->mode -= 1;
			this->UpdateMode(window);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !this->rightKey)
		{
			this->mode += 1;
			this->UpdateMode(window);
		}

		if (this->mode > 3)
		{
			this->mode = 0;
			this->UpdateMode(window);
		}
		if (this->mode < 0)
		{
			this->mode = 3;
			this->UpdateMode(window);
		}
	}

	this->play->setScale(1, 1);
	this->quit->setScale(1, 1);

	switch (this->selected)
	{
	case 0:
		this->play->setScale(this->scale, this->scale);
		break;
	case 1:
		this->quit->setScale(this->scale, this->scale);
		break;
	}

	this->scale += this->scaleInc;

	if (this->scale > 1.0f + MAX_SCALE || this->scale < 1.0f - MAX_SCALE)
	{
		this->scaleInc *= -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		switch (this->selected)
		{
		case 0:
			coreState.SetState(new main_game(this->mode));
			break;
		case 1:
			quitGame = true;
			break;
		}
	}
	this->upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	this->downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
	this->leftKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
	this->rightKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
}
void main_menu::Render(sf::RenderWindow* window)
{
	window->clear(sf::Color::Black);

	this->play->setColor(sf::Color::White);
	this->quit->setColor(sf::Color::White);
	switch (this->selected)
	{
	case 0:
		this->play->setColor(sf::Color::Green);
		break;
	case 1:
		this->quit->setColor(sf::Color::Green);
		break;
	}
	window->draw(*this->title);
	window->draw(*this->play);
	window->draw(*this->quit);
}
void main_menu::Destroy(sf::RenderWindow* window)
{
	delete this->font;
	delete this->title;
	delete this->play;
	delete this->quit;
}

void main_menu::UpdateMode(sf::RenderWindow* window)
{
	switch (this->mode)
	{
	case 0:
		this->play->setString("<Easy>");
		break;
	case 1:
		this->play->setString("<Medium>");
		break;
	case 2:
		this->play->setString("<Hard>");
		break;
	case 3:
		this->play->setString("<Multi>");
		break;
	}
	this->play->setOrigin(this->play->getGlobalBounds().width / 2, this->play->getGlobalBounds().height / 2);
	this->play->setPosition(window->getSize().x / 2, window->getSize().y / 2);
}
