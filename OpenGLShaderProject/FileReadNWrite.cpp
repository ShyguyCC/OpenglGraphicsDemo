#include "FileReadNWrite.h"



FileReadNWrite::FileReadNWrite()
{
}


FileReadNWrite::~FileReadNWrite()
{
}

//this is hard coded, a softer code will be in mk 2 that will take ina  string that will act at the file name.
void FileReadNWrite::ReadFile(){
	std::fstream file;
	std::string lineText = "";
	std::string finalString = "";

	std::fstream inFile;
	inFile.open("Config.txt");
	if (!inFile) {
		std::cout << "Unable to open file datafile.txt" << std::endl;
	}
	while (!inFile.eof()) {
		getline(inFile, lineText);
		std::cout << "this is the infile line text : " << lineText << std::endl;
	}
}

void FileReadNWrite::WriteFile(){
	std::ofstream outfile("Info.txt");
	outfile << "GL Render: " << (const char*)(glGetString(GL_RENDERER)) << std::endl;
	//display the current OpenGL version and mode set 
	outfile <<  "GL Version: " << (const char*)(glGetString(GL_VERSION)) << std::endl;
	//display which GLSL version is supported by the graphics card 
	outfile << "GL Shading Language Version: " << (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
	outfile << "Please use the infomation above to choice if you would like features like: Full Screen, high resolution and many others." << std::endl;
	outfile.close();
}

//these functions takes in a string thats the file full name.
void FileReadNWrite::ReadFileMK2(std::string file){
	std::ofstream inFile;
	inFile.open("..\\Config.txt");

}
// pass in a file name and what you want writting onto the file.
void FileReadNWrite::WriteFileMK2(std::string file, std::string OnToFile){
	std::ofstream outfile(file);
	outfile << OnToFile << std::endl;
	outfile.close();
}
