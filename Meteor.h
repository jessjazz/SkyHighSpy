#pragma once
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"

class Meteor : public GameObject
{
public:
	Meteor(Point2f pos);
	~Meteor();
	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
	static Meteor* CreateMeteor(Point2f pos);

	float GetRotation() const { return m_rot; }
	void SetRotation(float rot) { m_rot = rot; }

protected:
	float m_rot{ 0.25f };
};