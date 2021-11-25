#pragma once

// ДЛЯ ТЕСТА, удалить!
#include <iostream>
//

#include <string>
#include <map>
#include <regex>
// для потока
#include <thread> 
#include <chrono>
#include <atomic>
#include <memory>
//
#include "bricksAndMortar.h"

//--------------------------------------------------------------------------//
//--- оределение "filesystem" для разных систем
#if defined(_WIN32)// &&  __cplusplus >= 199711L // макрос "__cplusplus" в MSVS определен неправильно!
#include <filesystem>
namespace fs = std::filesystem;
#elif defined(__linux__) && __cplusplus >= 201402L// макрос "__cplusplus" в GCC определен таким образом, хотя должно быть 201703L
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "the compiler does not support the required level"
#endif
//--------------------------------------------------------------------------//

class partPath
{
public:
	partPath(const std::string&);				// это начало пути, полученный путь всегда статический, этот путь нужно сохранить с приватной переменной
	//partPath(checkDir::type_dir);				// это тоже начало пути, корень. Но папки в текущей (корневой) директории меняются. ВНИМАНИЕ! Такая конструкция вряд ли возможна. Не будем это реализовывать
	partPath(const std::string&, partPath&);	// это, что то в середине пути. Полученный "string" сохраним в приватной переменной. Но полный путь будем возвращать как запрос к
												// "partPath" + "own_path". Для "own_path" предусмотреть метод для изменения её значения
	partPath(checkDir::type_dir, partPath&);	// это середина или конец пути где текущий директорий определён типом "checkDir::type_dir", этот тип определяет характер динамической проверки
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
	// выяснить свой полный путь в конструкторе
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
