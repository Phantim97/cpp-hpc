struct Flower
{
	int height_ = 0;
	auto operator<=>(const Flower& f) const = default;
	bool operator==(const Flower& f) const = default;
};

void flower_driver()
{
	std::vector<Flower> garden = { {67}, {28}, {14} };
	//std::max_element() uses operator<()
	auto tallest = std::max_element(garden.begin(), garden.end());
	//std::find() uses operator==()
	auto perfect = *std::find(garden.begin(), garden.end(), Flower{ 28 });
}