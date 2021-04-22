#pragma once
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Asteroid.h"

class BrokenAsteroid : public Asteroid
{
public:
	BrokenAsteroid(Point2f pos, int frameIndex, Vector2f velocity);
	~BrokenAsteroid();
	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;

	int GetFrameIndex() { return m_frameIndex; }
	void SetFrameIndex(int frameIndex) { m_frameIndex = frameIndex; }
};
