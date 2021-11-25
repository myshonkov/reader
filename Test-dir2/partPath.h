#pragma once

// ��� �����, �������!
#include <iostream>
//

#include <string>
#include <map>
#include <regex>
// ��� ������
#include <thread> 
#include <chrono>
#include <atomic>
#include <memory>
//
#include "bricksAndMortar.h"

//--------------------------------------------------------------------------//
//--- ���������� "filesystem" ��� ������ ������
#if defined(_WIN32)// &&  __cplusplus >= 199711L // ������ "__cplusplus" � MSVS ��������� �����������!
#include <filesystem>
namespace fs = std::filesystem;
#elif defined(__linux__) && __cplusplus >= 201402L// ������ "__cplusplus" � GCC ��������� ����� �������, ���� ������ ���� 201703L
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "the compiler does not support the required level"
#endif
//--------------------------------------------------------------------------//

class partPath
{
public:
	partPath(const std::string&);				// ��� ������ ����, ���������� ���� ������ �����������, ���� ���� ����� ��������� � ��������� ����������
	//partPath(checkDir::type_dir);				// ��� ���� ������ ����, ������. �� ����� � ������� (��������) ���������� ��������. ��������! ����� ����������� ���� �� ��������. �� ����� ��� �������������
	partPath(const std::string&, partPath&);	// ���, ��� �� � �������� ����. ���������� "string" �������� � ��������� ����������. �� ������ ���� ����� ���������� ��� ������ �
												// "partPath" + "own_path". ��� "own_path" ������������� ����� ��� ��������� � ��������
	partPath(checkDir::type_dir, partPath&);	// ��� �������� ��� ����� ���� ��� ������� ���������� �������� ����� "checkDir::type_dir", ���� ��� ���������� �������� ������������ ��������
	std::string frashFish(const std::string &, checkDir::type_dir);

	~partPath();

	std::string getPath();
	//std::string getDir();
	//std::string getPath(partPath*);
	partPath* getHand();
	checkDir::type_dir getCheck();
	//std::string getDir();
	void setDir(std::string);


private:
	// �������� ���� ������ ���� � ������������
	//std::string own_path;
	std::string own_dir;
	partPath* hand;
	checkDir::type_dir check;

	std::atomic<bool> running;
	std::thread* t;
	void cycleThread(std::atomic<bool>& program_is_running);
	void reading();
	void tcloser(std::thread*);
};
