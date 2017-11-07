#include "StopClass.h"

//constructor
Stop::Stop(int x, string a, double b, double c) // vector<Stop*>, vector<Route*>)
{
	ID = x;
	stopID = a;
	stopLat = b;
	stopLon = c;
}

//default constructor
Stop::~Stop()
{
}

//geters
int Stop::getID() const
{
	return ID;
}

string Stop::getstopID() const
{
	return stopID;
}

double Stop::getlat() const
{
	return stopLat;
}

double Stop::getlon() const
{
	return stopLon;
}

vector<pair<Stop*, int>> Stop::getConnectedStop() const
{
	return connected_stops;
}

vector<Route*> Stop::getConnectedroute() const
{
	return connected_routes;
}

vector < pair<Stop*, Route*>> Stop::getconnected_routes_stops() const
{
	return connected_routes_stops;
}

int Stop::getTransfer() const
{
	return transfer_stop;
}

//seters
void Stop::setConnectedStop(Stop* x, int y)
{
	int a = 0;

	for (unsigned int i = 0; i < connected_stops.size(); i++)
		if (connected_stops[i].first->getID() == x->getID()) a = 1;
	if (a == 0) connected_stops.push_back(make_pair(x, y));
}


void Stop::setConnectedRoutes(Route* y)
{
	int a = 0;

	for (unsigned int i = 0; i < connected_routes.size(); i++)
		if (connected_routes[i]->getrouteID() == y->getrouteID()) a = 1;
	if (a == 0) connected_routes.push_back(y);
}

void Stop::setconnectedroutesstops(Stop* x, Route* y)
{
	int a = 0;
	for (unsigned int i = 0; i < connected_routes.size(); i++)
	{
		if (connected_routes[i]->getrouteID() == y->getrouteID())
		{
			int count_0 = -1;
			int count_1 = -1;
			for (unsigned int j = 0; j < passing_trips.size(); j++)
			{
				if (passing_trips[j].second.first->getrouteID() == y->getrouteID() &&
					passing_trips[j].second.second->getdirection() == "0") count_0 = 1;
				if (passing_trips[j].second.first->getrouteID() == y->getrouteID() &&
					passing_trips[j].second.second->getdirection() == "1") count_1 = 1;
			}
			if (count_0 + count_1 == 2)	a = 1;
			else 
			{
				int count_0_x = -1;
				int count_1_x = -1;
				for (unsigned int j = 0; j < x->passing_trips.size(); j++)
				{
					if (x->passing_trips[j].second.first->getrouteID() == y->getrouteID() &&
						x->passing_trips[j].second.second->getdirection() == "0") count_0_x = 1;
					if (x->passing_trips[j].second.first->getrouteID() == y->getrouteID() &&
						x->passing_trips[j].second.second->getdirection() == "1") count_1_x = 1;
				}
				if (count_0 == count_0_x && count_1 == count_1_x) a = 1;
			}
		}
	}
	for (unsigned int i = 0; i < connected_routes_stops.size(); i++)
		if (connected_routes_stops[i].second->getrouteID() == y->getrouteID()) a = 1;

	if (a == 0) connected_routes_stops.push_back(make_pair(x, y));
}

void Stop::settransfer()
{
	int counter_route = 0;
	for (unsigned int i = 0; i < connected_routes.size(); i++)
	{
		for (unsigned int j = 0; j < connected_routes_stops.size(); j++)
		{
			if (connected_routes[i]->getrouteID() == connected_routes_stops[j].second->getrouteID()) counter_route = counter_route + 1;
		}
	}

	if (connected_routes.size() + connected_routes_stops.size() - counter_route > 1)
		transfer_stop = 1;
	else transfer_stop = 0;
	degree_centrality = connected_routes.size() + connected_routes_stops.size() - counter_route;
}