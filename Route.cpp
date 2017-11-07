#include "Route.h"


Route::Route(string id)// vector<Trip*> , vector<Stop*>)
{
	routeID = id;
}



Route::~Route()
{
}


//geters
string Route::getrouteID() const
{
	return routeID;
}

vector<Trip*> Route::gettrips() const
{
	return trip_ofroute;
}

vector<Stop*> Route::getstops() const
{
	return stop_onroute;
}

//seters
void Route::setrouteID(string x)
{
	routeID = x;
}

void Route::settrip_ofroute(Trip* x)
{
	int a = 0;

	for (unsigned int i = 0; i < trip_ofroute.size(); i++)
		if (trip_ofroute[i]->gettripID() == x->gettripID()) a = 1;

	if (a == 0) trip_ofroute.push_back(x);
}

void Route::setstop_onroute(Stop* x)
{
	int a = 0;

	for (unsigned int i = 0; i < stop_onroute.size(); i++)
		if (stop_onroute[i]->getID() == x->getID()) a = 1;

	if (a == 0) stop_onroute.push_back(x);
}