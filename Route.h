#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include "StopClass.h"
#include "Trip.h"
using namespace std;

class Stop;
class Trip;

class Route
{
private:
	string routeID;
	vector<Trip*> trip_ofroute;
	vector<Stop*> stop_onroute;
	
public:
	Route(string);// vector<Trip*>, vector<Stop*>);
	int directional = 0;
	~Route();

	//geters
	string getrouteID() const;
	vector<Trip*> gettrips() const;
	vector<Stop*> getstops() const;

	//seters
	void setrouteID(string);
	void settrip_ofroute(Trip*);
	void setstop_onroute(Stop*);
};
