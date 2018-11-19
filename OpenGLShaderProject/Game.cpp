#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

void Game::Update() {

	//SDL_Event e;
	//SDL_PollEvent(&e);
/**/
	TheInput::Instance()->update(); // this is needed to run the update funciton that saves the key strokes that we do, then we can get the key state that has been pressed.

	const Uint8* keys = TheInput::Instance()->GetKeyStates();
	//Uint8 button = TheInput::Instance()->GetButtonStates();
	int button = TheInput::Instance()->GetbuttonStatesFinal();
	/*
	if (keys[SDL_SCANCODE_RIGHT])
	{
		movement = movement + 0.01;
		std::cout << "right is being pressed " << std::endl;
	}
	else if (keys[SDL_SCANCODE_LEFT]) {
		movement = movement - 0.01;
		std::cout << "left is being pressed " << std::endl;
	}
	else */if (keys[SDL_SCANCODE_Q]) { // this is horrible unreusable code unless q will always quit 
		GameRunning = true;
		std::cout << "q is being pressed " << std::endl;
	}
	else if (TheInput::Instance()->m_isXClicked) {
		GameRunning = true;
	}
	else if (button == SDL_CONTROLLER_BUTTON_A) {
		printf("A beening pressed\n");
	}
	else if (button == SDL_CONTROLLER_BUTTON_B) {
		printf("B beening pressed\n");
	}
	else if (button == SDL_CONTROLLER_BUTTON_X) {
		printf("X beening pressed\n");
	}
	else if (button == SDL_CONTROLLER_BUTTON_BACK) {
		GameRunning = true;
	}
}

bool Game::GameRunningFun() {

	return false;
}

void Game::ClearBuffer(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


//clear color sets background.

void Game::Draw() {

	/*
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	
	//top left color and vertex of quad
	glColor3f(1, 0, 0);
//	glVertex3f(movement + -0.5f, movement + 0.5f, movement + 0.0f);
	glVertex3f(movement + -0.5f, 0.5f, -1.0f);



	//top right color and vertex of quad
	glColor3f(0, 1, 0);
//	glVertex3f(movement + 0.5f, movement + 0.5f, movement + 0.0f);
	glVertex3f(movement + 0.5f, 0.5f, -1.0f);



	//bottom right color and vertex of quad
	glColor3f(0, 0, 1);
//	glVertex3f(movement + 0.5f, movement + -0.5f, movement + 0.0f);
	glVertex3f(movement + 0.5f, -0.5f, -1.0f);



	//bottom left color and vertex of quad
	glColor3f(0, 0, 1);
//	glVertex3f(movement + -0.5f, movement + -0.5f, movement + 0.0f);
	glVertex3f(movement + -0.5f, -0.5f, -1.0f);

	
	
	glEnd();
	*/


}

void Game::AddState(GameState* state)
{

	state->OnEnter();
	m_gameStates.push_front(state);

}

void Game::ChangeState(GameState* state)
{

	state->OnEnter();
	m_gameStates.push_back(state);

}


bool Game::Run(){

	GameState* state;

	while (!m_endGame) {
		state = m_gameStates.front();

		while (state->IsActive())
		{
//			TheGameWindow::Instance()->Update();
			ClearBuffer();
			TheInput::Instance()->update();
			state->Update();
			state->Draw();
			TheGameWindow::Instance()->SwapWindow();
		}
		if (!state->IsAlive())
		{
			RemoveState();
		}
		m_endGame = m_gameStates.empty();
	}



	return true;
}

bool Game::Initialize() {
	TheGameWindow::Instance()->CreatingWindowAndAttributesWithFile();

	TheShaderManager::Instance()->CreateProgram();
	TheShaderManager::Instance()->CreateShaders();
	TheShaderManager::Instance()->CompileShaders();		
	TheShaderManager::Instance()->AttachShaders();
	TheShaderManager::Instance()->LinkProgram();


	return true;
}

void Game::ShutDown(){
	TheGameWindow::Instance()->ShutDownWindow();
}


void Game::RemoveState() {
	m_gameStates.front()->OnExit();

//	delete m_gameStates.front(); // this broke, no clue why.
	m_gameStates.pop_front();
}