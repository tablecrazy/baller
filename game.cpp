#include "game.h"
#include "surface.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
#include "template.h"
#include <math.h>
#include <cstring>
#include <iostream>

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	void Circle(Surface* s, float x, float y, float r)
	{
		for (int i = 0; i < 64; i++)
		{
			float r1 = (float)i * PI / 32, r2 = (float)(i + 1) * PI / 32;
			s->Line(x - r * sinf(r1), y - r * cosf(r1),
				x - r * sinf(r2), y - r * cosf(r2), 0xff0000);
		}
	}

	void Square(Surface* s, float x, float y)//not working
	{
		s->Line(15 + x, 30 + y, 360 + x, 30 + y, 0xffffff);//top
	}

	static Sprite theSprite(new Surface("assets/ball.png"), 1);
	static Sprite theSprite2(new Surface("assets/ball.png"), 1);
	int px = 0, py = 0;

	int bx1 = 0, bx2 = 750, by1 = 0, by2 = 200;

	int spriteY = 0, speed = 1;

	bool isGrounded = false;

	int xDiff = 360 - px;
	int yDiff = spriteY - 200;
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		int xDiff = 360 - px;
		int yDiff = spriteY - 200;
		
		spriteY += speed;
		speed += 1.0f;
		DrawBorders(bx1, bx2, spriteY, spriteY);

		Circle(screen, px + 25, spriteY + 25, 25);
		Circle(screen, 385, 225, 25);


		float xdist = 360 - px;
		float ydist = 200 - spriteY;
		float distance = sqrtf(xdist * xdist + ydist * ydist);
		if (distance < (25 + 25))
		{
			float fix = (25 + 25) - distance;
			float fraction = fix / distance;
			px -= fraction * xdist;
			spriteY -= fraction * ydist;

			//screen->Box //started making it and i had to go :D
		}

		//visualize
		theSprite.Draw(screen, px, (int)spriteY);
		theSprite2.Draw(screen, 360, 200);

		//input controls
		if (GetAsyncKeyState(VK_LEFT)) px -= 5;
		if (GetAsyncKeyState(VK_RIGHT)) px += 5;
		if (GetAsyncKeyState(VK_UP)) py--;
		if (GetAsyncKeyState(VK_DOWN)) py++;
		if (GetAsyncKeyState(VK_SPACE) && isGrounded == true) speed *= 1.25f;

		screen->Print("Left/Right arrow keys to move.", 20, 20, 0xffffff);
		screen->Print("Hold space to progressively gain bounce force", 20, 40, 0xffffff);

		//debug values
		printf("x: %d ", px);
		printf("y: %d \n", spriteY);
		printf("xDiff: %d ", xDiff);
		printf("yDiff: %d \n", yDiff);
	}

	void Game::DrawBorders(int xMin, int xMax, int yMin, int yMax)
	{
		if (px < (xMin))
		{
			px = xMin;

		}
		if (px > (xMax))
		{
			px = xMax;

		}
		if (spriteY > (512 - 50))
		{
			spriteY = 512 - 50;
			speed = -speed * 0.8f;
			isGrounded = true;
		}
		else
		{
			isGrounded = false;
		}
		if (spriteY < (0))
		{
			spriteY = 0;
		}
	}
};