#include "InputManager.h"



InputManager::InputManager()
{
	m_keyStates;

	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			m_controller = SDL_GameControllerOpen(i);
			break;
		}
	}
}


InputManager::~InputManager()
{
}

bool InputManager::IsKeyPressed() {
	return m_isKeyPressed;
}

const Uint8* InputManager::GetKeyStates()
{

	return m_keyStates;

}
Uint8 InputManager::GetButtonStates()
{

	return m_buttonStates;

}

void InputManager::update() {


//	std::cout << SDL_MouseButtonEvent << "  this is mouse state update " << std::endl;
	



	buttonReseter();
	SDL_Event events;


	if (!SDL_PollEvent(&events))
	{
		SDL_Delay(1);
	}
	else
	{
		SDL_PushEvent(&events);
	}
	m_isXClicked = false;
	m_keyStates = SDL_GetKeyboardState(0);
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
			case SDL_QUIT:
			{
				m_isXClicked = true;
				break;
			}
			case SDL_KEYUP:
			{
				m_isKeyPressed = false;
				break;
			}
			case SDL_KEYDOWN:
			{
				m_isKeyPressed = true;
				break;
			}
			case SDL_CONTROLLERBUTTONDOWN: {
				buttonPressedFinal = events.cbutton.button;
				break;
			}
			case SDL_CONTROLLERBUTTONUP:
			{
				buttonPressedFinal = -1;
				m_isButtonPressed = false;
				break;
			}
			case SDL_CONTROLLERAXISMOTION: {
				m_LeftStickState = 0;
				m_RightStickState = 0;
				m_TriggerState = 0;
				
				if (events.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
					m_TriggerState = 1;
				}else if (events.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
					m_TriggerState = 2;
				}

				if (events.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX || events.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
					if (events.caxis.axis == 0) {
						if (events.caxis.value < -stickDeadZone) {
							m_LeftStickState = 4;
						}
						else if (events.caxis.value > stickDeadZone) {
							m_LeftStickState = 2;
						}
					}
					else if (events.caxis.axis == 1) {
						if (events.caxis.value < -stickDeadZone) {
							m_LeftStickState = 1;
						}
						else if (events.caxis.value > stickDeadZone) {
							m_LeftStickState = 3;
						}
					}
				}else if (events.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX || events.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
					if (events.caxis.axis == 2) {
						if (events.caxis.value < -stickDeadZone) {
							m_RightStickState = 4;
						}
						else if (events.caxis.value > stickDeadZone) {
							m_RightStickState = 2;
						}
					}else if (events.caxis.axis == 3) {
						if (events.caxis.value < -stickDeadZone) {
							m_RightStickState = 1;
						}
						else if (events.caxis.value > stickDeadZone) {
							m_RightStickState = 3;
						}
					}
				}
			}
			case SDL_MOUSEBUTTONDOWN: {
				if (events.button.button == SDL_BUTTON_LEFT) {
					m_MouseClickState = 1;
				}else if (events.button.button == SDL_BUTTON_RIGHT) {
					m_MouseClickState = 2;
				}
			}
			case SDL_MOUSEMOTION: {

				m_mouseVol.x = events.motion.xrel;
				m_mouseVol.y = events.motion.yrel;
			}
		}
	}
	std::cout << m_mouseVol.x << " = Mouse x. " << m_mouseVol.y << " = mouse y." << std::endl;
}

void InputManager::buttonReseter() {
	buttonA = false;
	buttonB = false;

	m_mouseVol.x = 0;
	m_mouseVol.y = 0;
}

int InputManager::GetbuttonStatesTwo() {

	if (buttonA) {
		return SDL_CONTROLLER_BUTTON_A;
	}
	if (buttonB) {
		return SDL_CONTROLLER_BUTTON_B;
	}


	return -1;
}

void InputManager::MouseUpdate(const glm::vec2 & newMousePostion) {

}
