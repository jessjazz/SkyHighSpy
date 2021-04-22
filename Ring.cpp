#include "MainGame.h"
#include "Ring.h"

Ring::Ring(Point2f pos, float scale, float life)
	: Particle(pos)
{
	m_pos = pos;
	SetScale(scale);
	SetType(OBJ_PARTICLE);
	SetDrawOrder(7);
	SetUpdateOrder(7);
	SetLife(life);
	SetRemainingLife(m_lifeTime);
}

Ring::~Ring()
{}

void Ring::Update(GameState& gState)
{
	if (m_remainingLife <= 0.0f)
	{
		m_active = false;
	}
	else
	{
		// Decrease remaining life over time
		m_remainingLife -= gState.elapsedTime * 100.0f;
		m_scale += 0.15f; // Scale increases with each frame
	}
}

void Ring::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	blit.DrawRotated(blit.GetSpriteId("ring"), m_pos, 0, 0.f, m_scale);
}

void Ring::SpawnRings(Point2f pos)
{
	for (float scale = 0.5f; scale < 2.0f; scale += 0.5f)
	{
		new Ring(pos, scale, 15.f);
	}
}
