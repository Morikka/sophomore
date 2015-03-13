#pragma once
#include"stdafx.h"
#include"Theroad.h"
#include<map>
#include<stack>
#include <fstream>
#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
using namespace std;

map<string, int> place;//to store all city name and you can search the city by it's number
stack<int> knum;//if you delete a city ,this will keep the key number of the city
ans pans[3], ppns;//to store the answer of the way
//the constructed function
Theroad::Theroad(){
	citynum = 0;
	Road rrRoad;
	for (int i = 0; i < mx; i++)
		for (int j = 0; j < mx; j++)
			troad[i][j] = rrRoad;
	ifstream in("in.txt");
	//ofstream out("out.txt");
	init(in);
	in.close();
}
//init the text
void Theroad::init(ifstream& in) {
	int n;
	in >> n;//the number of the train table
	inputt(in,n);
	in >> n;
	inputp(in,n);//the number of the plane table
	cout << "finish" << endl;
}
//the way to insert city
void Theroad::insertcity(char *chr) {
	if (place.count(chr)) {
		return;
	}
	if (knum.empty()) {
		citynum++;
		place.insert(pair<string, int>(chr, citynum));
	}
	else {
		place.insert(pair<string, int>(chr, knum.top()));
		knum.pop();
	}
}
//to paint all the city in the text
void Theroad::printcity() {
	ofstream out("test.txt");
	for (map<string, int>::iterator it = place.begin(); it != place.end(); it++)
		out << it->first << " " << it->second << endl;
	out.close();
}
//judge if the city is in the text
bool Theroad::findcity(string str){
	for (map<string, int>::iterator it = place.begin(); it != place.end(); it++)
		if (it->first == str)
			return true;
	return false;
}
//return the passing time by minute that time2 - time1 
int Theroad::cnttime(char *time1, char *time2) {
	int tm1, tm2, res = 0;
	tm1 = ((time1[0] - '0') * 10 + time1[1] - '0') * 60 + (time1[3] - '0') * 10 + time1[4] - '0';
	tm2 = ((time2[0] - '0') * 10 + time2[1] - '0') * 60 + (time2[3] - '0') * 10 + time2[4] - '0';
	res = tm2 - tm1;
	if (res<10)res += 24 * 60;
	return res;
}
//input the train table
void Theroad::inputt(ifstream& in,int n) {
	int s, e, pos, cnt, st, tc[mn];
	char name[l], tn[mn][l], ttm1[mn][l], ttm2[mn][l];
	for (int i = 0; i<n; i++) {
		//scanf("%s%d", name, &st);
		in >> name >> st;
		for (int j = 0; j<st; j++) {
			//scanf("%s%s%s%d", tn[j], ttm1[j], ttm2[j], &tc[j]);
			in >> tn[j] >> ttm1[j] >> ttm2[j] >> tc[j];
			insertcity(tn[j]);
		}
		for (int j = 0; j<st; j++) {
			cnt = 0;
			s = place.find(tn[j])->second;
			for (int k = j + 1; k<st; k++) {
				e = place.find(tn[k])->second;
				pos = troad[s][e].tcnt;
				cnt += tc[k];
				strcpy_s(troad[s][e].tname[pos], name);
				strcpy_s(troad[s][e].ttname1[pos], ttm1[j]);
				strcpy_s(troad[s][e].ttname2[pos], ttm2[k]);
				troad[s][e].tcost[pos] = cnt;
				troad[s][e].tcnt++;
			}
		}
	}
}
//input the plane table
void Theroad::inputp(ifstream& in,int n) {
	char name[l], pn1[l], pn2[l], tm1[l], tm2[l];
	int cost;
	for (int i = 0; i<n; i++) {
		//scanf("%s%s%s%d%s%s", name, pn1, pn2, &cost, tm1, tm2);
		in >> name >> pn1 >> pn2 >> cost >> tm1 >> tm2;
		insertcity(pn1);
		insertcity(pn2);
		int s = place.find(pn1)->second;
		int e = place.find(pn2)->second;
		int pos = troad[s][e].pcnt;
		strcpy_s(troad[s][e].pname[pos], name);
		strcpy_s(troad[s][e].ptname1[pos], tm1);
		strcpy_s(troad[s][e].ptname2[pos], tm2);
		troad[s][e].pcost[pos] = cost;
		troad[s][e].pcnt++;
	}
}
//using in findroad
void Theroad::copyt1(int pos, int s, int e, int i, char *tm) {
	strcpy_s(pans[pos].aname, troad[s][e].tname[i]);
	pans[pos].acost = troad[s][e].tcost[i];
	pans[pos].atime = cnttime(tm, troad[s][e].ttname1[i]) + cnttime(troad[s][e].ttname1[i], troad[s][e].ttname2[i]);
	strcpy_s(pans[pos].abegin, troad[s][e].ttname1[i]);
	strcpy_s(pans[pos].aend, troad[s][e].ttname2[i]);
}
//using in findroad
void Theroad::copyt2(int pos, int s, int tp, int e, int i, int j, char *tm, string ct) {
	strcpy_s(pans[pos].aname, troad[s][tp].tname[i]);
	pans[pos].aname[4] = '-';
	strcpy_s(pans[pos].aname + 5,5,troad[tp][e].tname[j]);
	pans[pos].acost = troad[s][tp].tcost[i] + troad[tp][e].tcost[j];
	pans[pos].atime = cnttime(tm, troad[s][tp].ttname1[i]) + cnttime(troad[s][tp].ttname1[i], troad[s][tp].ttname2[i]) + cnttime(troad[s][tp].ttname2[i], troad[tp][e].ttname1[j]) + cnttime(troad[tp][e].ttname1[j], troad[tp][e].ttname2[j]);
	strcpy_s(pans[pos].abegin, troad[s][tp].ttname1[i]);
	strcpy_s(pans[pos].aend, troad[tp][e].ttname2[j]);
	pans[pos].hub = ct;
}
//find the way that choose train and money
int Theroad::findroadtm(char *pn1, char *pn2, char *tm) {
	int s = place.find(pn1)->second;
	int e = place.find(pn2)->second;
	int num = 0, cost;
	string ct;
	for (int i = 0; i<troad[s][e].tcnt; i++) {
		cost = troad[s][e].tcost[i];
		if (cost<pans[0].acost) {
			pans[2] = pans[1];
			pans[1] = pans[0];
			copyt1(0, s, e, i, tm);
		}
		else if (cost<pans[1].acost) {
			pans[2] = pans[1];
			copyt1(1, s, e, i, tm);
		}
		else if (cost<pans[2].acost)
			copyt1(2, s, e, i, tm);
		num++;
	}
	if (num>3)return 3;
	for (map<string, int>::iterator it = place.begin(); it != place.end(); it++) {
		if (it->second == s || it->second == e)continue;
		int tp = it->second;
		ct = it->first;
		for (int i = 0; i<troad[s][tp].tcnt; i++)
			for (int j = 0; j<troad[tp][e].tcnt; j++) {
				if (!strcmp(troad[s][tp].tname[i], troad[tp][e].tname[j]))continue;
				cost = troad[s][tp].tcost[i] + troad[tp][e].tcost[j];
				if (cost<pans[0].acost) {
					pans[2] = pans[1];
					pans[1] = pans[0];
					copyt2(0, s, tp, e, i, j, tm, ct);
				}
				else if (cost<pans[1].acost) {
					pans[2] = pans[1];
					copyt2(1, s, tp, e, i, j, tm, ct);
				}
				else if (cost<pans[2].acost)
					copyt2(2, s, tp, e, i, j, tm, ct);
				num++;
			}
	}
//	printans(num);
	return num;
}
//find the way that choose train and time
int Theroad::findroadtt(char *pn1, char *pn2, char *tm) {
	int s = place.find(pn1)->second;
	int e = place.find(pn2)->second;
	int num = 0, time;
	string ct;
	for (int i = 0; i<troad[s][e].tcnt; i++) {
		time = cnttime(tm, troad[s][e].ttname1[i]) + cnttime(troad[s][e].ttname1[i], troad[s][e].ttname2[i]);
		if (time<pans[0].atime) {
			pans[2] = pans[1];
			pans[1] = pans[0];
			copyt1(0, s, e, i, tm);
		}
		else if (time<pans[1].atime) {
			pans[2] = pans[1];
			copyt1(1, s, e, i, tm);
		}
		else if (time<pans[2].atime)
			copyt1(2, s, e, i, tm);
		num++;
	}
	if (num>3)return 3;
	for (map<string, int>::iterator it = place.begin(); it != place.end(); it++) {
		if (it->second == s || it->second == e)continue;
		int tp = it->second;
		ct = it->first;
		for (int i = 0; i<troad[s][tp].tcnt; i++)
			for (int j = 0; j<troad[tp][e].tcnt; j++) {
				if (!strcmp(troad[s][tp].tname[i], troad[tp][e].tname[j]))continue;
				time = cnttime(tm, troad[s][tp].ttname1[i]) + cnttime(troad[s][tp].ttname1[i], troad[s][tp].ttname2[i]) + cnttime(troad[s][tp].ttname2[i], troad[tp][e].ttname1[j]) + cnttime(troad[tp][e].ttname1[j], troad[tp][e].ttname2[j]);
				if (time<pans[0].atime) {
					pans[2] = pans[1];
					pans[1] = pans[0];
					copyt2(0, s, tp, e, i, j, tm, ct);
				}
				else if (time<pans[1].atime) {
					pans[2] = pans[1];
					copyt2(1, s, tp, e, i, j, tm, ct);
				}
				else if (time<pans[2].atime)
					copyt2(2, s, tp, e, i, j, tm, ct);
				num++;
			}
	}
//	printans(num);
	return num;
}
//using in findroad
void Theroad::copyp1(int pos, int s, int e, int i, char *tm) {
	strcpy_s(pans[pos].aname, troad[s][e].pname[i]);
	pans[pos].acost = troad[s][e].pcost[i];
	pans[pos].atime = cnttime(tm, troad[s][e].ptname1[i]) + cnttime(troad[s][e].ptname1[i], troad[s][e].ptname2[i]);
	strcpy_s(pans[pos].abegin, troad[s][e].ptname1[i]);
	strcpy_s(pans[pos].aend, troad[s][e].ptname2[i]);
}
//using in findroad
void Theroad::copyp2(int pos, int s, int tp, int e, int i, int j, char *tm, string ct){
	strcpy_s(pans[pos].aname, troad[s][tp].pname[i]);
	pans[pos].aname[4] = '-';
	strcpy_s(pans[pos].aname + 5,5,troad[tp][e].pname[j]);
	pans[pos].acost = troad[s][tp].pcost[i] + troad[tp][j].pcost[j];
	pans[pos].atime = cnttime(tm, troad[s][tp].ptname1[i]) + cnttime(troad[s][tp].ptname1[i], troad[s][tp].ptname2[i]) + cnttime(troad[s][tp].ptname2[i], troad[tp][e].ptname1[j]) + cnttime(troad[tp][e].ptname1[j], troad[tp][e].ptname2[j]);
	strcpy_s(pans[pos].abegin, troad[s][tp].ptname1[i]);
	strcpy_s(pans[pos].aend, troad[tp][e].ptname2[j]);
	pans[pos].hub = ct;
}
//find the way that choose plane and money
int Theroad::findroadpm(char *pn1, char *pn2, char *tm) {
	int s = place.find(pn1)->second;
	int e = place.find(pn2)->second;
	int num = 0, cost;
	string ct;
	for (int i = 0; i<troad[s][e].pcnt; i++) {
		cost = troad[s][e].pcost[i];
		if (cost<pans[0].acost) {
			pans[2] = pans[1];
			pans[1] = pans[0];
			copyp1(0, s, e, i, tm);
		}
		else if (cost<pans[1].acost) {
			pans[2] = pans[1];
			copyp1(1, s, e, i, tm);
		}
		else if (cost<pans[2].acost)
			copyp1(2, s, e, i, tm);
		num++;
	}
	if (num>3)return 3;
	for (map<string, int>::iterator it = place.begin(); it != place.end(); it++) {
		if (it->second == s || it->second == e)continue;
		int tp = it->second;
		ct = it->first;
		for (int i = 0; i<troad[s][tp].pcnt; i++)
			for (int j = 0; j<troad[tp][e].pcnt; j++) {
				cost = troad[s][tp].pcost[i] + troad[tp][j].pcost[j];
				if (cost<pans[0].acost) {
					pans[2] = pans[1];
					pans[1] = pans[0];
					copyp2(0, s, tp, e, i, j, tm, ct);
				}
				else if (cost<pans[1].acost) {
					pans[2] = pans[1];
					copyp2(1, s, tp, e, i, j, tm, ct);
				}
				else if (cost<pans[2].acost)
					copyp2(2, s, tp, e, i, j, tm, ct);
				num++;
			}
	}
//	printans(num);
	return num;
}
//find the way that choose plane and time
int Theroad::findroadpt(char *pn1, char *pn2, char *tm) {
	int s = place.find(pn1)->second;
	int e = place.find(pn2)->second;
	int num = 0, time;
	string ct;
	for (int i = 0; i<troad[s][e].pcnt; i++) {
		time = cnttime(tm, troad[s][e].ptname1[i]) + cnttime(troad[s][e].ptname1[i], troad[s][e].ptname2[i]);
		if (time<pans[0].atime) {
			pans[2] = pans[1];
			pans[1] = pans[0];
			copyp1(0, s, e, i, tm);
		}
		else if (time<pans[1].atime) {
			pans[2] = pans[1];
			copyp1(1, s, e, i, tm);
		}
		else if (time<pans[2].atime)
			copyp1(2, s, e, i, tm);
		num++;
	}
	if (num>3)return 3;
	for (map<string, int>::iterator it = place.begin(); it != place.end(); it++) {
		if (it->second == s || it->second == e)continue;
		int tp = it->second;
		ct = it->first;
		for (int i = 0; i<troad[s][tp].pcnt; i++)
			for (int j = 0; j<troad[tp][e].pcnt; j++) {
				time = cnttime(tm, troad[s][tp].ptname1[i]) + cnttime(troad[s][tp].ptname1[i], troad[s][tp].ptname2[i]) + cnttime(troad[s][tp].ptname2[i], troad[tp][e].ptname1[j]) + cnttime(troad[tp][e].ptname1[j], troad[tp][e].ptname2[j]);
				if (time<pans[0].atime) {
					pans[2] = pans[1];
					pans[1] = pans[0];
					copyp2(0, s, tp, e, i, j, tm, ct);
				}
				else if (time<pans[1].atime) {
					pans[2] = pans[1];
					copyp2(1, s, tp, e, i, j, tm, ct);
				}
				else if (time<pans[2].atime)
					copyp2(2, s, tp, e, i, j, tm, ct);
				num++;
			}
	}
//	printans(num);
	return num;
}
//the string is the ans of the result
string Theroad::printans(int num) {
	string res;
	ostringstream oss;
	for (int i = 0; i < min(3, num); i++) {
		oss << "the " << i+1 << " choose is to take " << pans[i].aname;
		if (pans[i].hub.length() != 0)oss << " and change at " << pans[i].hub;
		oss << endl;
		//oss << "the time is " << pans[i].atime << " and the cost is" << pans[i].acost;
		pans[i] = ppns;
	}
	res = oss.str();
	return res;
}