#pragma once
#include "stdafx.h"
#include "ans.h"
#include <iostream>

using namespace std;
class Road {
	friend class ans;
	friend class Theroad;
public:
	Road() {
		tcnt = pcnt = 0;
	}
private:
	int tcnt;//the number of the train
	char tname[mn][l], ttname1[mn][l], ttname2[mn][l];//the train name the start time and the end time
	int tcost[mn];//the cost of the train
	int pcnt;//the number of the plane
	char pname[mn][l], ptname1[mn][l], ptname2[mn][l];//the plane name the start time and the end time
	int pcost[mn];//the cost of the plane
};