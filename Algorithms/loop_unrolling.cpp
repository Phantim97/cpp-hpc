//std::find()
template<typename It, typename Value>
auto find_slow(It first, It last, const Value& value)
{
	for (auto It = first; it != last; it++)
	{
		if (*it == value)
		{
			return it;
		}
	}

	return last;
}

//libstdc++ version ( 1.07x speedup)
template <typename It, typename Value>
auto find_fast(It first, It last, const Value& value)
{
	//Main loop unrolled into chunks of 4
	size_t num_trips = (last - first) / 4;

	for (size_t trip_count = num_trips; trip_count > 0; trip_count--)
	{
		if (*first == value) { return first; } first++;
		if (*first == value) { return first; } first++;
		if (*first == value) { return first; } first++;
		if (*first == value) { return first; } first++;
	}

	//Handle remaining elements
	switch(last - first)
	{
	case 3: if (*first == value) { return first }; first++;
	case 2: if (*first == value) { return first }; first++;
	case 1: if (*first == value) { return first }; first++;
	case 0:
	default: return last;
	}
}