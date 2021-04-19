#pragma once
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"

class Asteroid : public GameObject
{
public:
	Asteroid(Point2f pos);
	~Asteroid();
	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
	static Asteroid* CreateAsteroid(Point2f pos);
	static void SpawnAsteroids(GameState& gState);
	bool HasAsteroidCollided(Point2f pos1, Point2f pos2);
	void HandleCollision();
	
	float GetRotation() const { return m_rot; }
	void SetRotation(float rot) { m_rot = rot; }

protected:
	float m_rot{ 0.0f };
	int m_frameIndex{ 0 };
};