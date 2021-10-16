#include <string>

//normal way
bool concat_normal()
{
	std::string a = "Cole";
	std::string b = "Porter";
	std::string c = "ColePorter";

	return (a + b) == c; //a + b allocates another string
}

//Performantly better, syntactically worse
bool is_concat_equal(const std::string& a, const std::string& b, std::string& c)
{
	return a.size() + b.size() == c.size() && std::equal(a.begin(), a.end(), c.begin())
		&& std::equal(b.begin(), b.end(), c.begin() + a.size());
}

struct ConcatProxy
{
	const std::string& a;
	const std::string& b;
};

class String
{
public:
	String() = default;
	String(std::string str)
	{
		str_ = std::move(str);
	}
	std::string str_;
};

auto operator+(const String& a, const String& b)
{
	return ConcatProxy{ a.str_, b.str_ };
}

auto operator==(ConcatProxy&& concat, const String& str)
{
	return is_concat_equal(concat.a, concat., str.str_);
}

bool better_concat_equal()
{
	String A = "Cole";
	String B = "Porter";
	String C = "ColePorter";
	return (a + b) == c;
}