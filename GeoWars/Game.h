#ifndef _GAME_H_
#define _GAME_H_

#include "Battery.h"
#include "LCD_HY28B.h"
#include "ScreenBuffer.h"
#include "GameObjectManager.h"
#include "Thumbstick.h"

class Game
{
public:
	static LCD_HY28B debugLcd;

	Game();
	static void Start();

	static GameObjectManager* Get_GameObjectManager();

private:
	enum gamestate_t { SPLASH_SCREEN, PLAYING };

	static uint32_t gameTime;
	static uint32_t prevTime;
	static uint16_t updateTime;
	static uint16_t frameTime;
	static uint16_t enemySpawnTime;

	static uint16_t minFrameTime;
	static uint16_t frameRate;
	static bool limitFramerate;
	static bool showFramerate;

	static gamestate_t gameState;
	static ScreenBuffer* screenBuffer;
	static GameObjectManager* gameObjectManager;

	static Thumbstick* thumbstickLeft;
	static Thumbstick* thumbstickRight;

	static Battery* battery;

	static void Game_Loop();
};

#endif // _GAME_H_
