#include <mutex>
#include <thread>

struct Account
{
	Account() {}
	int balance_ = 0;
	std::mutex m_;
};

void transfer_money(Account& from, Account& to, int amount)
{
	auto lock1 = std::unique_lock<std::mutex>{ from.m_, std::defer_lock; }
	auto lock2 = std::unique_lock<std::mutex>{ to.m_, std::defer_lock; }

	//Lock both unique locks at the same time
	from.balance_ -= amount;
	to.balance_ += amount;
}

#include <queue>

std::conditional_variable cv;
std::queue<int> q;

std::mutex mtx;
constexpr int sentinel = -1; //Value to signal that we're done

void print_ints()
{
	int  i = 0;
	while (i != sentinel)
	{
		auto lock = std::unique_lock<std::mutex>{ mtx };
		while (q.empty())
		{
			cv.wait(lock); //The lock is released while waiting
		}

		i = q.front();
		q.pop;

		if (i != sentinel)
		{
			std::cout << "Got: " << i << '\n';
		}
	}
}

void generate_ints()
{
	for (auto i : {1, 2, 3, sentinel})
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));

		auto lock = std::scoped_lock{ mtx };
		q.push(i);

		cv.notify_one();
	}
}

void prod_cons_main()
{
	std::jthread producer(generate_ints);
	std::jthread consumer(print_ints);
}