#include "MainGame.h"
#include "Meteor.h"

constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;

Meteor::Meteor(Point2f pos)
	: GameObject(pos)
{
	m_pos = pos;
	SetType(OBJ_METEOR);
	SetDrawOrder(4);
	SetUpdateOrder(3);
}

Meteor::~Meteor()
{}

void Meteor::Update(GameState& gState)
{
	m_velocity = { 2, -10 };
	// Wrap around to other side of the screen
	if (m_pos.y < 0)
	{
		m_pos = { m_pos.x + 25, DISPLAY_HEIGHT };
	}
	else if (m_pos.x > DISPLAY_WIDTH)
	{
		m_pos = { 0, DISPLAY_HEIGHT };
	}

	m_pos += m_velocity;
}

void Meteor::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	blit.DrawRotated(blit.GetSpriteId("meteor"), m_pos, 5.0f * gState.time, m_rot);
}
