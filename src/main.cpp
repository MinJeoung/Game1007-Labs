// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>

#include "Game.h"

constexpr float FPS = 60.0f;
constexpr float DELAY_TIME = 1000.0f / FPS;

/**
 * \brief Program Entry Point
 */
int main(int argc, char* args[])
{
	Uint32 frames = 0;

	// show and position the application console
	AllocConsole();
	auto console = freopen("CON", "w", stdout);
	const auto window_handle = GetConsoleWindow();
	MoveWindow(window_handle, 100, 700, 800, 200, TRUE);

	// Display Main SDL Window
	Game::Instance().Init("SDL_Engine v0.29", 100, 100, 800, 600, false);

	// Main Game Loop
	while (Game::Instance().IsRunning())
	{
		// time at the start of the frame, in ms
		const auto frame_start = static_cast<float>(SDL_GetTicks());

		Game::Instance().HandleEvents(); // take player input
		Game::Instance().Update(); // update game state (presumably based on other conditions and input)
		Game::Instance().Render(); // draw to screen to show new game state to player

		// figure out how long we need to wait for the next frame timing
		// current time - time at the start of frame = time elapsed during this frame
		if (const float frame_time = static_cast<float>(SDL_GetTicks()) - frame_start;
			frame_time < DELAY_TIME) // if time passeed is less than the time we have for each frame...
		{
			// do nothing for awhile until its time for the next frame
				SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
		}

		// delta time. Time elapsed this frame, in seconds
		const float delta_time = (static_cast<float>(SDL_GetTicks()) - frame_start) / 1000.0f;
		Game::Instance().SetDeltaTime(delta_time);

		frames++; // increments and how many frames have passed since the start of game
		Game::Instance().SetFrames(frames);

	}

	Game::Instance().Clean();
	return 0;
}

