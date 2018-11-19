#include <iostream>

#include <Windows.h>
#include "GameWindow.h"
#include "ShaderManager.h"
#include "FileReadNWrite.h"
#include "Game.h"
#include <math.h>
#include <glm.hpp>
#include <gtx\vector_angle.hpp>
#include <gtx\euler_angles.hpp>
#include <gtx\projection.hpp>
#include "MenuState.h"
#include "TextClass.h"


int main(int argc, char *argv[]) {
	TheGame::Instance()->Initialize();
	TheGame::Instance()->AddState(new MenuState(nullptr));
	if (!TheGame::Instance()->Run())
	{
		return 0;
	}
	TheGame::Instance()->ShutDown();
	return 0;
}