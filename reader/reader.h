#ifndef READER_H
#define READER_H
#include "general_datataype.h"
//#include "compare_mask.h"
#include <iostream>
//#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class reader
{
public:

	reader(std::string &filePath);
	~reader();
	std::string getName();
	bool print();//test

private:

	std::string fPath;// полный путь с файлом
	std::ifstream fin;

};
#endif //READER_H