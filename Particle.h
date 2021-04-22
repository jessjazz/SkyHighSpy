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
	static void SpawnParticles(Point2f pos, float speed, float rotation);

	void SetLife(float life) { m_lifeTime = life; }
	void SetRemainingLife(float remainingLife) { m_remainingLife = remainingLife; }

protected:
	float m_lifeTime{75.f};
	float m_remainingLife{ m_lifeTime };
	float m_originalAlpha{ 0.2f };
	float m_alpha{ m_originalAlpha };
	float m_originalScale{ 0.75f };
	float m_scale{ m_originalScale };
	Vector2f m_velocityVariation = {3.0f, 1.0f};
	bool m_isDead{ false };
	static std::vector<Particle*> s_vParticles;
	static int m_particleIndex;
};
