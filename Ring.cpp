#include "MainGame.h"
#include "Ring.h"

Ring::Ring(Point2f pos)
	: Particle(pos)
{
	m_pos = pos;
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
		m_remainingLife -= gState.elapsedTime * 100.f;
		m_scale += 0.15f; // Scale increases with each frame
	}
}

void Ring::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	blit.DrawRotated(blit.GetSpriteId("ring"), m_pos, 0, 0.f, m_scale);
}

Ring* Ring::CreateRing(Point2f pos, float scale)
{
	Ring* pRing{ nullptr };
	pRing = new Ring({ pos });
	pRing->SetScale(scale);
	pRing->SetType(OBJ_PARTICLE);
	pRing->SetDrawOrder(7);
	pRing->SetUpdateOrder(7);
	return pRing;
}

void Ring::SpawnRings(Point2f pos)
{
	for (float scale = 0.5f; scale < 2.0f; scale += 0.5f)
	{
		Ring* r = Ring::CreateRing(pos, scale);
	}
}