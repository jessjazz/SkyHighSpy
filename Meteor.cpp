#include "MainGame.h"
#include "Meteor.h"

Meteor::Meteor(Point2f pos)
	: GameObject(pos)
{
	m_pos = pos;
}

Meteor::~Meteor()
{}

void Meteor::Update(GameState& gState)
{
	m_velocity = { 2, -10 };
	// Wrap around to other side of the screen
	if (m_pos.y < 0)
	{
		m_pos = { m_pos.x + 25, 720 };
	}
	else if (m_pos.x > 1280)
	{
		m_pos = { 0, 720 };
	}

	m_pos += m_velocity;
}

void Meteor::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	blit.DrawRotated(blit.GetSpriteId("meteor"), m_pos, 5.0f * gState.time, m_rot);
}

Meteor* Meteor::CreateMeteor(Point2f pos)
{
	Meteor* pMeteor{ nullptr };
	pMeteor = new Meteor({ pos });
	pMeteor->SetType(OBJ_METEOR);
	pMeteor->SetDrawOrder(4);
	pMeteor->SetUpdateOrder(3);
	return pMeteor;
}