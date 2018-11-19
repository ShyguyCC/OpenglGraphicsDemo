#pragma once

//parts taking from karstens game engine.

#include <string>
#include <SDL.h>
#include "Singleton.h"

class InputManager
{
public:
	InputManager();
	~InputManager();



	const Uint8* GetKeyStates();
	Uint8 GetButtonStates();
	bool IsKeyPressed();

	std::string GetInput() { return m_input; }

	void update();


	bool m_isXClicked;

	int GetbuttonStatesTwo();
	void buttonReseter();
	int GetbuttonStatesFinal() { return buttonPressedFinal; };
	int GetLeftStickState() { return m_LeftStickState; };
	int GetRightStickState() { return m_RightStickState; };
	int GetTriggerState() { return m_TriggerState; }



private:

	int m_LeftStickState = 0; // 0 stop/middle,1 forward, 2 right, 3 down, 4 left.
	int m_RightStickState = 0;// 0 stop/middle, 1 forward, 2 right, 3 down, 4 left.
	int m_TriggerState = 0;
	const Uint8* m_keyStates;
	bool m_isKeyPressed;
	std::string m_input;


	bool m_isButtonPressed;
	Uint8 m_buttonStates;
	const Uint8* m_buttonStatesTwo;

	int controlstate;
	SDL_GameController *m_controller = nullptr;
	SDL_GameControllerButton button;

	bool buttonA;
	bool buttonB;

	int buttonPressedFinal = -1;
	const int stickDeadZone = 8000;













};


typedef Singleton<InputManager> TheInput;
