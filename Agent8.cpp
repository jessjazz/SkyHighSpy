#include "MainGame.h"
#include "Agent8.h"
#include "Asteroid.h"
#include "BlueGem.h"
#include "BrokenAsteroid.h"
#include "Gem.h"
#include "Meteor.h"
#include "Particle.h"
#include "Star.h"
#include "vector"

constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;

Agent8::Agent8(Point2f pos)
	: GameObject(pos)
{
	m_pos = pos;
	SetType(OBJ_AGENT8);
	SetDrawOrder(2);
	SetUpdateOrder(1);
}

Agent8::~Agent8() {}

void Agent8::Update(GameState& gState)
{
	PlaySpeaker& speak = PlaySpeaker::Instance();
	PlayBlitter& blit = PlayBlitter::Instance();
	PlayBuffer& buff = PlayBuffer::Instance();
	
	// Seed rand()
	srand(time(NULL));

	// Start timer to measure frames for particle spawning
	m_timerCurrent += gState.elapsedTime / 2;

	// Spawn agent 8 on an asteroid at a random xPos when game begins
	if (GameObject::GetObjectCount(OBJ_ASTEROID) == 0 && gState.agentState == STATE_BEGIN)
	{
		m_pos = { rand() % DISPLAY_WIDTH, 0 };
		gState.pAsteroid = new Asteroid(m_pos);
		m_velocity = gState.pAsteroid->GetVelocity();
		m_pos += m_velocity;
		gState.agentState = STATE_STILL;
	}

	// Spawn increasing numbers of asteroids per game level after level 1
	if (GameObject::GetObjectCount(OBJ_ASTEROID) == 0 && GameObject::GetObjectCount(OBJ_GEM) == 0 && gState.agentState != STATE_DEAD && gState.agentState != STATE_BEGIN)
	{
		Asteroid::SpawnAsteroids(gState);
	}

	// Spawn a meteor that is constantly moving across the screen
	if (GameObject::GetObjectCount(OBJ_METEOR) == 0 && gState.agentState != STATE_DEAD)
	{
		new Meteor({ rand() % DISPLAY_WIDTH, rand() % DISPLAY_HEIGHT });
	}

	// Agent 8 dies when he collides with meteor
	std::vector<GameObject*> meteors;
	GameObject::GetObjectList(OBJ_METEOR, meteors);
	for (GameObject* meteor : meteors)
	{
		if (gState.agentState == STATE_FLY && HasCollided(m_pos, meteor->GetPosition()))
		{
			gState.agentState = STATE_DEAD;
			speak.StartSound("combust", false);
			meteor->SetActive(false);
		}
	}
	
	std::vector<GameObject*> asteroids;
	GameObject::GetObjectList(OBJ_ASTEROID, asteroids);
	for (GameObject* asteroid : asteroids)
	{
		if (gState.agentState == STATE_FLY && HasCollided(m_pos, asteroid->GetPosition()) && asteroid->GetType() != OBJ_BROKEN)
		{
			// Set Agent 8 pos and velocity to the colliding asteroid's pos and velocity when flying
			m_pos = asteroid->GetPosition();
			m_velocity = asteroid->GetVelocity();
			// Reverse rotation when Agent 8 lands on an asteroid
			m_rot += PLAY_PI;
			gState.agentState = STATE_STILL;
		}
		// Keep Agent 8 attached to asteroid
		if (gState.agentState != STATE_FLY && gState.agentState != STATE_DEAD && HasCollided(m_pos, asteroid->GetPosition()) && asteroid->GetType() != OBJ_BROKEN)
		{
			m_pos = asteroid->GetPosition();
			if (m_pos.y > DISPLAY_HEIGHT)
			{
				m_pos = { m_pos.x + 25, 0 };
			}
			else if (m_pos.y < 0)
			{
				m_pos = { m_pos.x + 25, DISPLAY_HEIGHT };
			}
			else if (m_pos.x > DISPLAY_WIDTH)
			{
				m_pos = { 0, m_pos.y + 25 };
			}
			else if (m_pos.x < 0)
			{
				m_pos = { DISPLAY_WIDTH, m_pos.y + 25 };
			}
		}

	}

	std::vector<GameObject*>Gems;
	GameObject::GetObjectList(OBJ_GEM, Gems);

	if (gState.agentState == STATE_DEAD)
	{
		// Continue flying in the directing Agent 8 was going when dead
		m_velocity.x = m_speed * sin(m_rot);
		m_velocity.y = m_speed * -cos(m_rot);
		m_pos += m_velocity;
		blit.DrawStringCentred(blit.GetSpriteId("151px"), {675, DISPLAY_HEIGHT/2}, "Game Over");
		blit.DrawStringCentred(blit.GetSpriteId("64px"), { 650, 450 }, "Press space to play again!");
		// Set all other GameObjects to inactive
		for (GameObject* gems : Gems)
		{
			gems->SetActive(false);
		}
		for (GameObject* a : asteroids)
		{
			a->SetActive(false);
		}
		// Reset game when space is pressed
		if (buff.KeyPressed(VK_SPACE))
		{
			gState.agentState = STATE_BEGIN;
			gState.level = 1;
			gState.levelStartTime = gState.time;
			gState.score = 0;
			m_speed = 8.f;
			speak.StartSound("music", true);
		}
	}
	
	if (gState.agentState == STATE_FLY)
	{
		// Rotate slightly to change direction when flying
		if (buff.KeyDown(VK_LEFT))
		{
			m_rot -= 0.02f;
		}

		if (buff.KeyDown(VK_RIGHT))
		{
			m_rot += 0.02f;
		}

		m_velocity.x = m_speed * sin(m_rot);
		m_velocity.y = m_speed * -cos(m_rot);

		// Wrap around to other side of the screen
		if (m_pos.y > DISPLAY_HEIGHT)
		{
			m_pos = { m_pos.x, 0 };
		}
		else if (m_pos.y < 0)
		{
			m_pos = { m_pos.x, DISPLAY_HEIGHT };
		}
		else if (m_pos.x > DISPLAY_WIDTH)
		{
			m_pos = { 0, m_pos.y };
		}
		else if (m_pos.x < 0)
		{
			m_pos = { DISPLAY_WIDTH, m_pos.y};
		}

		m_pos += m_velocity;
		
		// Spawn particles every x frames, determined by timer in Agent8.h
		if (m_timerCurrent >= m_timerTotal)
		{
			for (int i = 0; i < 3; i++)
			{
				Particle::SpawnParticles(m_pos, m_speed, m_rot);
			}
			m_timerCurrent = gState.elapsedTime / 2;
		}
	}


	if (gState.agentState != STATE_FLY && gState.agentState != STATE_DEAD && gState.agentState != STATE_BEGIN)
	{
		// Rotate around asteroid
		if (buff.KeyDown(VK_LEFT))
		{
			gState.agentState = STATE_LEFT;
			m_rot -= 0.05f;
		}
		else if (buff.KeyDown(VK_RIGHT))
		{
			gState.agentState = STATE_RIGHT;
			m_rot += 0.05f;
		}
		else 
		{
			gState.agentState = STATE_STILL;
		}
			
		if (buff.KeyPressed(VK_SPACE))
		{
			gState.agentState = STATE_FLY;
			speak.StartSound("explode", false);
			// Spawn broken pieces of asteroid
			new BrokenAsteroid({ m_pos }, 0, {0, -15});
			new BrokenAsteroid({ m_pos }, 1, {-15, 0});
			new BrokenAsteroid({ m_pos }, 2, {2, 15});
			m_KeyPressedTime = gState.time; // Capture key pressed time used to avoid immediately colliding with gems
			// Spawn random pickups
			int RandRoll{ GameObject::RandomRoll(8) };
			if (RandRoll != 1 && RandRoll != 8)
			{
				new Gem({ m_pos.x, m_pos.y});
			}
			else if (RandRoll == 1)
			{
				new BlueGem({ m_pos.x, m_pos.y });
			}
			else if (RandRoll == 8)
			{
				new Star({ m_pos.x, m_pos.y });
			}
			// Set asteroid to inactive after Agent 8 jumps off
			for (GameObject* asteroid : asteroids)
			{
				if (asteroid->GetType() == OBJ_ASTEROID && HasCollided(m_pos, asteroid->GetPosition()))
				{
					asteroid->SetActive(false);
				}
			}
		}
	}
}

void Agent8::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	switch (gState.agentState)
	{
	case STATE_BEGIN:
		blit.DrawRotated(blit.GetSpriteId("agent8_left"), m_pos, 0, m_rot);
		break;
	case STATE_STILL:
		blit.DrawRotated(blit.GetSpriteId("agent8_left"), m_pos, 0, m_rot);
		break;
	case STATE_LEFT:
		blit.DrawRotated(blit.GetSpriteId("agent8_left"), m_pos, 18.0f * gState.time, m_rot);
		break;
	case STATE_RIGHT:
		blit.DrawRotated(blit.GetSpriteId("agent8_right"), m_pos, 18.0f * gState.time, m_rot);
		break;
	case STATE_FLY:
		blit.DrawRotated(blit.GetSpriteId("agent8_fly"), m_pos, 0, m_rot);
		break;
	case STATE_DEAD:
		blit.DrawRotated(blit.GetSpriteId("agent8_dead"), m_pos, 5.0f * gState.time, m_rot);
		break;
	}
}
