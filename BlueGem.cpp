#include "Agent8.h"
#include "BlueGem.h"
#include "Gem.h"
#include "MainGame.h"
#include "Ring.h"
#include "vector"

BlueGem::BlueGem(Point2f pos)
	: Gem(pos)
{
	m_pos = pos;
}

BlueGem::~BlueGem() {}

void BlueGem::Update(GameState& gState)
{
	PlayBlitter& blit = PlayBlitter::Instance();
	PlaySpeaker& speak = PlaySpeaker::Instance();

	for (GameObject* p : s_vUpdateList)
	{
		Agent8* a8 = dynamic_cast<Agent8*>(p);

		if (a8 != nullptr)
		{
			if (HasCollided(m_pos, a8->GetPosition()) && gState.agentState == STATE_FLY && gState.time > a8->GetKeyPressedTime() + m_gemSpawnDelay)
			{
				speak.StartSound("reward", false);
				gState.score += 1000;
				a8->SetSpeed(a8->GetSpeed() * 1.5f);	// Increase speed until another pickup is activated
				Ring::SpawnRings(m_pos);
				m_active = false;

			}
		}
	}
}

void BlueGem::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	float rotWobble = sin(gState.time * 3);
	blit.DrawRotated(blit.GetSpriteId("gem_blue"), m_pos, 0, m_rot + rotWobble / 2);
}

BlueGem* BlueGem::CreateBlueGem(Point2f pos)
{
	BlueGem* pBlueGem{ nullptr };
	pBlueGem = new BlueGem({ pos });
	pBlueGem->SetType(OBJ_GEM);
	pBlueGem->SetDrawOrder(5);
	pBlueGem->SetUpdateOrder(5);
	return pBlueGem;
}