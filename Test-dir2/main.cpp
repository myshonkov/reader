// ������� ������ 09.11.2021
// v01

#include <iostream>
#include <chrono>
#include <map>
#include <algorithm>

// ��� ����� ////////////////
#include "partPath.h"
#include "bricksAndMortar.h"
/////////////////////////////

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

//--------------------------------------------------------------------------//
//--- helper function convert timepoint to usable timestamp
//template <typename TP>
//std::time_t to_time_t(TP tp) {
//	auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp - TP::clock::now() + std::chrono::system_clock::now());
//	return std::chrono::system_clock::to_time_t(sctp);
//}

//--------------------------------------------------------------------------//

int main()
{
/*
	std::string str = "E:\\temp";

	fs::directory_entry mydir;
	std::error_code er;
	std::map<fs::file_time_type, fs::directory_entry> sort_by_time;

	for (const auto &entry : fs::directory_iterator(str, fs::directory_options(), er))
	{
		sort_by_time[fs::last_write_time(entry)] = entry;// �������� ��� std::experimental::filesystem � std::filesystem
	}

	std::cout << sort_by_time.crbegin()->second.path().string() << std::endl;// ������� ��������� �� ���� ������� �� ������� "sort_by_time"
*/

	std::string str = "E:\\temp\\test1";

	partPath pp1(str);
	//partPath pp2(checkDir::year, pp1);
	//partPath pp2(checkDir::month, pp1);
	partPath pp2(checkDir::year, pp1);
	partPath pp3("aaa", pp2);
	partPath pp4(checkDir::month, pp3);

	std::cout << pp4.getPath() << std::endl;
}