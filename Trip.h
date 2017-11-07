#pragma once
#include <fstream>
#include <array>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include "Route.h"
#include "StopClass.h"

using namespace std;
class Stop;// pstop;
//typedef class Route * proute;

class Trip
{
private:
	string tripID;
	vector<pair<Stop*, pair<int, int> > > stop_time_ontrip;
	string direction_onroute;
public:
	Trip(string, string); // vector<pair<Stop*, string>>, string)
	~Trip();

	//geters
	string gettripID() const;
	vector<pair<Stop*, pair<int, int>>> getstop_time_ontrip() const;
	string getdirection() const;

	//seters
	void settripID(string);
	void setstop_time_ontrip(Stop*, int, int);
	void setdirection(string);
};