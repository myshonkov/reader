#include "partPath.h"

//partPath::partPath(const std::string &part) : own_path(part), own_dir(), hand(nullptr)
partPath::partPath(const std::string& part) : own_dir(part), hand(nullptr)
{
	std::replace(own_dir.begin(), own_dir.end(), '\\', '/');
	// тут ничего не надо
}

partPath::partPath(const std::string &part, partPath &handler) : own_dir(part), hand(&handler)
{
	std::replace(own_dir.begin(), own_dir.end(), '\\', '/');
	// и тут ничего не надо
}

partPath::partPath(checkDir::type_dir chek_type, partPath &handler) : hand(&handler)
{
	// прочитаем директорий
	own_dir = frashFish(hand->getPath(), chek_type);
	//own_dir = frashFish(hand->getDir(), chek_type);
}


partPath::~partPath()
{
}

/* *** */

std::string partPath::getPath()
{
	//return hand ? hand->getPath() + own_path + own_dir : own_path;
	//std::string aaa = hand ? hand->getPath() + own_dir : own_dir;
	return hand ? hand->getPath() + "/" + own_dir : own_dir;
}

//std::string partPath::getDir()
//{
//	return own_dir;
//}

std::string partPath::frashFish(const std::string &path, checkDir::type_dir type)
{
	fs::directory_entry mydir;
	std::error_code er;
	std::map<fs::file_time_type, fs::directory_entry> sort_by_time;

	//
	for (const auto& entry : fs::directory_iterator(path, fs::directory_options(), er))
	{
		sort_by_time[fs::last_write_time(entry)] = entry;// работает для std::experimental::filesystem и std::filesystem
	}

	for (std::map<fs::file_time_type, fs::directory_entry>::reverse_iterator r_it = sort_by_time.rbegin(); r_it != sort_by_time.rend(); r_it++)
	{
		std::string name = r_it->second.path().filename().string();
		// сверка содержимого r_it с маской
		switch (type)
		{
		case checkDir::year:
			if (std::regex_match(name, std::regex("20\\d\\d", std::regex_constants::icase))) return name;
			break;
		case checkDir::month:
			if (std::regex_match(name, std::regex("[0-4][0-9]|5[0-2]", std::regex_constants::icase))) return name;
			break;
		case checkDir::day:
			if (std::regex_match(name, std::regex("[0-2][0-9]|3[0-1]", std::regex_constants::icase))) return name;
			break;
		default:
			break;
		}
	}
	return std::string("");
}