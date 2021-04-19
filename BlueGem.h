#pragma once
#include "Gem.h"
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"

class BlueGem : public Gem
{
public:
	BlueGem(Point2f pos);
	~BlueGem();
	void Update(GameState& state) override;
	void Draw(GameState& gState) const override;
	static BlueGem* CreateBlueGem(Point2f pos);
};