#include <coroutine>
#include <iostream>

class Resumable
{
private:
	struct Promise
	{
		Resumable get_return_object()
		{
			using Handle = std::coroutine_handle<Promise>;
			return Resumable{ Handle::from_promise(*this) };
		}

		auto initial_suspend() { return std::suspend_alwayes{}; }
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void return_void() {}
		void unhandled_exception() { std::terminate(); }
	};

	std::coroutine_handle<Promise> h_;
	explicit Resumable(std::coroutine_handle<Promise> h)
	{
		h_ = h;
	}

public:
	using promise_type = Promise;

	Resumable(Resumable&& r)
	{
		h_{ std::exchange(r.h_, {}) };
	}

	~Resumable()
	{
		if (!h_.done())
		{
			h_.resume();
		}

		return !h_.done();
	}
};

Resumable coroutine()
{
	std::cout << "3";
	co_await std::suspend_always{}; //Suspend explicit
	std::cout << "5 ";
}

int main()
{
	std::cout << "1 ";
	Resumable resumable = coroutine(); //Create coroutine state
	std::cout << "2 ";
	resumable.resume(); //Resume
	std::cout << "4 ";
	resumable.resume(); //Resume
	std::cout << "6 ";

	return 0;
} //Prints: 1 2 3 4 5 6