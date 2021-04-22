#include "MainGame.h"
#include "Particle.h"
#include "Random.h"

std::vector<Particle*> Particle::s_vParticles;
int Particle::m_particleIndex{ 0 };

Particle::Particle(Point2f pos)
	: GameObject(pos)
{
	m_pos = pos;
	SetVelocity({ 0,0 });
	SetType(OBJ_PARTICLE);
	SetDrawOrder(6);
	SetUpdateOrder(6);
}

Particle::~Particle()
{}

void Particle::Update(GameState& gState)
{
	for (Particle* particle : s_vParticles)
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
		particle->m_pos += particle->m_velocity * gState.elapsedTime;
	}
}

void Particle::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	int id = blit.GetSpriteId("particle");

	for (Particle* p : s_vParticles)
	{
		if (!m_isDead)
		{
			blit.DrawRotated(id, m_pos, 0, 0.f, m_scale, m_alpha);
		}
	}
}

void Particle::SpawnParticles(Point2f pos, float speed, float rotation)
{
	// Reserve memory and fill vector with pointers to particles
	if (s_vParticles.empty())
	{
		s_vParticles.reserve(100);
	}

	// If vector is not full, create a particle and add to vector
	if (s_vParticles.size() < 100)
	{
		Particle* p = new Particle({ pos.x + (speed * sin(rotation)), pos.y + (speed * -cos(rotation)) });
		p->m_velocity.x += p->m_velocityVariation.x * (Random::Float() - 0.5f);
		p->m_velocity.y += p->m_velocityVariation.y * (Random::Float() - 0.5f);
		s_vParticles.push_back(p);
	}
	// If the vectr is full, revive a particle and reset values
	else if (s_vParticles.size() == 100)
	{
		s_vParticles.at(m_particleIndex)->m_isDead = false;
		s_vParticles[m_particleIndex]->m_pos = { pos.x + (speed * sin(rotation)), pos.y + (speed * -cos(rotation)) };
		s_vParticles[m_particleIndex]->m_remainingLife = s_vParticles[m_particleIndex]->m_lifeTime;
		s_vParticles[m_particleIndex]->m_scale = s_vParticles[m_particleIndex]->m_originalScale;
		s_vParticles[m_particleIndex]->m_alpha = s_vParticles[m_particleIndex]->m_originalAlpha;
		
		// Wrap particleIndex to 0 at the end of the vector
		if (m_particleIndex != 99)
		{
			m_particleIndex++;
		}
		else
		{
			m_particleIndex = 0;
		}
	}
}
