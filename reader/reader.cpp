#include "reader.h"

reader::reader(std::string &filePath) : fPath(filePath)
{
	std::replace(fPath.begin(), fPath.end(), '\\', '/');
}

reader::~reader()
{
	//fin.close();
}

std::string reader::getName()
{
	int pos = fPath.rfind('/');
	if (pos == std::string::npos) return fPath;
	return std::string(fPath, ++pos);
}

///
bool reader::print()
{
	//fin.open(fPath, std::ios::in);
	fin.open(fPath);
	if(!fin.is_open())
	{
		std::cout << "File not found" << std::endl;
		return false;
	}

	// тестовое чтение из файла //
	char buf[5];
	fin.getline(buf, 3);
	std::cout << buf << std::endl;
	fin.close();
	// ************************ //

	return true;
}

