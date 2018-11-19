#ifndef GAME_STATE_H
#define GAME_STATE_H

//following class was from karstens engine.

class GameState
{

public:

	GameState(GameState* state);
	virtual ~GameState() = 0 {}

public:

	bool& IsAlive();
	bool& IsActive();

public:

	virtual bool OnEnter() = 0;
	virtual bool Update() = 0;
	virtual bool Draw() = 0;
	virtual void OnExit() = 0;

protected:

	bool m_isAlive;
	bool m_isActive;
	GameState* m_previousState;

};

#endif