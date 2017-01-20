
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>

using namespace::std;


// class to handle comparisions and additions of infinite weighted quantities, used to store distances
class Distance
{
private:

	int weight;
	bool infinite;

public:

	Distance()
	{
		weight = 0;
		infinite = true;
		bool relatedToStartNode = false;
	}

	void setWeight(int weight)
	{
		this->weight = weight;
		infinite = false;
	}

	string getWeight() const
	{
		if (infinite)
			return "inf";

		return to_string(weight);
	}

	bool isInfinite()
	{
		return infinite;
	}

	bool isZero()
	{
		if (!infinite && weight == 0)
			return true;

		return false;
	}

	// comparing infinite weights
	bool operator > (const Distance & e)
	{
		if (e.infinite)
			return false;
		else if (this->infinite)
			return true;
		else if (this->weight > e.weight)
			return true;

		return false;
	}

	// adding infinite weights
	Distance operator + (const Distance & e)
	{
		Distance d;

		if (this->infinite || e.infinite)
		{
			return d;
		}

		d.setWeight(e.weight + this->weight);
		return d;
	}
};
