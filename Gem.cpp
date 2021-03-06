#include "Agent8.h"
#include "Gem.h"
#include "MainGame.h"
#include "Ring.h"
#include "vector"

Gem::Gem(Point2f pos)
	: GameObject(pos)
{
	m_pos = pos;
	SetType(OBJ_GEM);
	SetDrawOrder(5);
	SetUpdateOrder(5);
}

Gem::~Gem() {}

void Gem::Update(GameState& gState)
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
					gState.score += 1000;
					a8->SetSpeed(8.f);	// Reset speed to 8 for when blue gem is active  
					Ring::SpawnRings(m_pos);
					m_active = false;

				}
			}
		}

	}
}

void Gem::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();
	// Gem rotates back and forth on the spot
	float rotWobble = sin(gState.time * 3);
	blit.DrawRotated(blit.GetSpriteId("gem"), m_pos, 0, m_rot + rotWobble / 2);
}
