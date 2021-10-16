#include <iostream>
#include <functional>

class Image
{ /*...*/ };

Image load(std::string_view path);

class ScoreView
{
public:
	//Eager, requires loaded bonus image
	void display(const Image& bonus);

	//Lazy, only bonus image if necessary
	void display(std::function<Image()> bonus);
};

void lazy_vs_eager()
{
	ScoreView score;

	//Load default image lazily if needed
	std::function<Image> lazy = [] {return load("/images/stars.jpg"); };
	score.display(lazy);

	//Always load bonus image eagerly
	const Image eager = load("/images/stars.jpg"); //Image already loaded into memory
	score.display(eager);
}