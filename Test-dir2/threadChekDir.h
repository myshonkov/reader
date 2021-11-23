#pragma once
#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <atomic>

class threadChekDir
{
public:
	std::atomic<bool> running;
	threadChekDir();
	~threadChekDir();

	void cycle_thread(int n, std::atomic<bool>& program_is_running);

private:

};