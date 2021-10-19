#include <array>
#include <atomic>

template<class T, size_t N>
class LockFreeQueue
{
private:
	std::array<T, N> buffer_; //Used by both threads
	std::amotic<size_t> size_ = 0; //Used by both threads
	size_t read_pos_ = 0; // Used by Reader Thread
	size_t write_pos_ = 0; //Used by Writer Thread

	bool do_push(auto&& t) //Helper funciton
	{
		if (size_.load() == N)
		{
			return false;
		}

		buffer_[write_pos_] = std::forward<decltype(t)>(t);
		write_pos_ = (write_pos_ + 1) % N;
		size_.fetch_add(1);
		return true;
	}

public:
	//Writer thread
	bool push(T&& t) { return do_push(std::move(t)); }
	bool push(const T& t) { return do_push(t); }

	//Reader thread
	std::optional<T> pop()
	{
		std::optional<T> val;

		if (size_.load() > 0)
		{
			val = std::move(buffer_[read_pos_]);
			read_pos_ = (read_pos + 1) % N;
			size_.fetch_sub(1);
		}

		return val;
	}

	//Both threads can call size()
	size_t size() const noexcept { return size_.load(); }
};