//#include "chekDir.h"
#include <iostream>
#include <chrono>

#include <algorithm>

/* оределение "filesystem" для разных систем */
#if defined(_WIN32)// &&  __cplusplus >= 199711L // макрос "__cplusplus" в MSVS определен неправильно!
	#include <filesystem>
	namespace fs = std::filesystem;
#elif defined(__linux__) && __cplusplus >= 201402L// макрос "__cplusplus" в GCC определен таким образом, хотя должно быть 201703L
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#else
	#error "the compiler does not support the required level"
#endif
/* **************************************** */

//bool cmp(const fs::directory_iterator &a, const fs::directory_iterator &b) // Функция сравнения
bool cmp(const fs::directory_entry& a, const fs::directory_entry& b) // Функция сравнения
{
	//return fs::last_write_time((*a).path()) < fs::last_write_time((*b).path()) ? true : false;
	//return true;
	return a.last_write_time() < b.last_write_time() ? true : false;
}

// функтор
struct  directory_max_last_time
{
	void operator()(const fs::directory_entry& const _entry)
	{
		if(!entry.exists())
			entry = fs::directory_entry(_entry);
		try
		{
			if(_entry.last_write_time() > entry.last_write_time())
				entry = fs::directory_entry(_entry);// А вот так: entry = _entry нельзя!
		} catch (fs::filesystem_error err)
		{
			//entry = fs::directory_entry(_entry);
		}		
	}
	fs::directory_entry entry;
	//fs::filesystem_error err;
};


int main()
{
	//std::cout << "Version C++: " << __cplusplus << std::endl;


	std::string str = "E:\\temp";// E:\\1\\tmp\\21080101_g.og
	std::error_code er;
	fs::directory_entry mydir;


	for (const auto& entry : fs::directory_iterator(str, fs::directory_options(), er))
	{
		std::cout << entry.path().string() << " " << entry.is_directory() << " " << entry.is_regular_file() << std::endl;
	}
	std::cout << std::endl;

	// сделаем цикл класическим

	for (fs::directory_iterator my_dir = fs::begin(fs::directory_iterator(str));   my_dir != fs::end(fs::directory_iterator(str));   ++my_dir)
	{
		std::cout << my_dir->path().string() << " " << my_dir->is_directory() << " " << my_dir->is_regular_file() << std::endl;
	}




	fs::directory_iterator dir_begin = fs::begin(fs::directory_iterator(str));
	fs::directory_iterator dir_end  = fs::end(fs::directory_iterator(str));// этот "указатель" направлен на элемент за массивом!
	// ////fs::directory_iterator next_dir = ++dir_begin;
	// ////fs::directory_iterator dir_last_time = std::max_element<fs::directory_iterator&, bool>(dir_begin, dir_end, cmp);

	// fs::directory_iterator dir_last_time = std::max_element(dir_begin, dir_end, cmp);// это не работает! см.: https://en.cppreference.com/w/cpp/named_req/InputIterator
	// так как std::filesystem::directory_iterator это LegacyInputIterator !
	// A LegacyInputIterator is a LegacyIterator that can read from the pointed-to element.
	// LegacyInputIterators only guarantee validity for single pass algorithms: once a LegacyInputIterator i has been incremented, all copies of its previous value may be invalidated.
	// Попробуем соорудить необходимую конструкцию пр помощи std::for_each
	directory_max_last_time dir_last_time = std::for_each(dir_begin, dir_end, directory_max_last_time());

	std::cout << "directory with maximum lastwritetime: " << dir_last_time.entry.path().string() << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	//auto ftime = fs::last_write_time((*dir_begin).path());
	fs::file_time_type ftime = fs::last_write_time(dir_begin->path());
	std::cout << dir_begin->path().string() << " " << std::endl;
	//decltype(ftime)::clock::time_point();

	if (er)
	{
		std::cout << "error, directory not found!" << std::endl << std::endl;
	}



	//////////////////////////////////////////////////////////

	//fs::path p = "E:\\1\\tmp";
	//fs::directory_entry entry(p);
	// Здесь  еще нет обращения к файловой системе

	return 0;
}

