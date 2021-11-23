#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <atomic>
//



void pause_thread(int n)
{
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout << "pause of " << n << " seconds ended\n";
}

void cycle_thread(int n, std::atomic<bool>& program_is_running)
{
	while (program_is_running)
	{
		std::cout << "pause of " << n << " seconds ended\n";
		std::this_thread::sleep_for(std::chrono::seconds(n));
	}
}

int main()
{
	std::atomic<bool> running{ true };

	std::thread t(cycle_thread, 1, std::ref(running));
	std::thread t2(cycle_thread, 2, std::ref(running));
	std::cout << "Done spawning threads.\n";

	std::this_thread::sleep_for(std::chrono::seconds(5));
	running = false;

	t.join();
	t2.join();

	std::cout << "Detaching cycle_thread threads and sleep 5 sec.\n";
	pause_thread(5);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
}