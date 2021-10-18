#include <thread>
#include <iostream>
#include <chrono>
#include <ctime>

void print(std::stop_token stoken)
{
	while(!stoken.stop_requested())
	{
		std::cout << std::this_thread::get_id();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void main()
{
	std::jthread joinable_thread = std::jthread(print);

	std::cout << "Main: Goes to sleep\n";
	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::cout << "Main: Request jthread to stop\n";
	joinable_thread.request_stop();
}