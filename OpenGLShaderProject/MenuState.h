#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SDL.h>
#include "GameState.h"
#include "ShaderManager.h"
#include "QuadClass.h"
#include "BoxClass.h"
#include "CameraClass.h"
#include "GridClass.h"
#include "ShaderManager.h"
#include "LightClass.h"
#include "Model.h"
#include "TextClass.h"

class MenuState : public GameState
{

public:

	enum MenuOption { PLAY, QUIT };

public:

	MenuState(GameState* state);
	virtual ~MenuState() {}

public:

	void SetUpWalls();
	void SetUpObjects();
	virtual bool OnEnter();
	virtual bool Update();
	virtual bool Draw();
	virtual void OnExit();


private:

	bool DrawHelp;

	QuadClass WallOne;
	QuadClass WallTwo;
	QuadClass WallThree;
	QuadClass WallFour;
	QuadClass TheFloor;

	QuadClass FakeWaterFall;
	QuadClass CrossHatchText;
	QuadClass SpritTesting;
	QuadClass HelpingHUD;

	Model mod_Table;
	Model mod_ChairOne;
	Model mod_ChairTwo;
	Model mod_Gecko;
	Model mod_Fridge;

	BoxClass SkyBox;

	GridClass TheGrid;
	LightClass theLighter;
};

#endif