#pragma once
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Particle.h"

class Ring : public Particle
{
public:
	Ring(Point2f pos);
	~Ring();
	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
	static Ring* CreateRing(Point2f pos, float scale);
	static void SpawnRings(Point2f pos);

	void SetScale(float scale) { m_scale = scale; }

protected:
	float m_lifeTime{ 15.f };
	float m_remainingLife{ m_lifeTime };
};