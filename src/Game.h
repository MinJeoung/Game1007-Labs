#pragma once
#ifndef __GAME__
#define __GAME__

// Core Libraries
#include <iostream>
#include <string>
#include <vector>
#include "SceneState.h"

#include <SDL.h>

// Game Managers
#include "CollisionManager.h"

// Scenes
#include "StartScene.h"
#include "PlayScene.h"
#include "EndScene.h"

#include "Config.h"

#include "ImGuiWindowFrame.h"

// the class keyword allows us to define new types of variables, and the data and functionality inside the
// the data and functions inside the curly braces used to deffine this class are called members
class Game
{
public:
	// this is a function which returns a variable of type game.
	// for our purposes, this will be our way of accessing the singular game
	// access the game by writing the line Game::Instance().whateveryouwantfromit
	static Game& Instance() // static means this function belongs to the class and not any instance
	{
		static Game instance;
		return instance;
	}

	// member functions are functions whichc belong to a certain object of a certain type
	// we can access them by using the . operator on any variable to access its member functions and variables

	// simply set the isRunning variable to true
	void Init();
	bool Init(const char* title, int x, int y, int width, int height, bool fullscreen);

	// public life cycle functions
	void Render() const;
	void Update() const;
	void HandleEvents() const;
	void Clean() const;
	void Start();
	void Quit();

	// getter and setter functions
	[[nodiscard]] glm::vec2 GetMousePosition() const;

	void SetFrames(Uint32 frames);
	[[nodiscard]] Uint32 GetFrames() const;

	[[nodiscard]] float GetDeltaTime() const;
	void SetDeltaTime(float time);

	[[nodiscard]] bool IsRunning() const;
	void ChangeSceneState(SceneState new_state);

	[[nodiscard]] SDL_Window* GetWindow() const;

	// private Member variables. These are variables which this class has access to, not outside of class.
private:
	Game();
	~Game();

	// game properties
	bool m_bRunning;
	Uint32 m_frames;
	float m_deltaTime{};
	glm::vec2 m_mousePosition;

	// scene variables
	Scene* m_pCurrentScene;
	SceneState m_currentSceneState;

	// storage structures
	std::shared_ptr<SDL_Window> m_pWindow;
};


#endif /* defined (__GAME__) */

