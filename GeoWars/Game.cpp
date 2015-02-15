#include <WProgram.h>
#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

// For testing only.
#include "sprites.h"
#include "ASCII.h"

uint32_t Game::gameTime;
uint32_t Game::prevTime;
uint16_t Game::updateTime;
uint16_t Game::frameTime;
uint16_t Game::enemySpawnTime;

uint16_t Game::minFrameTime;
uint16_t Game::frameRate;
bool Game::limitFramerate;
bool Game::showFramerate;

LCD_HY28B Game::debugLcd;

Game::gamestate_t Game::gameState;
ScreenBuffer* Game::screenBuffer = new ScreenBuffer;
GameObjectManager* Game::gameObjectManager = new GameObjectManager;

Thumbstick* Game::thumbstickLeft = new Thumbstick(A8, A7, 23);
Thumbstick* Game::thumbstickRight = new Thumbstick(A6, A5, 18);

Battery* Game::battery = new Battery();

void Game::Start()
{
	debugLcd.Set_Font(&ASCII);

	gameState = PLAYING;

	Player* player = new Player();
	player->Set_Thumbsticks(thumbstickLeft, thumbstickRight);
	player->Sprite(sprite_player);
	player->Fire_Rate(300);
	player->Set_Max_Velocity(200);
	player->Move(160, 120);
	gameObjectManager->Add(player);

	int numEnemys = 0;
	Enemy* enemyArray[numEnemys];
	for (int i = 0; i < numEnemys; i++)
	{
		enemyArray[i] = new Enemy();
		enemyArray[i]->Sprite(sprite_enemy);
		enemyArray[i]->Move(random(0, 320), random(0, 240));
		gameObjectManager->Add(enemyArray[i]);
	}

	// This need to happen once before the gameloop starts otherwise first updateTime is large.
	gameTime = millis();
	updateTime = 0;
	frameTime = 0;
	prevTime = gameTime;
	minFrameTime = 16; // 33 = 30fps. 16 = 60fps.
	limitFramerate = true;
	showFramerate = false;

	while (1)
	{
		Game_Loop();
	}
}

void Game::Game_Loop()
{
	gameTime = millis();
	updateTime = gameTime - prevTime;
	prevTime = gameTime;

	frameTime += updateTime;
	frameRate = 1000 / frameTime; // 1000(ms) / updateTime(ms)

	enemySpawnTime += updateTime;

	switch(gameState)
	{
		case MAIN_MENU:
			break;

		case PLAYING:
			gameObjectManager->Update_All(updateTime);

			if (frameTime > minFrameTime || !limitFramerate)
			{
				if (showFramerate)
				{
					debugLcd.Print_Int(frameRate, 0, 0, WHITE);
				}

				debugLcd.Print_Int(battery->Percentage(), 0, 0, WHITE);

				battery->Show_Level();
				gameObjectManager->Draw_All(screenBuffer);
				battery->Show_Level(); // Before and after drawing screen buffer reduces flicker.

				frameTime = 0;
			}

			// if (enemySpawnTime > 2000)
			// {
			// 	Enemy* enemy = new Enemy();
			// 	enemy->Sprite(sprite_enemy);
			// 	enemy->Move(random(0, 320), random(0, 240));
			// 	gameObjectManager->Add(enemy);
			// 	enemySpawnTime = 0;
			// }

			break;

		default:
			break;
	}
}

GameObjectManager* Game::Get_GameObjectManager()
{
	return gameObjectManager;
} 
