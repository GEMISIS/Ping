#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite
{
public:
	Entity()
	{
		this->texture = new sf::Texture();
	}

	void Load(std::string filename)
	{
		this->texture->loadFromFile("Graphics/sprites/" + filename);
		this->setTexture(*this->texture);
	}

	virtual void Update()
	{
		this->move(this->velocity);
	}

	bool CheckCollision(Entity* entity)
	{
		return this->getGlobalBounds().intersects(entity->getGlobalBounds());
	}

	~Entity()
	{
		delete this->texture;
	}
protected:
	sf::Vector2f velocity;
private:
	sf::Texture* texture;
};

