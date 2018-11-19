#pragma once

#include <iostream>
#include <glew.h>
#include <SDL.h>
#include <fstream>
#include <string>
#include <deque>
#include "Singleton.h"
#include "InputManager.h"
#include "GameState.h"
#include "GameWindow.h"
#include "ShaderManager.h"


class Game
{

public:
	Game();
	Game(const Game&);
	Game& operator=(Game&);
	~Game();


	bool Initialize();
	void AddState(GameState* state);
	void ChangeState(GameState* state);





	void Update();
	void Draw();
	bool GameRunningFun();
	bool GameRunning = false;
	void ClearBuffer();


	bool Run();
	void ShutDown();




private:

	void RemoveState();
	float movement = 0;
	std::deque<GameState*> m_gameStates;

private:

	bool m_endGame;

	GLuint m_fragmentShaderID;
	GLuint m_vertexShaderID;
	GLuint m_shaderProgramID;
	GLfloat VBODataStore[];






};

typedef Singleton<Game> TheGame;