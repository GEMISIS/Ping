#pragma once

#include <SFML/Audio.hpp>
#include "paddle_player.h"
#include "score.h"

extern int lastScorer;

#define BALL_SPEED 4
#define BALL_MAX_SPEED (BALL_SPEED * 1.25f)

#define STICK_FPS 2

class ball : public Entity
{
public:
	ball(Score* score1, Score* score2, paddle* player1, paddle* player2);
	
	void AddVelocity(paddle* paddle);

	bool GoingToCeil();
	bool GoingToFloor();

	float getHitX(float y);
	float getHitY(float x);

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

	bool timerRestart;
	sf::Clock delayTimer;
	sf::Time delayElapsed;
};
