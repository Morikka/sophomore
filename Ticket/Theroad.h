#pragma once
#include "stdafx.h"
#include"ans.h"
#include"Road.h"
#include<map>
#include<iostream>

using namespace std;

class Theroad {
	friend class ans;
	friend class Road;
public:
	Theroad();//the constructed function
	void insertcity(char *chr);//the way to insert city
	bool findcity(string str);//judge if the city is in the text
	void printcity();//to paint all the city in the text
	int cnttime(char *time1, char *time2);//return the passing time by minute that time2 - time1 
	void inputt(ifstream& in,int n);//input the train table
	void inputp(ifstream& in,int n);//input the plane table
	void init(ifstream& in);//init the text
	void copyt1(int pos, int s, int e, int i, char *tm);//using in findroad
	void copyt2(int pos, int s, int t, int e, int i, int j, char *tm, string ct);//using in findroad
	int findroadtm(char *pn1, char *pn2, char *tm);//find the way that choose train and money
	int findroadtt(char *pn1, char *pn2, char *tm);//find the way that choose train and time
	void copyp1(int pos, int s, int e, int i, char *tm);//using in findroad
	void copyp2(int pos, int s, int tp, int e, int i, int j, char *tm, string ct);//using in findroad
	int findroadpm(char *pn1, char *pn2, char *tm);//find the way that choose plane and money
	int findroadpt(char *pn1, char *pn2, char *tm);//find the way that choose plane and time
	string printans(int num);//the string is the ans of the result
private:
	Road troad[mx][mx];//to save the plane or the train table between two city
	int citynum;//the number of the city
};

