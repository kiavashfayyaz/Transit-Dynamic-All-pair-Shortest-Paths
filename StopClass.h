
#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include"Route.h"
#include "Trip.h"
#include <unordered_map>
using namespace std;

class Route;
class Trip;

class Stop{

private:
	int ID;
	string stopID;
	double stopLat;
	double stopLon;
	vector<pair<Stop*, int>> connected_stops;
	vector < Route* > connected_routes;
	vector < pair<Stop*, Route*>> connected_routes_stops;
	int transfer_stop;

public:
	Stop(int, string, double, double);//, vector<Stop*>, vector<Route*>);
	~Stop();

	vector<double> stop_distance;
	vector<pair<int, pair<Route*, Trip*>>> passing_trips;
	int population;
	unsigned int degree_centrality;

	//geters
	int getID() const;
	string getstopID() const;
	double getlat() const;
	double getlon() const;
	vector<pair<Stop*, int>> getConnectedStop() const;
	vector<Route*> getConnectedroute() const;
	vector < pair<Stop*, Route*>> getconnected_routes_stops() const;
	int getTransfer() const;

	//seters
	void setConnectedStop(Stop*, int);
	void setConnectedRoutes(Route*);
	void setconnectedroutesstops(Stop*, Route*);
	void settransfer();
};
