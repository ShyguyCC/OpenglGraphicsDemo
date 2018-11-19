#include "GameState.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults 
//------------------------------------------------------------------------------------------------------
GameState::GameState(GameState* state)
{

	m_isAlive = true;
	m_isActive = true;
	m_previousState = state;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns memory flag reference
//------------------------------------------------------------------------------------------------------
bool& GameState::IsAlive()
{

	return m_isAlive;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns active flag reference
//------------------------------------------------------------------------------------------------------
bool& GameState::IsActive()
{

	return m_isActive;

}