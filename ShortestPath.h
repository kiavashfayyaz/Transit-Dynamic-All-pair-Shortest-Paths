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

vector<pair<Stop*, int>> pathfinder_CS_byRoute(Stop* a, vector<double>& TT, int t)
{
		// vector<double> TTvector = stop_holder[i]->stop_distance;
	
	vector<pair<Stop*, int>> transfer_stops_connected;
	for (unsigned int j = 0; j < a->getConnectedroute().size(); j++)
		{
			int abbas = 86400;
			int abbas1 = 86400;
			int firsttrip = -1;
			int firsttrip1 = -1;
			for (unsigned int k = 0; k < a->passing_trips.size(); k++)
			{
				if (a->passing_trips[k].first - t > -1
					&& a->passing_trips[k].second.second->getdirection() == "0"
					&& a->passing_trips[k].first - t < abbas
					&& a->getConnectedroute().at(j)->getrouteID() == a->passing_trips[k].second.first->getrouteID())
				{
					abbas = a->passing_trips[k].first - t;
					firsttrip = k;
				}
				if (a->passing_trips[k].first - t > -1
					&& a->passing_trips[k].second.second->getdirection() == "1"
					&& a->passing_trips[k].first - t < abbas1
					&& a->getConnectedroute().at(j)->getrouteID() == a->passing_trips[k].second.first->getrouteID())
				{
					abbas1 = a->passing_trips[k].first - t;
					firsttrip1 = k;
				}
			}
			if (firsttrip > -1)
			{
				for (unsigned int k = 0; k < a->passing_trips[firsttrip].second.second->getstop_time_ontrip().size(); k++)
				{
					if (a->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).second.first >= a->passing_trips[firsttrip].first
						&& TT[a->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).first->getID()] >
						a->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).second.first - t)
					{
						//update travel time matrix
						TT[a->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).first->getID()] =
							a->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).second.first - t;

						// find connected transfer stops
						if (a->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).first->getTransfer() == 1)
							transfer_stops_connected.push_back(make_pair(a->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).first,
							a->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).second.first));
					}
				}
			}
			if (firsttrip1 > -1)
			{
				for (unsigned int k = 0; k < a->passing_trips[firsttrip1].second.second->getstop_time_ontrip().size(); k++)
				{
						if (a->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).second.first >= a->passing_trips[firsttrip1].first
						&& TT[a->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).first->getID()] >
						a->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).second.first - t)
					{
						//update travel time matrix
						TT[a->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).first->getID()] =
							a->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).second.first - t;

						// find connected transfer stops
						if (a->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).first->getTransfer() == 1)
							transfer_stops_connected.push_back(make_pair(a->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).first,
							a->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).second.first));
					}
				}
			}
		}
	return transfer_stops_connected;	
}

vector<pair<Stop*, int>> pathfinder_CS_byCS(Stop* a, int t)
{
	vector<pair<Stop*, int>> transfer_stops_connected;
	for (unsigned int j = 0; j < a->getconnected_routes_stops().size(); j++)
	{
		transfer_stops_connected.push_back(make_pair(a->getconnected_routes_stops().at(j).first, a->stop_distance[a->getconnected_routes_stops().at(j).first->getID()] + t));
	}
	return transfer_stops_connected;
}

vector<pair<Stop*, int>> pathfinder_CS_byRoute_second(vector<double>& TT, int t_first, vector<pair<Stop*, int>> b)
{
	// vector<double> TTvector = stop_holder[i]->stop_distance;
	
	vector<pair<Stop*, int>> transfer_stops_connected;
	for (unsigned int i = 0; i < b.size(); i++)
	{
		int t = b[i].second;
		for (unsigned int j = 0; j < b[i].first->getConnectedroute().size(); j++)
		{
			int abbas = 86400;
			int abbas1 = 86400;
			int firsttrip = -1;
			int firsttrip1 = -1;
			for (unsigned int k = 0; k < b[i].first->passing_trips.size(); k++)
			{
				if (b[i].first->passing_trips[k].first - t > -1
					&& b[i].first->passing_trips[k].second.second->getdirection() == "0"
					&& b[i].first->passing_trips[k].first - t < abbas
					&& b[i].first->getConnectedroute().at(j)->getrouteID() == b[i].first->passing_trips[k].second.first->getrouteID())
				{
					abbas = b[i].first->passing_trips[k].first - t;
					firsttrip = k;
				}
				if (b[i].first->passing_trips[k].first - t > -1
					&& b[i].first->passing_trips[k].second.second->getdirection() == "1"
					&& b[i].first->passing_trips[k].first - t < abbas1
					&& b[i].first->getConnectedroute().at(j)->getrouteID() == b[i].first->passing_trips[k].second.first->getrouteID())
				{
					abbas1 = b[i].first->passing_trips[k].first - t;
					firsttrip1 = k;
				}
			}

			if (firsttrip > -1)
			{
				for (unsigned int k = 0; k < b[i].first->passing_trips[firsttrip].second.second->getstop_time_ontrip().size(); k++)
				{
					if (firsttrip > -1 &&
						b[i].first->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).second.first >= b[i].first->passing_trips[firsttrip].first
						&& TT[b[i].first->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).first->getID()] >
						b[i].first->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).second.first - t_first)
					{
						//update travel time matrix
						TT[b[i].first->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).first->getID()] =
							b[i].first->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).second.first - t_first;

						// find connected transfer stops
						if (b[i].first->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).first->getTransfer() == 1)
							transfer_stops_connected.push_back(make_pair(b[i].first->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).first,
							b[i].first->passing_trips[firsttrip].second.second->getstop_time_ontrip().at(k).second.first));
					}
				}
			}
			if (firsttrip1 > -1)
			{
				for (unsigned int k = 0; k < b[i].first->passing_trips[firsttrip1].second.second->getstop_time_ontrip().size(); k++)
				{
					if (firsttrip1 > -1 &&
						b[i].first->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).second.first >= b[i].first->passing_trips[firsttrip1].first
						&& TT[b[i].first->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).first->getID()] >
						b[i].first->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).second.first - t_first)
					{
						//update travel time matrix
						TT[b[i].first->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).first->getID()] =
							b[i].first->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).second.first - t_first;

						// find connected transfer stops
						if (b[i].first->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).first->getTransfer() == 1)
							transfer_stops_connected.push_back(make_pair(b[i].first->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).first,
							b[i].first->passing_trips[firsttrip1].second.second->getstop_time_ontrip().at(k).second.first));
					}
				}
			}
		}
	}
	return transfer_stops_connected;
}

vector<pair<Stop*, int>> pathfinder_CS_byCS_second(vector<double>& TT, vector<pair<Stop*, int>> b, int t)
{
	vector<pair<Stop*, int>> transfer_stops_connected;
	for (unsigned int i = 0; i < b.size(); i++)
	{
		for (unsigned int j = 0; j < b[i].first->getconnected_routes_stops().size(); j++)
		{
			transfer_stops_connected.push_back(make_pair(b[i].first->getconnected_routes_stops().at(j).first, b[i].first->stop_distance[b[i].first->getconnected_routes_stops().at(j).first->getID()] + b[i].second));
			if (TT[b[i].first->getconnected_routes_stops().at(j).first->getID()] > b[i].first->stop_distance[b[i].first->getconnected_routes_stops().at(j).first->getID()] + b[i].second - t)
			TT[b[i].first->getconnected_routes_stops().at(j).first->getID()] = b[i].first->stop_distance[b[i].first->getconnected_routes_stops().at(j).first->getID()] + b[i].second - t;
		}
	}
	return transfer_stops_connected;
}