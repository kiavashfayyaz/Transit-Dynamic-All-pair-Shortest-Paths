#include "StopClass.h"
#include "Route.h"
#include "Trip.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include "Functions.h"
#include "ShortestPath.h"
#include <time.h>
#include <thread>
#include "multi_threading.h"


using namespace std;

//Unordered map for stop
unordered_map<string, int> findID_fromStopID;

//unordered map for routes
unordered_map<string, int> findRoute_fromID;

//Unordered map for trip
unordered_map<string, int> findTrip_fromTripID;

//Unordered map of trip and route
unordered_map<string, string> findRouteID_fromTripID;

// stop holder vector 
vector<Stop*> stop_holder;

// route holder vector
vector<Route*> route_holder;

// trip holder vector
vector<Trip*> trip_holder;

// parameter of StopTime-file: StopTime_tripID, StopTime_arrivalTime, StopTime_departureTime, StopTime_stopID, StopTime_sequence



int main()
{
	
	// Reads Stops file into: vector<Stop> stop_holder
	unsigned int nthreads = thread::hardware_concurrency();
	cout << "number of available threads: " << nthreads << endl;

	string lineStation;
	string nameStation;
	ifstream fileStation;

	cout << "Please provide the path to GTFS-Stops File: t" << endl;
	cin >> nameStation;
	// C:\Users\Kia\Desktop\GTFS\stgeorge
	string filename_Stops = "C:\\Users\\Kia\\Desktop\\GTFS\\UTA\\stops.tx" + nameStation;
	fileStation.open(filename_Stops);

	if (fileStation.fail())
	{
		cerr << "Opening Station file has failed";
		exit(1);
	}

	cout << "\n" << endl;

	while (fileStation.good())
	{
		int IDgenerator = -1;
		while (getline(fileStation, lineStation))
		{
			istringstream streamA(lineStation);
			IDgenerator = IDgenerator + 1;
			string stpID;
			string stpCode;
			string stpDesc;
			string stplat;
			string stplon;
			string stpname;

			getline(streamA, stpID, ',');

			getline(streamA, stpCode, ',');

			getline(streamA, stpname, ',');

			getline(streamA, stpDesc, ',');

			getline(streamA, stplat, ',');

			getline(streamA, stplon, ',');

			Stop *new_stp = new Stop(IDgenerator, stpID, atof(stplat.c_str()), atof(stplon.c_str()));
			stop_holder.push_back(new_stp);

			//stop_holder[1]->
			//to find the related Stop use the "vector::at", so the Stop will be stop_holder.at(findID_fromStopID[stpID])
			findID_fromStopID[stpID] = IDgenerator;

		}
	}

	/* cout << "# Stops: " << stop_holder.size() << endl;
	for (unsigned int i = 0; i < stop_holder.size(); i++)
	{
		cout << "Stps file title line:   ID: " << stop_holder[i]->getID() << "   next is stopID:  " << stop_holder[i]->getstopID() << "   next is lat:  " << stop_holder[i]->getlat() << stop_holder[i]->getlon() << endl;
	}
	string stop_id_for_check = "1";
	cout << "the stop_id = 1 have ID: " << stop_holder[findID_fromStopID[stop_id_for_check]]->getID() << endl; */
	getchar();
	string kia;
	cout << "enter kia: ..." << endl;
	cin >> kia;

	// Reads Route file into: vector<Route> route_holder

	string lineRoute;
	string nameRoute;
	ifstream fileRoute;

	cout << "Please provide the path to GTFS-Route File: t" << endl;
	cin >> nameRoute;
	// C:\Users\Kia\Desktop\GTFS\stgeorge
	string filename_Route = "C:\\Users\\Kia\\Desktop\\GTFS\\UTA\\routes.tx" + nameRoute;
	fileRoute.open(filename_Route);

	if (fileRoute.fail())
	{
		cerr << "Opening Station file has failed";
		exit(1);
	}

	cout << "\n" << endl;

	while (fileRoute.good())
	{
		int IDgenerator = -1;
		while (getline(fileRoute, lineRoute))
		{
			istringstream streamA(lineRoute);
			IDgenerator = IDgenerator + 1;
			string rtID;
			string agcID;
			string rtname;

			getline(streamA, rtID, ',');

			getline(streamA, agcID, ',');

			getline(streamA, rtname, ',');

			Route *new_rt = new Route(rtID);
			route_holder.push_back(new_rt);

			//to find the related route use the "vector::at", so the route will be route_holder.at(findRoute_fromID[rtID])
			findRoute_fromID[rtID] = IDgenerator;
		}
	}

	//cout << "# Routes: " << route_holder.size() << endl;
	//cout << "Route file title line:   ID: " << route_holder[0]->getrouteID() << endl;
	//cout << "Route file first line:   ID: " << route_holder[1]->getrouteID() << endl;
	//cout << "the Route_id = 1 have ID: " << route_holder[findRoute_fromID[stop_id_for_check]]->getrouteID() << endl;
	getchar();
	cout << "enter kia: ..." << endl;
	cin >> kia;

	// Reads Trips file into:
	// parameter of Trips-file: Trips_routeID, Trips_serviceID, Trips_tripID, Trips_directionID

	string lineTrips;
	string nameTrips;
	ifstream fileTrips;

	cout << "Please provide the path to GTFS-Trips File: v(CSV)" << endl;
	cin >> nameTrips;
	string filename_Trips = "C:\\Users\\Kia\\Desktop\\GTFS\\UTA\\tripsWeekdays.cs" + nameTrips;
	fileTrips.open(filename_Trips);

	if (fileTrips.fail())
	{
		cerr << "Opening Trips file has failed";
		exit(1);
	}

	cout << "\n" << endl;

	while (fileTrips.good())
	{
		int IDgenerator = -1;
		while (getline(fileTrips, lineTrips))
		{
			istringstream streamA(lineTrips);
			IDgenerator = IDgenerator + 1;
			string trphs;
			string rtID;
			string serviceID;
			string trpID;
			string dirID;

			getline(streamA, rtID, ',');

			getline(streamA, serviceID, ',');

			getline(streamA, trpID, ',');

			getline(streamA, trphs, ',');

			getline(streamA, dirID, ',');

			Trip *new_trp = new Trip(trpID, dirID);
			trip_holder.push_back(new_trp);

			route_holder[findRoute_fromID[rtID]]->settrip_ofroute(new_trp);
			if (atoi(dirID.c_str()) == 1) route_holder[findRoute_fromID[rtID]]->directional = 1;

			//to find the related route use the "vector::at", so the route will be route_holder.at(findRoute_fromID[rtID])
			findTrip_fromTripID[trpID] = IDgenerator;
			findRouteID_fromTripID[trpID] = rtID;

		}
	}

	/*cout << "# Trips: " << route_holder.size() << endl;
	cout << "Trips file title line:   trip_ID: " << trip_holder[0]->gettripID() << " Direction is: " << trip_holder[0]->getdirection() << endl;
	cout << "Route 1's trips: " << endl; 
	for (unsigned int i = 0; i < 100; i++)
	{
		cout << trip_holder[i]->gettripID() << "has direction: " << trip_holder[i]->getdirection() << endl;
		if (trip_holder[i]->getdirection() == "0")
		{
			cout << "TRUE" << endl;
		}
		else
		{
			cout << "false" << endl;
		}
	}
	*/
	getchar();
	cout << "enter kia: ..." << endl;
	cin >> kia;

	// Reads StopTimes file into:
	// parameter: StopTime_tripID, StopTime_arrivalTime, StopTime_departureTime, StopTime_stopID, StopTime_sequence

	string lineStopTimes;
	string nameStopTimes;
	ifstream fileStopTimes;
	int weekday_count = 0;

	cout << "Please provide the path to GTFS-Stop-Times File: t" << endl;
	cin >> nameStopTimes;
	string filename_StopTimes = "C:\\Users\\Kia\\Desktop\\GTFS\\UTA\\stop_times.tx" + nameStopTimes;
	fileStopTimes.open(filename_StopTimes);

	if (fileStopTimes.fail())
	{
		cerr << "Opening Station file has failed";
		exit(1);
	}

	cout << "\n" << endl;

	while (fileStopTimes.good())
	{
		while (getline(fileStopTimes, lineStopTimes))
		{
			istringstream streamA(lineStopTimes);
			string trpID;
			string arrtime;
			string deptime;
			string stopID;
			string stopseq;
			string stophs;

			getline(streamA, trpID, ',');

			getline(streamA, arrtime, ',');

			getline(streamA, deptime, ',');

			getline(streamA, stopID, ',');

			getline(streamA, stopseq, ',');

			getline(streamA, stophs, ',');

			int timearr = TimeToInt(arrtime);
			int timedep = TimeToInt(deptime);

			if (findTrip_fromTripID.count(trpID) > 0)
			{
				weekday_count = weekday_count + 1;
				//set stop and time in trip file
				trip_holder[findTrip_fromTripID[trpID]]->setstop_time_ontrip(stop_holder[findID_fromStopID[stopID]], timedep, atoi(stopseq.c_str()));

				//set stop on routes
				route_holder[findRoute_fromID[findRouteID_fromTripID[trpID]]]->setstop_onroute(stop_holder[findID_fromStopID[stopID]]);

				//set connected routes to stop
				stop_holder[findID_fromStopID[stopID]]->setConnectedRoutes(route_holder[findRoute_fromID[findRouteID_fromTripID[trpID]]]);

				//set passing trips to stop
				/*stop_holder[findID_fromStopID[stopID]]->passing_trips[timedep]
					= make_pair(route_holder[findRoute_fromID[findRouteID_fromTripID[trpID]]],
					trip_holder[findTrip_fromTripID[trpID]]);*/

				stop_holder[findID_fromStopID[stopID]]->passing_trips.push_back(make_pair(timedep, make_pair(route_holder[findRoute_fromID[findRouteID_fromTripID[trpID]]],
					trip_holder[findTrip_fromTripID[trpID]])));
			}
		}
	}
	
	/* cout << "Route 1's stops: " << endl;
	for (unsigned int i = 0; i < route_holder[findRoute_fromID[stop_id_for_check]]->getstops().size(); i++)
	{
		cout << route_holder[findRoute_fromID[stop_id_for_check]]->getstops()[i]->getstopID() << endl;
	}

	string tripID_test = "REDCLIFFS1";
	cout << " REDCLIFFS1's stopID, time and sequences are: " << endl;
	for (unsigned int i = 0; i < trip_holder[findTrip_fromTripID[tripID_test]]->getstop_time_ontrip().size(); i++)
	{
		cout << "stopID: " << trip_holder[findTrip_fromTripID[tripID_test]]->getstop_time_ontrip()[i].first->getstopID() << "   stop time: " <<
			trip_holder[findTrip_fromTripID[tripID_test]]->getstop_time_ontrip()[i].second.first << "  stop sequence: " <<
			trip_holder[findTrip_fromTripID[tripID_test]]->getstop_time_ontrip()[i].second.second << endl;
	}
	*/
	//getchar();
	cout << "number of weekday trips counted: " << weekday_count << endl;
	cout << "enter kia: ..." << endl;
	cin >> kia;

	string linePOP;
	ifstream filePopulation;
	string filename_Population = "C:\\Users\\Kia\\Desktop\\GTFS\\UTA\\population.csv";
	filePopulation.open(filename_Population);

	if (filePopulation.fail())
	{
		cerr << "Opening Station file has failed";
		exit(1);
	}

	cout << "\n" << endl;

	while (filePopulation.good())
	{
		while (getline(filePopulation, linePOP))
		{
			istringstream streamA(linePOP);
			string stop_id;
			string populationID;

			getline(streamA, stop_id, ',');

			getline(streamA, populationID, ',');
			//cout << " pop read is: " << populationID << endl;

			//set stop and time in trip file
			stop_holder[findID_fromStopID[stop_id]]->population = atoi(populationID.c_str());
		}
	}

	cout << stop_holder[20]->getID() << "  the pop is:   " << stop_holder[20]->population << endl;
	getchar();
	cout << "enter kia: ..." << endl;
	cin >> kia;

	// find the Connected stops for each stop
	// find the walking between all stops
	for (unsigned int i = 0; i < stop_holder.size(); i++)
	{
		for (unsigned int j = 0; j < stop_holder.size(); j++)
		{
			Distance_SetCS_SetSD(stop_holder[i], stop_holder[j]);
		}
	}
	double maxtt = 0;
	for (unsigned int i = 0; i < stop_holder[1]->stop_distance.size(); i++)
	{
		//cout << "distance between stop 1 and stop " << i << "   is:  " << stop_holder[1]->stop_distance[i] << endl;
		if (stop_holder[1]->stop_distance[i] >= maxtt) maxtt = stop_holder[1]->stop_distance[i];
	}
	//cout << "max tt for stop 1 is : " << maxtt << endl;
	getchar();
	cout << "enter kia: ..." << endl;
	cin >> kia;

	// set the connected stops, connected routes
	for (unsigned int i = 0; i < stop_holder.size(); i++)
	{
		for (unsigned int j = 0; j < stop_holder[i]->getConnectedStop().size(); j++)
		{
			for (unsigned int k = 0; k < stop_holder[i]->getConnectedStop().at(j).first->getConnectedroute().size(); k++)
			{
				stop_holder[i]->setconnectedroutesstops(stop_holder[i]->getConnectedStop().at(j).first,
					stop_holder[i]->getConnectedStop().at(j).first->getConnectedroute().at(k));
			}
		}
	}

	clock_t t1, t2;
	float diff;
	t1 = clock();
	ofstream closeness;
	closeness.open("C:\\Users\\Kia\\Desktop\\GTFS\\UTA\\closeness.csv");

	for (unsigned int i = 1; i < stop_holder.size(); i++)
	{
		double poptt = 0.0;
		for (unsigned int tt_stops = 1; tt_stops < stop_holder[i]->stop_distance.size(); tt_stops++)
		{
			poptt = poptt + (stop_holder[tt_stops]->population * stop_holder[i]->stop_distance[tt_stops]);
		}
		double closeNN = poptt / 661197.4;
		stop_holder[i]->settransfer();
		closeness << stop_holder[i]->getID() << "," << closeNN << "," << stop_holder[i]->degree_centrality << endl;
	}
	closeness.close();
	t2 = clock();
	diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
	cout << "closeness calculation time is: " << diff << endl;

	t1 = clock();

	/*ofstream betweenness;
	betweenness.open("C:\\Users\\Kia\\Desktop\\GTFS\\UTA\\betweenness.csv");

	for (unsigned int i = 1; i < stop_holder.size(); i++)
	{
		int btwn_centrality = 0;
		for (unsigned int j = 0; j < stop_holder[i]->getConnectedroute().size(); j++)
		{
			for (unsigned int k = 0; k < stop_holder[i]->getConnectedroute().at(j)->getstops().size(); k++)
			{
				btwn_centrality = btwn_centrality + stop_holder[i]->getConnectedroute().at(j)->getstops().at(k)->getTransfer();
			}
		}

		for (unsigned int j = 0; j < stop_holder[i]->getconnected_routes_stops().size(); j++)
		{
			for (unsigned int k = 0; k < stop_holder[i]->getconnected_routes_stops().at(j).second->getstops().size(); k++)
			{
				btwn_centrality = btwn_centrality + stop_holder[i]->getconnected_routes_stops().at(j).second->getstops().at(k)->getTransfer();
			}
		}
		betweenness << stop_holder[i]->getID() << "," << btwn_centrality << endl;

	}
	betweenness.close();
	*/

	t2 = clock();
	diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
	cout << "betweenness calculation time is: " << diff << endl;

	
	ofstream results_WATT;
	results_WATT.open("C:\\Users\\Kia\\Desktop\\GTFS\\UTA\\WATTresults.csv");
	string myline = "StationTime";
	for (unsigned int timeIT = 18000; timeIT < 18301; timeIT = timeIT + 300)
	{
		myline = myline + "," + to_string(timeIT);
	}
	results_WATT << myline << endl;
	vector<double> TTvector_for1;

	t1 = clock();
	for (unsigned int i = 1; i < stop_holder.size(); i++)
	{
		myline = stop_holder[i]->getstopID();

		for (unsigned int timeIT = 18000; timeIT < 18301; timeIT = timeIT + 300)
		{
			double poptt = 0.0;
			vector<double> TTvector = stop_holder[i]->stop_distance;
			vector<pair<Stop*, int>> r1;
			vector<pair<Stop*, int>> s1;
			vector<pair<Stop*, int>> s2;
			vector<pair<Stop*, int>> s3;
			
			//starting from the route passing the stop
			r1 = pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute(stop_holder[i], TTvector, timeIT)));
			cout << "routing1" << endl;
			s1 = pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute(stop_holder[i], TTvector, timeIT)), timeIT));
			cout << "routing2" << endl;
			s2 = pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute(stop_holder[i], TTvector, timeIT), timeIT)));
			cout << "routing3" << endl;
			s3 = pathfinder_CS_byRoute_second(TTvector, timeIT, 
				pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT, 
				pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute(stop_holder[i], TTvector, timeIT), timeIT)), timeIT));
			cout << "routing4" << endl;
			r1.insert(r1.end(),s1.begin(),s1.end());
			r1.insert(r1.end(), s2.begin(), s2.end());
			r1.insert(r1.end(), s3.begin(), s3.end());
			pathfinder_CS_byRoute_second(TTvector, timeIT, r1);
			cout << "routing5" << endl;
			pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS_second(TTvector, r1, timeIT));
			cout << "routing6" << endl;

			//starting from the connected stops of the stop
			r1 = pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS(stop_holder[i], timeIT))));
			cout << "stop routing1" << endl;
			s1 = pathfinder_CS_byRoute_second(TTvector, timeIT, 
				pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS(stop_holder[i], timeIT))), timeIT));
			cout << "stop routing2" << endl;
			s2 = pathfinder_CS_byRoute_second(TTvector, timeIT, 
				pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS(stop_holder[i], timeIT)), timeIT)));
			cout << "stop routing3" << endl;
			s3 = pathfinder_CS_byRoute_second(TTvector, timeIT,
				pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT,
				pathfinder_CS_byCS_second(TTvector, pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS(stop_holder[i], timeIT)), timeIT)), timeIT));
			cout << "stop routing4" << endl;
			r1.insert(r1.end(), s1.begin(), s1.end());
			r1.insert(r1.end(), s2.begin(), s2.end());
			r1.insert(r1.end(), s3.begin(), s3.end());
			pathfinder_CS_byRoute_second(TTvector, timeIT, r1);
			cout << "stop routing5" << endl;
			pathfinder_CS_byRoute_second(TTvector, timeIT, pathfinder_CS_byCS_second(TTvector, r1, timeIT));
			cout << "stop routing6" << endl;
			
			TTvector_for1 = TTvector;
			for (unsigned int tt_stops = 1; tt_stops < TTvector.size(); tt_stops++)
			{
				
				poptt = poptt + (stop_holder[tt_stops]->population * TTvector[tt_stops]);
			}
			double watt_time = poptt / 73239;
			myline = myline + "," + to_string(watt_time);
		}
		cout << "WATT for station number " << i << " is calculated" << endl;
		results_WATT << myline << endl;
	}
	results_WATT.close();
	

	t1 = clock();
	/*unsigned int start_processing = 14400;
	unsigned int processiong_interval_number = 1;
	unsigned int processing_interval = processiong_interval_number * 600;

	thread first(haste, "1", "first", stop_holder, start_processing, start_processing + processing_interval);
	thread second(haste, "2", "second", stop_holder, start_processing + processing_interval, start_processing + (processing_interval*2));
	thread third(haste, "3", "third", stop_holder, start_processing + (processing_interval * 2), start_processing + (processing_interval * 3));
	thread fourth(haste, "4", "fourth", stop_holder, start_processing + (processing_interval * 3), start_processing + (processing_interval * 4));
	thread fifth(haste, "5", "fifth", stop_holder, start_processing + (processing_interval * 4), start_processing + (processing_interval * 5));
	thread sixth(haste, "6", "sixth", stop_holder, start_processing + (processing_interval * 5), start_processing + (processing_interval * 6));
	//thread seventh(haste, "7", "seventh", stop_holder, start_processing + (processing_interval * 6), start_processing + (processing_interval * 7));
	//thread eighth(haste, "8", "eighth", stop_holder, 10, 20);

	*/
	/*unsigned int start_processing = 14400;
	unsigned int processiong_interval_number = 1;
	unsigned int processing_interval = processiong_interval_number * 600;

	thread first(haste, "1", "first", stop_holder, 14400, 79201);
	first.join();
	//second.join();
	//third.join();
	//fourth.join();
	//fifth.join();
	//sixth.join();
	//seventh.join();
	//eighth.join();

	t2 = clock();
	diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
	cout << "WATT calculation time is: " << diff << endl;
	cout << "type kia to finish: " << endl;
	cin >> kia;
	/*ofstream WATT_Notransit;
	WATT_Notransit.open("C:\\Users\\Kia\\Desktop\\GTFS\\stgeorge\\WATT_Notransit.csv");
	
	for (unsigned int i = 0; i < TTvector_for1.size(); i++)
	{
		WATT_Notransit << i << "," << TTvector_for1[i] << "," << stop_holder[1]->stop_distance[i] << endl;
	}
	for (unsigned int i = 1; i < stop_holder.size(); i++)
	{
		double poptt = 0.0;
		myline = stop_holder[i]->getstopID();
		for (unsigned int tt_stops = 1; tt_stops < stop_holder[i]->stop_distance.size(); tt_stops++)
		{

			poptt = poptt + (stop_holder[tt_stops]->population * stop_holder[i]->stop_distance[tt_stops]);
		}
		double watt_time = poptt / 661197.4;
		myline = myline + "," + to_string(watt_time);
		WATT_Notransit << myline << endl;
	}

	WATT_Notransit.close();*/


	return 0;
}