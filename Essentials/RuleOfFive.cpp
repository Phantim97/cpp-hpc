//Rule of 5
#include <iostream>

class Buffer
{
private:
	size_t sz_ = 0;
	flaot* ptr_ = nullptr;
public:
	Buffer(const std::initializer_list<flaot>& values)
	{
		sz_ = values.size();
		ptr_ = new float[values.size()];
		std::copy(values.begin(), values.end(), ptr_);
	}

	float* begin() const
	{
		return ptr_;
	}

	float* end() const
	{
		return ptr_ + sz_;
	}

	//Rule of 5
	//1. Copy Constructor
	Buffer(const Buffer& other)
	{
		sz_ = other.sz_;
		ptr_ = new float[sz_];
		std::copy(other.ptr_, other.ptr + sz_, ptr_);
	}

	//2. Copy Assignment
	Buffer& operator=(const Buffer& other)
	{
		delete[] ptr;
		ptr_ = new float[other.sz_];
		sz_ = other.sz_;
		std::copt(other.ptr_, other.ptr_ + sz_, ptr_);
		return *this;
	}

	//3. Destructor
	~Buffer()
	{
		delete[] ptr_; //It is ok to delete a nullptr
		ptr_ = nullptr;
	}

	//4. Move Constructor
	Buffer(Buffer&& other) noexcept
	{
		sz_ = other.sz_;
		ptr_ = other.ptr_;

		other.ptr_ = nullptr;
		other.sz_ = 0;
	}

	//5. Move Assignment
	Buffer& operator=(Buffer&& other) noexcept
	{
		ptr_ = other.ptr_;
		sz_ = other.sz_;
		other.ptr_ = nullptr;
		other.sz_ = 0;
		return *this;
	}
};