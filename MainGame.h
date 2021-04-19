#include "Play.h"
#pragma once

class Asteroid;
class Meteor;
class Agent8;
class Particle;

enum Agent8State
{
	STATE_BEGIN = 0,
	STATE_LEFT,
	STATE_RIGHT,
	STATE_FLY,
	STATE_DEAD,
};

struct GameState
{
	float time{0.f};
	float elapsedTime{ 0.f };
	int score{0};
	Asteroid* pAsteroid;
	Agent8* agent8;
	Agent8State agentState{ STATE_BEGIN };
	int level{1};
	float showLevelTimer{2.f};
	float levelStartTime;
};

bool HasCollided(Point2f pos1, Point2f pos2);
