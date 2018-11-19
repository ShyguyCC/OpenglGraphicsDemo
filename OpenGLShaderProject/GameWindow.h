#pragma once


#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <fstream>  
#include <string>

#include "Singleton.h"
#include "ShaderManager.h"
#include "CameraClass.h"

class GameWindow
{


public:
	GameWindow();
	~GameWindow();
	void CreateWindowCiaran(int width, int lenth);
	void SettingAttributes();
	void ShutDownWindow();
	void SwapWindow();
	void SettingAttributesPTTwo(int Red_Size, int Greem_Size, int Blue_Size, int Alpha_Size, int Buffer_Size, int DoubleBuffer, bool CoreOrCompact, int Major_Ver, int Minor_Ver);
		
	void CreatingWindowAndAttributesWithFile();
	void TestFunction();


private:
	SDL_Window* window;
	SDL_GLContext context;
	std::string WindowName = "";
	int WindowWidth = 0;
	int WindowHight = 0;
	bool FullScreen = false;


private:

	int RedSizeInt = 0;
	int GreenSizeInt = 0;
	int BlueSizeInt = 0;
	int AlphaSizeInt = 0;
	int BufferSizeInt = 0;
	int DoubleBufferInt = 0;
	int MajorVerInt = 0;
	int MinorVerInt = 0;
	int WindowWidthInt = 0;
	int WindowHightInt = 0;







};

typedef Singleton<GameWindow> TheGameWindow;