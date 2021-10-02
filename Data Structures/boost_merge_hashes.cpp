#include <Boost/functional/hash.hpp>

std::function<bool> person_eq =  [](const Person& lhs, const Person& rhs)
{
	return lhs.name() == rhs.name() && lhs.age() == rhs.age();
}

//Boost functionality to combine hashes
std::function<size_t> person_hash = [](const Person& person)
{
	size_t seed = 0;
	boost::hash_combine(seed, person.name());
	boost::hash_combine(seed, person.age());
	return seed;
}