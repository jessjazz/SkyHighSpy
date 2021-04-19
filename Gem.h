#pragma once
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"

class Gem : public GameObject
{
public:
	Gem(Point2f pos);
	~Gem();
	void Update(GameState& state) override;
	void Draw(GameState& gState) const override;
	static Gem* CreateGem(Point2f pos);

protected:
	float m_rot{0.f};
	float m_gemSpawnDelay{ 0.35f }; // To avoid agent 8 colliding with the gem as soon as it is spawned
};