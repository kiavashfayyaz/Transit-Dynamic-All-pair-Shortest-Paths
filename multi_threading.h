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
#include <cmath>
using namespace std;

void haste(string x, string thread_number, vector<Stop*> stop_holder, unsigned int start_time, unsigned int end_time)
{
	ofstream results_WATT;
	results_WATT.open("C:\\Users\\Kia\\Desktop\\GTFS\\UTA\\WATTresults"+ x + ".csv");
	string myline = "StationTime";
	for (unsigned int timeIT = start_time; timeIT < end_time; timeIT = timeIT + 60)
	{
		myline = myline + "," + to_string(timeIT);
	}
	results_WATT << myline << endl;

	for (unsigned int i = 1; i < 2 /*stop_holder.size()*/; i++)
	{
		myline = stop_holder[i]->getstopID();

		for (unsigned int timeIT = start_time; timeIT < end_time; timeIT = timeIT + 60)
		{
			double poptt = 0.0;
			vector<double> TTvector = stop_holder[i]->stop_distance;
			/*vector<pair<Stop*, int>> r1;
			vector<pair<Stop*, int>> s1;
			vector<pair<Stop*, int>> s2;
			vector<pair<Stop*, int>> s3;
			*/
			//starting from the route passing the stop
			pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute(stop_holder[i], TTvector, timeIT)));
			cout << "routing1" << endl;
			pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute(stop_holder[i], TTvector, timeIT)), timeIT));
			cout << "routing2" << endl;
			pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute(stop_holder[i], TTvector, timeIT), timeIT)));
			cout << "routing3" << endl;
			pathfinder_CS_byRoute_second(TTvector, timeIT,
				pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT,
				pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute(stop_holder[i], TTvector, timeIT), timeIT)), timeIT));
			cout << "routing4" << endl;

			//starting from the connected stops of the stop
			pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS(stop_holder[i], timeIT))));
			cout << "stop routing1" << endl;
			pathfinder_CS_byRoute_second(TTvector, timeIT,
				pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS(stop_holder[i], timeIT))), timeIT));
			cout << "stop routing2" << endl;
			pathfinder_CS_byRoute_second(TTvector, timeIT,
				pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS(stop_holder[i], timeIT)), timeIT)));
			cout << "stop routing3" << endl;
			pathfinder_CS_byRoute_second(TTvector, timeIT,
				pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT,
				pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS(stop_holder[i], timeIT)), timeIT)), timeIT));
			cout << "stop routing4" << endl;
	
			for (unsigned int tt_stops = 1; tt_stops < TTvector.size(); tt_stops++)
			{
				poptt = poptt + (stop_holder[tt_stops]->population * TTvector[tt_stops]);
			}
			double watt_time = poptt / 73239;
			myline = myline + "," + to_string(watt_time);
		}
		cout << "WATT for station number " << i << " is calculated on thread number: " << thread_number << endl;
		results_WATT << myline << endl;
	}
	results_WATT.close();
}