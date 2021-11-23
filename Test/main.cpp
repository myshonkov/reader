#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <atomic>
//
#include <future>


void pause_thread(int n)
{
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout << "pause of " << n << " seconds ended\n";
}

void cycle_thread(int n, std::future<int> mystop)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	bool aaa = mystop.valid();

	while (mystop.);
	{	
		std::cout << "pause of " << n << " seconds ended\n";
		std::this_thread::sleep_for(std::chrono::seconds(n));
	}
}

int main()
{
	std::promise<int> stopping_promise;
	std::future<int> stopping_future = stopping_promise.get_future();
	//std::future<int> stopping_future;
	//std::thread t(cycle_thread, 1, std::move(stopping_future));
	//std::thread t(cycle_thread, 1, stopping_future);

	bool aaa = stopping_future.valid();
	std::thread t(cycle_thread, 1, std::move(stopping_future));
	bool bbb = stopping_future.valid();
	stopping_promise.set_value(10);

	std::this_thread::sleep_for(std::chrono::seconds(5));
	//stopping_future = stopping_promise.get_future();
	stopping_promise.set_value(1);

	t.join();
	std::cout << "Detaching cycle_thread threads and sleep 5 sec.\n";
	//pause_thread(5);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
}