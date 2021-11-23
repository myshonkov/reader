#include "threadChekDir.h"

threadChekDir::threadChekDir()
{
	//std::this_thread::sleep_for(std::chrono::seconds(1));
}

threadChekDir::~threadChekDir()
{

}

void threadChekDir::cycle_thread(int n, std::atomic<bool>& program_is_running)
{
	while (program_is_running)
	{
		std::this_thread::sleep_for(std::chrono::seconds(n));
	}
}