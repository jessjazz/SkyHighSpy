#include "Agent8.h"
#include "MainGame.h"
#include "Ring.h"
#include "Star.h"
#include "vector"

Star::Star(Point2f pos)
	: Gem(pos)
{
	m_pos = pos;
	SetType(OBJ_GEM);
	SetDrawOrder(5);
	SetUpdateOrder(5);
}

Star::~Star() {}

void Star::Update(GameState& gState)
{
	PlayBlitter& blit = PlayBlitter::Instance();
	PlaySpeaker& speak = PlaySpeaker::Instance();

	for (GameObject* p : s_vUpdateList)
	{
		if (p->GetType() == OBJ_AGENT8)
		{
			Agent8* a8 = static_cast<Agent8*>(p);
			if (a8 != nullptr)
			{
				if (HasCollided(m_pos, a8->GetPosition()) && gState.agentState == STATE_FLY && gState.time > a8->GetKeyPressedTime() + m_gemSpawnDelay)
				{
					speak.StartSound("reward", false);
					gState.score += 5000;
					a8->SetSpeed(8.f); // Reset speed to 8 for when blue gem is active 
					Ring::SpawnRings(m_pos);
					m_active = false;

				}
			}
		}
	}
}

void Star::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	float rotWobble = sin(gState.time * 3);
	blit.DrawRotated(blit.GetSpriteId("star"), m_pos, 0, m_rot + rotWobble / 2);
}
