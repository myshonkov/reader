#include "partPath.h"

partPath::partPath(const std::string& part) : own_dir(part), hand(nullptr)
{
	std::replace(own_dir.begin(), own_dir.end(), '\\', '/');// для win
	// тут ничего не надо
}

partPath::partPath(const std::string &part, partPath &handler) : own_dir(part), hand(&handler)
{
	std::replace(own_dir.begin(), own_dir.end(), '\\', '/');// для win
	// и тут ничего не надо
}

partPath::partPath(checkDir::type_dir check_type, partPath &handler) : check(check_type), hand(&handler)
{
	// прочитаем директорий
	//own_dir = frashFish(hand->getPath(), check_type);
	// создать поток
	reading();
}

partPath::~partPath()
{
}

/* *** */

std::string partPath::getPath()
{
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

/*
void partPath::cycleThread(std::atomic<bool>& program_is_running)
{
	std::string found;
	while (program_is_running)
	{
		found = frashFish(hand->getPath(), check);
		if (found != own_dir) own_dir = found;
		/// !!! TEST !!! ///
		std::cout << hand->getPath() << "/" << own_dir << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		///////////////////
	}
}
*/
partPath* partPath::getHand()
{
	return hand;
}
checkDir::type_dir partPath::getCheck()
{
	return check;
}
void partPath::setDir(std::string str)
{
	if (str != own_dir) own_dir = str;
	/// !!! TEST !!! ///
	std::cout << hand->getPath() << "/" << own_dir << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	///////////////////
}

void cycleThread(std::atomic<bool>& program_is_running, partPath& pp)
{
	std::string found;
	while (program_is_running)
	{
		found = pp.frashFish(pp.getHand()->getPath(), pp.getCheck());
		//if (found != own_dir) own_dir = found;
		pp.setDir(found);
	}
}

void partPath::tcloser(std::thread* t)
{
	
	t->join();
	delete t;
	//running = false;
};

void partPath::reading()
{
	running = true;
	//t = new std::thread(cycleThread, std::ref(running), std::ref(*this));
	std::unique_ptr<std::thread, tcloser> t(std::thread(cycleThread, std::ref(running), std::ref(*this)));
}

