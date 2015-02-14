#pragma once

#include "game_state.h"

#define SCALE_SPEED 0.01f
#define MAX_SCALE 0.10

class main_menu : public tiny_state
{
public:
	void Initialize(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	sf::Font* font;
	sf::Text* title;
	sf::Text* play;
	sf::Text* quit;

	int selected;
	int mode;

	float scale;
	float scaleInc;

	bool upKey, downKey, leftKey, rightKey;

	void UpdateMode(sf::RenderWindow* window);
};