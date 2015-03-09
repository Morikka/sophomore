#pragma once
#include <iostream>
#include <fstream>

using namespace std;
static const int mx = 10, mn = 50, l = 10, inf = 0x3f3f3f3f;

class ans
{
	friend class Road;
	friend class Theroad;
	
	public:
		ans();
		~ans();
	private:
		char aname[l], abegin[l], aend[l];//save the train or the plane name,the total time of start and end;
		int atime, acost;//the total cost and time spent(time means start from the time that user input)
		string hub;//if the user need to change train or plane that the string save the state to change
};
