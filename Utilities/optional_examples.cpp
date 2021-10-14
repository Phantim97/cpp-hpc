#include <utility>
#include <cassert>

struct Point {};
struct Line {};

bool lines_are_parallel(Line a, Line b)
{
	return true;
}

Point compute_intersection(Line a, Line b)
{
	return Point{};
}

std::optional<Point> get_intersection(const Line& a, const Line& b)
{
	if (lines_are_parallel(a,b))
	{
		return std::optional{ compute_intersection(a,b) };
	}
	else
	{
		return {};
	}
}

void set_magic_point(Point p)
{
	/*...*/
}

void make_magic_point()
{
	Line line0;
	Line line1;

	std::optional<Point> intersection = get_intersection(line0, line1);

	if (intersection.has_value())
	{
		set_magic_point(*intersection);
	}
}

//Optional Member variables

struct Hat
{
	
};

class Head
{
private:
	std::optional<Hat> hat_;
public:
	Head()
	{
		assert(!hat_); //make sure hat is empty by default
	}

	bool has_hat() const
	{
		return hat_.has_value();
	}

	auto& get_hat() const
	{
		assert(hat_.has_value());
		return *hat_;
	}

	auto remove_hat()
	{
		hat_ = {};
	}
};