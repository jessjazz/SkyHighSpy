#pragma once
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"

class Particle : public GameObject
{
public:
	Particle(Point2f pos);
	~Particle();
	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
	static Particle* CreateParticle(Point2f pos);
	static void SpawnParticles(Point2f pos, Vector2f velocity);

protected:
	float m_lifeTime{75.f};
	float m_remainingLife{ m_lifeTime };
	float m_originalAlpha{ 0.2f };
	float m_alpha{ m_originalAlpha };
	float m_originalScale{ 0.75f };
	float m_scale{ m_originalScale };
	bool m_isDead{ false };
	static std::vector<Particle*> s_vParticles;
	static int m_particleIndex;
};