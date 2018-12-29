#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"

struct Athlete
{
	std::string name;
	double height;
	double weight;
};

Athlete Tigress = { "Master Tigress", 220.5, 100.50 };
Athlete Monkey = { "Master Monkey ", 150.8, 78.42 };
Athlete Mantis = { "Master Mantis", 18.5, 0.85 };
Athlete Crane = { "Master Crane", 180.0, 50.20 };
Athlete Viper = { "Master Viper", 250.5, 42.05 };
Athlete Po = { "Dragon Warrior", 187.96, 118.00 };

std::vector<Athlete> emptyAthleteVector;
std::vector<Athlete> athletes = { Tigress, Monkey, Mantis, Crane, Viper, Po };


bool LessWeight(Athlete const & lhs, Athlete const & rhs)
{
	return (lhs.weight < rhs.weight);
}


bool LessHeight(Athlete const & lhs, Athlete const & rhs)
{
	return (lhs.height < rhs.height);
}


void IsAthleteEqual(Athlete const & lhs, Athlete const & rhs)
{
	BOOST_CHECK((lhs.name == rhs.name) && (lhs.height == rhs.height) && (lhs.weight == rhs.weight));
}


BOOST_AUTO_TEST_SUITE(findmaxEx_function_)

	BOOST_AUTO_TEST_CASE(cannot_find_expected_item_in_empty_array)
	{
		{
			Athlete weightestAthlete = Tigress;
			BOOST_CHECK(!FindMaxEx(emptyAthleteVector, weightestAthlete, LessWeight));
			IsAthleteEqual(weightestAthlete, Tigress);
		}
		{
			Athlete heightestAthlete = Tigress;
			BOOST_CHECK(!FindMaxEx(emptyAthleteVector, heightestAthlete, LessHeight));
			IsAthleteEqual(heightestAthlete, Tigress);
		}
	}
	BOOST_AUTO_TEST_CASE(return_max_element_in_nonempty_vector)
	{
		{
			Athlete weightestAthlete = Tigress;
			BOOST_CHECK(FindMaxEx(athletes, weightestAthlete, LessWeight));
			IsAthleteEqual(weightestAthlete, Po);
		}
		{
			Athlete heightestAthlete = Tigress;
			BOOST_CHECK(FindMaxEx(athletes, heightestAthlete, LessHeight));
			IsAthleteEqual(heightestAthlete, Viper);
		}
	}

BOOST_AUTO_TEST_SUITE_END()