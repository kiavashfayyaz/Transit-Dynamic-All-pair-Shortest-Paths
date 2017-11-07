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
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

double deg2rad(double deg) 
{
	return (deg * pi / 180);
}

void Distance_SetCS_SetSD(Stop* a, Stop* b)
{
	double lat1r, lon1r, lat2r, lon2r, u, v, dist;
	lat1r = deg2rad(a->getlat());
	lon1r = deg2rad(a->getlon());
	lat2r = deg2rad(b->getlat());
	lon2r = deg2rad(b->getlon());
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	dist = 1000 * 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
	int distotime = (int) (dist / 1.4);
	if (dist <= 400 && a->getID() != b->getID())
	{
		// walking speed = 1.4 m/s, walking distance treshhold = 400 m, time = 4:45 minute
		a->setConnectedStop(b, distotime);
		b->setConnectedStop(a, distotime);
	}

	// if (dist > 700 && dist <= 1500) distotime = distotime * 2;
	// if (dist > 1500) distotime = distotime * 5;

	// seting the distance vector in STOP classes (stop getID is the postion of stop on vector) 

	unsigned int bigger_size = 0;
	if (a->getID() > b->getID()) bigger_size = a->getID();
	else bigger_size = b->getID();

	if (a->stop_distance.size() >= bigger_size + 1)
	{
		a->stop_distance[b->getID()] = distotime;
		a->stop_distance[a->getID()] = 0;
	}
	else if (a->stop_distance.size() < bigger_size + 1)
	{
		a->stop_distance.resize(bigger_size + 1, 0);
		a->stop_distance[b->getID()] = distotime;
		a->stop_distance[a->getID()] = 0;
	}

	if (b->stop_distance.size() >= bigger_size + 1)
	{
		b->stop_distance[a->getID()] = distotime;
		b->stop_distance[b->getID()] = 0;
	}
	else if (b->stop_distance.size() < bigger_size + 1)
	{
		b->stop_distance.resize(bigger_size + 1, 0);
		b->stop_distance[a->getID()] = distotime;
		b->stop_distance[b->getID()] = 0;
	}
}

int TimeToInt(string a)
{
	istringstream streamA(a);
	string hour;
	string minute;
	string second;

	getline(streamA, hour, ':');
	getline(streamA, minute, ':');
	getline(streamA, second, ':');

	return (atoi(hour.c_str()) * 3600) + (atoi(minute.c_str()) * 60) + (atoi(second.c_str()));
}