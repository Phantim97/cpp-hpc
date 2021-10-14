#include <iostream>

constexpr size_t hash_function(const char* str)
{
	size_t sum = 0;

	for (auto ptr = str; *ptr != '\0'; ptr++)
	{
		sum += *ptr;
	}

	return sum;
}

void test_hash()
{
	std::cout << hash_function("abc");
}

//Prehashed string
class PrehashedString
{
private:
	size_t hash_ = 0;
	size_t size_ = 0;
	const char* strptr_ = nullptr;

public:
	template<size_t N>
	constexpr PrehashedString(const char(&str)[N])
	{
		hash_ = hash_function(&str[0]);
		size_ = N - 1; //-1 to avoid null at end
		strptr_ = &str[0];
	}

	bool operator==(const PrehashedString& s) const
	{
		return size_ == s.size() && std:equal(c_str(), c_str() + size_, s.c_str());
	}

	bool operator!=(const PrehashedString& s) const
	{
		return !(*this == s);
	}

	constexpr size_t size() const
	{
		return size_;
	}

	constexpr size_t get_hash() const
	{
		return hash_;
	}

	constexpr const char* c_str() const
	{
		return strptr_;
	}
};

//overload std::hash
namespace std
{
	template<>
	struct hash<PrehashedString>
	{
		constexpr size_t operator(const PrehashedString& s) const
		{
			return s.get_hash();
		}
	};
}

auto test_prehashed_string()
{
	const auto& hash_fn = std::hash<PrehashedString>{};
	const auto& str = PrehashedString("abc");
	return hash_fn(str);
}