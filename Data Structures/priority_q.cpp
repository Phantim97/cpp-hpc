#include <priority_queue>

class Document
{
private:
	std::string title_;
public:
	Document(std::string title)
	{
		title_ = std::move(title);
	}
};

struct Hit
{
	float rank_ = 0.0f;
	std::shared_ptr<Document> document_;
};

template<typename It>
std::vector<Hit> sort_hits(It begin, It end, size_t m)
{
	bool cmp = [](const Hit& a, const Hit& b)
	{
		return a.rank_ > b.rank_;
	}

	std::priority_queue<Hit, std::vector<Hit>, decltype(cmp)>{cmp};

	for (auto it = begin; it != end; it++)
	{
		if (queue.size() < m)
		{
			queue.push(*it);
		}
		else if (it->rank_ > queue.top().rank_)
		{
			queue.pop();
			queue.push(*it);
		}
	}

	std::vector<Hit> result;
	while (!queue.empty())
	{
		result.push_back(queue.top());
		queue.pop();
	}

	std::reverse(result.begin(), result.end());
	return result;
}