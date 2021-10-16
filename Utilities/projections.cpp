#include <utility>

struct Player
{
	std::string name_;
	int level_ = 0;
	int score_ = 0;
};

std::vector<Player> players;

auto cmp = [](const Player& lhs, const Player& rhs)
{
	if (lhs.level_ == rhs.level_)
	{
		return lhs.score_ < rhs.score_;
	}
	else
	{
		return lhs.level_ < rhs.level_;
	}
};

std::sort(players.begin(), players.end(), cmp);

//better version (Projection)
auto cmp2 = [](const Player& lhs, const Player& rhs)
{
	auto p1 = std::tie(lhs.level_, lhs.score_);
	auto p2 = std::tie(rhs.level_, rhs.score_);

	return p1 < p2;
}

std::ranges::sort(players, std::less, [](const Player& p) {return std::tie(p.level_, p.score_)});