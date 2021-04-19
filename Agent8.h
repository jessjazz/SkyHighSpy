#pragma once
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"

class Agent8 : public GameObject
{
public:
	Agent8(Point2f pos);
	~Agent8();

	void Update(GameState& state) override;
	void Draw(GameState& gState) const override;
	static Agent8* CreateAgent8(Point2f pos);
	void SetSpeed(float speed) { m_speed = speed; }
	float GetSpeed() const { return m_speed; }
	float GetKeyPressedTime() const { return m_KeyPressedTime; }

private:
	float m_rot{};
	float m_speed{8.f};
	float m_KeyPressedTime{ 0.f };
	float m_timerCurrent{ 0.f };
	float m_timerTotal{ 0.05f };
};