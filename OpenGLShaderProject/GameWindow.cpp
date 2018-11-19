#include "GameWindow.h"



GameWindow::GameWindow()
{
}


GameWindow::~GameWindow()
{
}

/*
void GameWindow::CreateWindow(std::string windowname, int width, int lenth)



*/

//need to be able to toggle fullscreen
void GameWindow::CreateWindowCiaran(int width, int lenth) {
	/*

	below can be used if we want to use the whole of the sdl libary.
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cout << "sdl didnt work properly" << std::endl;
	}
	*/

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) == -1) {
		std::cout << "sdl didnt work properly" << std::endl;
	}



//	SettingAttributes();
//	here ya can change the attributes and they will be added in order, 
	SettingAttributesPTTwo(8, 8, 8, 8, 32, 1, false, 4, 4);


	window = SDL_CreateWindow("ciarans first window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, width, lenth, SDL_WINDOW_OPENGL);
	if (window == 0) {
		std::cout << "game window had failed to be made." << std::endl;
	}
	context = SDL_GL_CreateContext(window);
	if (context == 0) {
		std::cout << "opengl context couldnt be created." << std::endl;
	}
	//glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "glew didnt work" << std::endl;
	}


}


/*


int Red_Size, int Greem_Size, int Blue_Size, int Alpha_Size, int Buffer_Size, int DoubleBuffer, bool CoreOrCompact, int Major_Ver, Minor_Ver)


*/

// bool double buffer true if core, false for compatibility.
void GameWindow::SettingAttributesPTTwo(int Red_Size, int Green_Size, int Blue_Size, int Alpha_Size, int Buffer_Size, int DoubleBuffer, bool CoreOrCompact, int Major_Ver, int Minor_Ver) {
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, Red_Size);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, Green_Size);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, Blue_Size);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, Alpha_Size);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, Buffer_Size);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, DoubleBuffer);


	if (CoreOrCompact) {
		//set a core OpenGL context
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	}
	else if (!CoreOrCompact) {

		//set a compatibility OpenGL context
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, Major_Ver);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, Minor_Ver);



}

void GameWindow::CreatingWindowAndAttributesWithFile(){

	// -------------------------------------------------------------------------------------------------------------------
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) == -1) {
		std::cout << "sdl didnt work properly" << std::endl;
	}

	// -------------------------------------------------------------------------------------------------------------------


	std::string lineText = "";
	std::string finalString = "";
	std::string delimiter = "=";
	std::fstream myfile("Config.txt");
	int InfoInt = 0;
	if (!myfile.is_open()) {
		std::cout << "error opening the Config.txt folder, please create it." << std::endl;
	}
	//in this while loop, we search through the Config File, we fine key words like "RedSize" and use the token "=" to split the string up, we then
	//use that split up string to put the infomation in the correct place.
	while (!myfile.eof())
	{
		getline(myfile, lineText);
		std::string token = lineText.substr(0, lineText.find(delimiter));
//		std::cout << token << std::endl;
		if (token == "RedSize") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			InfoInt = std::stoi(lineText);
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, InfoInt);
		}
		else if (token == "GreenSize") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			InfoInt = std::stoi(lineText);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, InfoInt);
		}
		else if (token == "BlueSize") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			InfoInt = std::stoi(lineText);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, InfoInt);
		}
		else if (token == "AlphaSize") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			InfoInt = std::stoi(lineText);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, InfoInt);
		}
		else if (token == "BufferSize") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			InfoInt = std::stoi(lineText);
			SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, InfoInt);
		}
		else if (token == "DoubleBuffer") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			InfoInt = std::stoi(lineText);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, InfoInt);
		}
		else if (token == "ContextProfile") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			if (lineText == "Core") {
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			}
			else if (lineText == "Compatibility") {
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
			}

		}
		else if (token == "ContextMajorVer") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			InfoInt = std::stoi(lineText);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, InfoInt);
		}
		else if (token == "ContextMinorVer") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			InfoInt = std::stoi(lineText);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, InfoInt);
		}
		else if (token == "WindowName") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			WindowName = lineText;
		}
		else if (token == "WindowWidth") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			InfoInt = std::stoi(lineText);
			WindowWidth = InfoInt;
		}
		else if (token == "WindowLength") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			InfoInt = std::stoi(lineText);
			WindowHight = InfoInt;
		}
		else if (token == "FullScreen") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			if (lineText == "False") {
				FullScreen = false;
			}
			else if (lineText == "True") {
				FullScreen = true;
			}
		}

	}
	if (!FullScreen) {
		window = SDL_CreateWindow(WindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHight, SDL_WINDOW_OPENGL);
	}
	else if (FullScreen) {
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
		window = SDL_CreateWindow(WindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHight, flags);
	}


	// -------------------------------------------------------------------------------------------------------------------
	// set attributes above


	if (window == 0) {
		std::cout << "game window had failed to be made." << std::endl;
	}
	context = SDL_GL_CreateContext(window);
	if (context == 0) {
		std::cout << "opengl context couldnt be created." << std::endl;
	}
	//glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "glew didnt work" << std::endl;
	}
	// -------------------------------------------------------------------------------------------------------------------

	glEnable(GL_DEPTH_TEST);
	TheCamera::Instance()->projectionFunction(WindowHight, WindowWidth, true); // this sets up the camera as a 3d.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

// a testing function to test out things like file reading
void GameWindow::TestFunction(){


	std::string lineText = "";
	std::string finalString = "";
	std::string delimiter = "=";
	std::fstream myfile("Config.txt");
	if (!myfile.is_open()) {
		std::cout << "error opening the Config.txt folder, please create it." << std::endl;
	}

	while (!myfile.eof())
	{
		getline(myfile, lineText);

		std::string token = lineText.substr(0, lineText.find(delimiter));
		std::cout << token << std::endl;
		if (token == "RedSize") {
			lineText.erase(0, lineText.find(delimiter) + delimiter.length());
			std::cout << "string " <<lineText << std::endl;
			int testyint = std::stoi(lineText);
			std::cout << "Int " << testyint << std::endl;
			
		}
	}



}



void GameWindow::SettingAttributes() {

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//set a core OpenGL context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//set a compatibility OpenGL context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

}

void GameWindow::ShutDownWindow() {
	SDL_GL_DeleteContext(context);
	//free SDL game window
	SDL_DestroyWindow(window);
	//shut down all SDL subsystems
	SDL_Quit();

}

void GameWindow::SwapWindow() {
	SDL_GL_SwapWindow(window);
}

