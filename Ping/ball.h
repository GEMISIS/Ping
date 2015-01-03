#pragma once

#include <SFML/Audio.hpp>
#include "paddle_player.h"
#include "score.h"

class ball : public Entity
{
public:
	ball(Score* score1, Score* score2, paddle* player1, paddle* player2);
	void Update(sf::RenderWindow* window);
	void Reset(sf::RenderWindow* window);
	~ball();
private:
	Score* score1;
	Score* score2;
	paddle* player1;
	paddle* player2;

	sf::SoundBuffer* buffer;
	sf::Sound* sound;
};
