#include <range>
#include <string>
#include <vector>

void sample()
{
	std::vector<std::string> names = { "Ralph", "Lisa", "Homer", "Maggie", "Apu", "Bart" };

	std::ranges::sort(names, std::less<>{}, & std::string::size);
	//names is now Apu, Lisa, Bart, Ralph, Homer, Maggie

	//Find names with length 3
	auto x = std::ranges::find(names, 3, &std::string::size);
	//x poitns to Apu
}

//It is also possible to pass a lambda as a projection parameter, which can be handy
//in combining multiple properties in a projection
struct Player
{
	std::string name_ = "";
	int level_ = 0;
	float health_ = 0.0f;
};

void sample2()
{
	std::vector<Player> players = {
		{ "Aki", 1, 9.0f },
		{ "Nao", 2, 7.0f },
		{ "Rei", 2, 3.0f },
	};

	auto level_and_health = [](const Player& p) { return std::tie(p.level_, p.health_)};

	//Order players by level then health
	std::ranges::sort(players, std::greater<>{}, level_and_health);
}