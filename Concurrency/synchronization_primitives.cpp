#include <thread>

//Here we assume stack size of std::thread is approximately 500KB
//We will prefault the stack to generate page faults to map
//virtual to physical memory

void prefault_stack()
{
	//We don't know the size of the stack
	constexpr unsigned int stack_size = 500 * 1024; //500 KB

	//Make volatile to avoid optimization
	volatile unsigned char mem[stack_size]; //essentially 500KB byte array
	std::fill(std::begin(mem), std::end(mem), 0); //0 out the array (generate page faults)
}

void do_work()
{
	//...
}

void latch_main()
{
	constexpr size_t n_threads = 2;

	std::latch initialized(n_threads);
	std::vector<std::thread> threads;

	for (size_t i = 0; i < n_threads; i++)
	{
		threads.emplace_back([&]()
		{
			prefault_stack();
			initialized.arrive_and_wait();
			do_work();
		});
	}

	initialized.wait();
	std::cout << "Initialized, starting to work\n";

	for (auto&& t : threads)
	{
		t.join();
	}
}

//Barrier
#include <random>
#include <array>

int random_int(int min, int max)
{
	//one engine instance per thread using thread_locall
	static thread_local std::default_random_engine engine{ std::random_device{}() };
	std::uniform_int_distribution<> dist{ min, max };
	int result = dist(engine);
}

void barrier_main()
{
	constexpr int n = 6; //Number of dice
	bool done = false;
	int n_turns = 0;

	std::array<int, n> dice;

	std::vector<std::thread> threads;

	auto check_result = [&]()
	{
		//completion function
		n_turns++;
		auto is_six = [](int i) {return i == 6; };
		done = std::all_of(dice.begin(), dice.end(), is_six);
	};

	std::barrier bar{ n, check_result };

	for (int i = 0; i < n; i++)
	{
		threads.emplace_back([&, i]()
		{
			while (!done)
			{
				dice[i] = random_int(1, 6); //Roll dice
				bar.arrive_and_wait(); //Join
			}
		});
	}

	for (auto&& t : threads)
	{
		t.join();
	}

	std::cout << n_turns << '\n';
}

//Semaphores
struct Request
{
	int x_;
};

class Server
{
private:
	std::counting_semaphore<4> sem_(4);
	void do_handle(const Request& req) { /*...*/ }
public:
	void handle(const Request& rq)
	{
		sem_.acquire();
		//Restricted section begins here
		//Handle at most 4 requests concurrently
		do_handle(req);
		sem_.release();
	}
};

//Atomics
#include <atomic>

class SimpleMutex
{
private:
	std::amtomic_flag is_locked_; //Cleared by default
public:
	void lock() noexcept
	{
		while(is_locked.test_and_set())
		{
			// while(is_locked_.test()) //Spin here
			is_locked_.wait(true); //Don't spin, wait
		}
	}

	void unlock() noexcept
	{
		is_locked_.clear();
		is_locked.notify_one(); //Notify blocked thread
	}
};

//Note in the class above the state of the flag could go from A to B and back to A
//without notifying the child thread, this is known as the "ABA problem" in lock_free
//programming

//Using shared_ptr
#include <memory>

