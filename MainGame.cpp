#include "MainGame.h"
#include "Asteroid.h"
#include "Meteor.h"
#include "Agent8.h"
#include "Particle.h"
#define PLAY_IMPLEMENTATION
#include "Play.h"

constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;
constexpr int DISPLAY_SCALE = 1;

GameState gState;

// The entry point for a Windows program
int WINAPI WinMain( PLAY_WINARGS_IN )
{
	PlayBuffer& buff = PlayBuffer::Instance( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE, 0 );
	PlayBlitter& blit = PlayBlitter::Instance("Data\\Sprites\\");
	PlaySpeaker& speak = PlaySpeaker::Instance("Data\\Sounds\\");

	// Do things here that only need to be performed once at the start of your application
	blit.SetDisplayBuffer(buff.GetDisplayBuffer(), DISPLAY_WIDTH, DISPLAY_HEIGHT);
	blit.LoadBackground("Data\\Backgrounds\\background.png");
	speak.StartSound("music", true);
	blit.CentreAllSpriteOrigins();
	blit.SetSpriteOrigin(blit.GetSpriteId("agent8_left"), { 50, 110 });
	blit.SetSpriteOrigin(blit.GetSpriteId("agent8_right"), { 50, 110 });
	blit.SetSpriteOrigin(blit.GetSpriteId("agent8_fly"), { 60, 100 });
	gState.agent8 = Agent8::CreateAgent8({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 });

	return buff.HandleWindows( PLAY_WINARGS_OUT, L"Sky-High Spy" );
}

// Called by the PlayBuffer once for each frame of the game (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	PlayBuffer& buff = PlayBuffer::Instance();
	PlayBlitter& blit = PlayBlitter::Instance();

	gState.elapsedTime = elapsedTime;
	gState.time += elapsedTime;

	blit.DrawBackground();
	blit.DrawStringCentred(blit.GetSpriteId("105px"), { DISPLAY_WIDTH / 2, 40 }, "Score: " + std::to_string(gState.score));
	blit.DrawStringCentred(blit.GetSpriteId("64px"), { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 50 }, "arrow keys to rotate and space to launch");
	GameObject::UpdateAll(gState);
	GameObject::DrawAll(gState);
	if (gState.time < gState.levelStartTime + gState.showLevelTimer && gState.agentState != STATE_DEAD)
	{
		blit.DrawStringCentred(blit.GetSpriteId("151px"), { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "Level " + std::to_string(gState.level));
	}
	buff.Present();
	return buff.KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
void MainGameExit( void )
{
	GameObject::DestroyAll();
	PlayBuffer::Destroy();
	PlayBlitter::Destroy();
}

bool HasCollided(Point2f pos1, Point2f pos2)
{
	Vector2f d = pos2 - pos1;
	float dist = sqrt((d.x * d.x) + (d.y * d.y));
	if (dist < 50)
	{
		return true;
	}
	else
	{
		return false;
	}
}
