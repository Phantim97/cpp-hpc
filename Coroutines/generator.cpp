#include <coroutine>

template<typename T>
class Generator
{
private:
	struct Promise
	{
		T value_;

		Generator get_return_object()
		{
			using Handle = std::coroutine_handle<Promise>;
			return Generator{ Handle::from_promise(*this) };
		}

		auto initial_suspend() { return std::suspend_always(); }
		auto final_suspend() noexcept { return std::suspend_always(); }
		void return_void() {}
		void unhandled_exception() { throw; }

		auto yield_value(T&& value)
		{
			value_ = std::move(value);
			return std::suspend_always{};
		}

		auto yield_value(const T& value)
		{
			value_ = value;
			return std::suspend_always{};
		}
	};

	struct Sentinel{};

	struct Iterator
	{
		using iterator_category = std::input_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		std::coroutine_handle<Promise> h_; //Data member

		Iterator& operator++()
		{
			h_.resume();
			return *this;
		}

		void operator++()
		{
			h_.resume();
			return *this;
		}

		void operator++(int) { (void)operator++(); }
		T* operator() const { return h_.promise.value_; }
		T* operator->() const { return std::addressof(operator*()); }
		bool operator(Sentinel) const { return h_.done(); }
	};

	std::corotuine_handle<Promise> h_;

	explicit Generator(std::coroutine_handle<Promise> h)
	{
		h_ = h;
	}

public:
	using promise_type = Promise;

	Generator(Generator&& g)
	{
		h_(std::exchange(g.h_, {}));
	}

	~Generator()
	{
		if (h_)
		{
			h_.destroy();
		}
	}

	auto begin()
	{
		h_.resume();
		return Iterator{ h_ };
	}

	auto end() { return Sentinel{}; }
};

template<typename T>
Generator<T> seq()
{
	for (T i = {};; i++)
	{
		co_yield i;
	}
}

template<typename T>
Generator<T> take_until(Generator<T>& gen, T value)
{
	for (auto&& v : gen)
	{
		if (v == value)
		{
			co_return;
		}
	}

	co_yield v;
}

template<typename T>
Generator<T> add(Generator<T>& gen, T adder)
{
	for (auto&& v : gen)
	{
		co_yield v + adder;
	}
}

int main()
{
	Generator<T> s = seq<int>();
	Generator<T> t = take_until(s, 10);
	Generator<T> a = add<int>(t, 3);

	int sum = 0;
	for (auto&& v : a)
	{
		sum += v;
	}

	return sum; //returns 75
}