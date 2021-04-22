#pragma once
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Particle.h"

class Ring : public Particle
{
public:
	Ring(Point2f pos, float scale, float life);
	~Ring();
	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
	static void SpawnRings(Point2f pos);

	void SetScale(float scale) { m_scale = scale; }
};
