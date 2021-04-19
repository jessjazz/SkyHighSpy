#include "BrokenAsteroid.h"

BrokenAsteroid::BrokenAsteroid(Point2f pos)
	: Asteroid(pos)
{
	m_pos = pos;
}

BrokenAsteroid::~BrokenAsteroid() {}

void BrokenAsteroid::Update(GameState& gState)
{
	m_rot = 0.f;
	// Set to inactive if off screen
	if (m_pos.y > 720 || m_pos.y < 0 || m_pos.x > 1280 || m_pos.x < 0)
	{
		m_active = false;
	}
	m_pos += m_velocity;
}

void BrokenAsteroid::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	blit.DrawRotated(blit.GetSpriteId("asteroid_pieces"), m_pos, m_frameIndex, m_rot);
}

BrokenAsteroid* BrokenAsteroid::CreateBrokenAsteroid(Point2f pos, int frameIndex, Vector2f velocity)
{
	BrokenAsteroid* pBrokenAsteroid{ nullptr };
	pBrokenAsteroid = new BrokenAsteroid({ pos });
	pBrokenAsteroid->SetType(OBJ_BROKEN);
	pBrokenAsteroid->SetDrawOrder(1);
	pBrokenAsteroid->SetUpdateOrder(4);
	pBrokenAsteroid->SetVelocity({velocity});
	pBrokenAsteroid->SetFrameIndex(frameIndex);
	return pBrokenAsteroid;
}