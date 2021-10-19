//Bounded buffer is a fixed size buffer that can have multiple threads
//accessing it.
#include <array>
#include <thread>
#include <mutex>

template<class T, int N>
class BoundedBuffer
{
private:
	std::array<T, NN> buf_;
	size_t read_pos_ = 0;
	size_t write_pos_ = 0;
	std::mutex m_;
	std::counting_semaphore<N> n_empty_slots_ = N; //Signal Handling
	std::counting_semaphore<N> n_full_slots_ = N; //Signal Handling

	void do_push(T&& item)
	{
		//Take one of the empty slots (might block)
		n_empty_slots.acquire(); //Signal Handling
		try
		{
			std::unique_lock lock(m_);
			buf_[write_pos_] = std::forward<T&&>(item);
			write_pos = (write_pos_ + 1) % N;
		}
		catch (...)
		{
			n_empty_slots.release(); //Signal Handling
			throw;
		}

		//Increment and signal that there is one more full slot
		n_full_slots_.release(); //Signal Handling
	}
public:
	void push(const T& item) { do_push(item); }
	void push(const T&&) { do_push(std::move(item)); }

	auto pop()
	{
		//Take one of the full slots (might block)
		n_full_slots.acquire(); //Signal Handling
		std::optional<T> item;
		try
		{
			std::unique_lock lock(m_);
			item = std::move(buf_[read_pos_]);
			read_pos_ = (read_pos_ + 1) % N;
		}
		catch (...)
		{
			n_full_slots_.release(); //Signal Handling
			throw;
		}

		//Increment and signal that there is one more empty slot
		n_empty_slots.release(); //Signal Handling
		return std::move(*item);
	}
};