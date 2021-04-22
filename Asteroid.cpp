#include <math.h>
#include "MainGame.h"
#include "Asteroid.h"

constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;

Asteroid::Asteroid(Point2f pos)
	: GameObject(pos)
{
	m_pos = pos;
	SetType(OBJ_ASTEROID);
	SetDrawOrder(3);
	SetUpdateOrder(2);
	SetMass(100.f);
	SetVelocity({ rand() % 3 + (-1), rand() % 3 + 2 });
	SetRotation(atan2(m_velocity.y, m_velocity.x));
}

Asteroid::~Asteroid()
{}

void Asteroid::Update(GameState& gState)
{	
	PlayBuffer& buff = PlayBuffer::Instance();
	// If asteroid goes off the screen, move it to the opposite side of the screen +25px
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

	// Handle collision with other asteroids
	HandleCollision();

	// Rotate sprite to match direction
	m_rot = atan2(m_velocity.y, m_velocity.x) + PLAY_PI/2;

	m_pos += m_velocity;
}

void Asteroid::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	blit.DrawRotated(blit.GetSpriteId("asteroid"), m_pos, 5.0f * gState.time, m_rot);
}

void Asteroid::SpawnAsteroids(GameState& gState)
{
	PlayBlitter& blit = PlayBlitter::Instance();

	std::vector<GameObject*> asteroids;
	GameObject::GetObjectList(OBJ_ASTEROID, asteroids);

	for (int i = 0; i < gState.level + 1; i++)
	{
		new Asteroid({ rand() % DISPLAY_WIDTH, rand() % 2 + (-2) });
		bool done{ false };
		// Check if any asteroids exist at the randomly generated xPos so they won't spawn on top of each other
		if (GameObject::GetObjectCount(OBJ_ASTEROID) != 0)
		{
			for (GameObject* asteroid : asteroids)
			{
				while (!done)
				{
					int xPos = rand() % DISPLAY_WIDTH;
					if (xPos <= asteroid->GetPosition().x - 100 || xPos >= asteroid->GetPosition().x + 100)
					{
						new Asteroid({ xPos, 0 });
						done = true;
					}
					else
					{
						continue;
					}
				}
			}
		}
	}
	gState.level++;
	gState.levelStartTime = gState.time;
}

bool Asteroid::HasAsteroidCollided(Point2f pos1, Point2f pos2)
{
	Vector2f d = pos2 - pos1;
	float dist = sqrt((d.x * d.x) + (d.y * d.y));
	if (dist <= 120)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// Detect collision and move asteroids accordingly
void Asteroid::HandleCollision()
{
	std::vector<GameObject*> asteroids;
	GameObject::GetObjectList(OBJ_ASTEROID, asteroids);
	for (size_t i = 0; i < asteroids.size() - 1; i++)
	{
		GameObject* asteroid = asteroids[i];
		for (size_t j = i + 1; j < asteroids.size(); j++)
		{
			GameObject* target = asteroids[j];
			if (HasAsteroidCollided(asteroid->GetPosition(), target->GetPosition()))
			{
				Point2f aPos{ asteroid->GetPosition() };
				Point2f tPos{ target->GetPosition() };
				
				// Calculate distance asteroids are overlapping
				Vector2f d = tPos - aPos;
				float dist = sqrt((d.x * d.x) + (d.y * d.y));
				float overlap = 0.5f * (dist - 120.0f);
				
				// Displace current asteroid
				asteroid->SetPosition({ (aPos.x - (overlap * (aPos.x - tPos.x) / dist)),
										(aPos.y - (overlap * (aPos.y - tPos.y) / dist)) });
				
				// Displace target asteroid
				target->SetPosition({ (tPos.x + (overlap * (aPos.x - tPos.x) / dist)),
									  (tPos.y + (overlap * (aPos.y - tPos.y) / dist)) });
				
				// Normal
				float nx = (tPos.x - aPos.x) / dist;
				float ny = (tPos.y - aPos.y) / dist;

				// Tangent
				float tx = -ny;
				float ty = nx;

				// Dot Product Tangent
				float dpTan1 = asteroid->GetVelocity().x * tx + asteroid->GetVelocity().y * ty;
				float dpTan2 = target->GetVelocity().x * tx + target->GetVelocity().y * ty;

				// Dot Product Normal
				float dpNorm1 = asteroid->GetVelocity().x * nx + asteroid->GetVelocity().y * ny;
				float dpNorm2 = target->GetVelocity().x * nx + target->GetVelocity().y * ny;

				// Conservation of momentum
				float aMass{ asteroid->GetMass() };
				float tMass{ target->GetMass() };

				float m1 = (dpNorm1 * (aMass - tMass) + 2.0f * tMass * dpNorm2) / (aMass + tMass);
				float m2 = (dpNorm2 * (tMass - aMass) + 2.0f * aMass * dpNorm1) / (aMass + tMass);

				// Set velocity after collision
				asteroid->SetVelocity({(tx * dpTan1 + nx * m1), (ty * dpTan1 + ny * m1)});
				target->SetVelocity({(tx * dpTan2 + nx * m2), (ty * dpTan2 + ny * m2)});
			}
		}
	}
}
