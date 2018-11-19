#pragma once
#include <iostream>
#include <glew.h>
#include <fstream>  
#include <string>
#include "Singleton.h"
class FileReadNWrite
{
public:
	FileReadNWrite();
	~FileReadNWrite();
	void ReadFile();
	void WriteFile();
	void ReadFileMK2(std::string file);
	void WriteFileMK2(std::string file, std::string OnToFile);


private:


};

typedef Singleton<FileReadNWrite> TheFileManager;
