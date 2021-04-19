#pragma once
#include "Gem.h"
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"

class Star : public Gem
{
public:
	Star(Point2f pos);
	~Star();
	void Update(GameState& state) override;
	void Draw(GameState& gState) const override;
	static Star* CreateStar(Point2f pos);
};