#include "MainGame.h"
#include "Particle.h"

std::vector<Particle*> Particle::s_vParticles;
int Particle::m_particleIndex{ 0 };

Particle::Particle(Point2f pos)
	: GameObject(pos)
{
	m_pos = pos;
}

Particle::~Particle()
{}

void Particle::Update(GameState& gState)
{
	for (auto particle : s_vParticles)
	{
		if (particle->m_isDead)
		{
			continue;
		}
		if (particle->m_remainingLife <= 0.0f)
		{
			particle->m_isDead = true;
			continue;
		}
		// Decrease remaining life over time
		particle->m_remainingLife -= gState.elapsedTime;
		float life = particle->m_remainingLife / particle->m_lifeTime;
		particle->m_scale = m_originalScale * life; // Scale decreases with life
		particle->m_alpha  = m_originalAlpha * life; // Alpha decreases with life
	}
}

void Particle::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	for (auto p : s_vParticles)
	{
		if (!m_isDead)
		{
			blit.DrawRotated(blit.GetSpriteId("particle"), m_pos, 0, 0.f, m_scale, m_alpha);
		}
	}
}

Particle* Particle::CreateParticle(Point2f pos)
{
	Particle* pParticle{ nullptr };
	pParticle = new Particle({ pos });
	pParticle->SetType(OBJ_PARTICLE);
	pParticle->SetDrawOrder(6);
	pParticle->SetUpdateOrder(6);
	return pParticle;
}

void Particle::SpawnParticles(Point2f pos, Vector2f velocity)
{
	// Reserve memory and fill vector with pointers to particles
	if (s_vParticles.empty())
	{
		s_vParticles.reserve(50);
	}

	// If vector is not full, create a particle and add to vector
	if (s_vParticles.size() < 50)
	{
		Particle* p = Particle::CreateParticle({ pos.x + (velocity.x + static_cast<float>(rand() % 35 + (-35))), pos.y + (velocity.y + static_cast<float>(rand() % 35 + (-35))) });
		s_vParticles.push_back(p);
	}
	// If the vectr is full, revive a particle and reset values
	else if (s_vParticles.size() == 50)
	{
		s_vParticles.at(m_particleIndex)->m_isDead = false;
		s_vParticles[m_particleIndex]->m_pos = { pos.x + (velocity.x + static_cast<float>(rand() % 35 + (-35))), pos.y + (velocity.y + static_cast<float>(rand() % 35 + (-35))) };
		s_vParticles[m_particleIndex]->m_remainingLife = s_vParticles[m_particleIndex]->m_lifeTime;
		s_vParticles[m_particleIndex]->m_scale = s_vParticles[m_particleIndex]->m_originalScale;
		s_vParticles[m_particleIndex]->m_alpha = s_vParticles[m_particleIndex]->m_originalAlpha;
		
		// Wrap particleIndex to 0 at the end of the vector
		if (m_particleIndex != 49)
		{
			m_particleIndex++;
		}
		else
		{
			m_particleIndex = 0;
		}
	}
}