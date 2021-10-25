#include <string>
#include <vector>
#include <benchmark/benchmark.h>

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
	operator String() const&& { return a + b; }
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

auto operator==(ConcatProxy&& concat, String& str)
{
	return is_concat_equal(concat.a, concat.b, str.str_);
}

bool better_concat_equal()
{
	String A = "Cole";
	String B = "Porter";
	String C = "ColePorter";
	return (a + b) == c;
}

//rvalue modifier
bool operator==(ConcatProxy&& concat1, const String str)
{
	//...	
}

void using_rvalue_modifier()
{
	String concat = String{ "Cole" } + String{ "Porter" };
	bool is_cole_porter = concat == String{ "ColePorter" };
}

void assigning_to_proxy()
{
	String C = String{ "Marc" } + String{ "Chagall" };
	auto c = String{ "Marc" } + String{ "Chagall" }; //here auto makes c ConcatProxy
}

//Performance notes:
//When benchmarking with strings that are size 50 we can achieve a 40x speedup vs
//the normal std::string concatenation

template<typename T>
std::vector<T> create_strings(int n, size_t length)
{
	//Create m random strings of the specified length
	//...
}

template<typename T>
void bm_string_compare(benchmark::State& state)
{
	const int n = 10000;
	const int length = 10000;

	std::vector<T> a = create_strings<T>(n, length);
	std::vector<T> b = create_strings<T>(n, length);
	std::vector<T> c = create_strings<T>(n, length * 2);

	for (auto _ : state)
	{
		for (int i = 0; i < n; i++)
		{
			bool is_equal = a[i] + b[i] == c[i];
			benchmark::DoNotOptimize(is_equal);
		}
	}
}

BENCHMARK_TEMPLATE(bm_string_compare, std::string);
BENCHMARK_TEMPLATE(bm_string_compare, String);
BENCHMARK_MAIN();
