#include "Trip.h"

Trip::Trip(string a, string b) // vector<pair<Stop*, string>>, string b)
{
	tripID = a;
	direction_onroute = b;
}

Trip::~Trip()
{
}

//geters
string Trip::gettripID() const
{
	return tripID;
}

vector<pair<Stop*, pair<int, int>>> Trip::getstop_time_ontrip() const
{
	return stop_time_ontrip;
}

string Trip::getdirection() const
{
	return direction_onroute;
}

//seters
void Trip::settripID(string x)
{
	tripID = x;
}

void Trip::setstop_time_ontrip(Stop* x, int z, int k)
{
	int a = 0;

	for (unsigned int i = 0; i < stop_time_ontrip.size(); i++)
		if (stop_time_ontrip[i].first->getID() == x->getID() && stop_time_ontrip[i].second.first == z && stop_time_ontrip[i].second.second == k) a = 1;

	if (a == 0) stop_time_ontrip.push_back(make_pair(x, make_pair(z, k)));
}

void Trip::setdirection(string y)
{
	direction_onroute = y;
}