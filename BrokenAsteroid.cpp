#include "BrokenAsteroid.h"

constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;

BrokenAsteroid::BrokenAsteroid(Point2f pos, int frameIndex, Vector2f velocity)
	: Asteroid(pos)
{
	m_pos = pos;
	SetType(OBJ_BROKEN);
	SetDrawOrder(1);
	SetUpdateOrder(4);
	SetVelocity({ velocity });
	SetFrameIndex(frameIndex);
}

BrokenAsteroid::~BrokenAsteroid() {}

void BrokenAsteroid::Update(GameState& gState)
{
	m_rot = 0.f;
	// Set to inactive if off screen
	if (m_pos.y > DISPLAY_HEIGHT || m_pos.y < 0 || m_pos.x > DISPLAY_WIDTH || m_pos.x < 0)
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
