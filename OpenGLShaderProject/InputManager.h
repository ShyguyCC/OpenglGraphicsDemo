#pragma once

//parts taking from karstens game engine.

#include <iostream>

#include <string>
#include <SDL.h>
#include <glm.hpp>
#include <SDL_events.h>
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
	int GetMouseClickState() { return m_MouseClickState; }

	void MouseUpdate(const glm::vec2& newMousePostion);
	glm::vec2 GetMouseVol() { return m_mouseVol; }

private:

	glm::vec2 m_mouseVol;

	int m_LeftStickState = 0; // 0 stop/middle,1 forward, 2 right, 3 down, 4 left.
	int m_RightStickState = 0;// 0 stop/middle, 1 forward, 2 right, 3 down, 4 left.
	int m_TriggerState = 0;
	int m_MouseClickState = 0;
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
