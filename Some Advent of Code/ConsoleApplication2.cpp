// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include<utility>
#include <algorithm>
#include <map>
#define max_path 10000
using namespace std;
int find_min_Manhathan(const pair<int, int> & p, const vector<pair<pair<int, int>, int>> c) {
	int ret = -51;
	int min = 2000;
	for (int i = 0; i < c.size(); ++i) {
		if (abs(p.first - c[i].first.first) + abs(c[i].first.second  - p.second) < min) {
			min = abs(p.first - c[i].first.first) + abs(c[i].first.second - p.second);
			ret = c[i].second;
		}
		else if (abs(p.first - c[i].first.first) + abs(c[i].first.second - p.second) == min) {
			ret = -51;
		}
	}
	return ret;
}
int sum_Manhathan(const pair<int, int> & p, const vector<pair<pair<int, int>, int>> c) {
	int sum = 0;
	for (int i = 0; i < c.size(); ++i) {
		sum += abs(p.first - c[i].first.first) + abs(c[i].first.second - p.second);
	}
	return sum;
}
int main(){
    cout << "Hello World!\n"; 
	map<pair<int, int>, int> _map_ = map<pair<int, int>, int>();
	vector<pair<pair<int, int>, int>> coords = vector<pair<pair<int,int>, int>>();
	fstream F("input2.txt", fstream::in);
	int max = 1;
	while (!(F.eof())) {
		int x, y;
		char comma;
		F >> x >> comma >> y;
		max = max>x?(max>y?max:y):(x>y?x:y);
		coords.push_back(make_pair(make_pair(x, y), coords.size() + 1));
	}
	for (int i = 0; i <= max; ++i) {
		for (int j = 0; j <= max; ++j) {
			pair<int, int> tmp = make_pair(i, j);
			_map_.insert(make_pair(tmp, 0));
		}
	}
	for (pair<pair<int, int>, int> p : coords) {
		_map_[p.first] = p.second;
	}
	for (auto &p : _map_) {
		if (!any_of(coords.begin(), coords.end(), [p](pair<pair<int, int>, int> p1) { return p1.first == p.first; })) {
			p.second = find_min_Manhathan(p.first, coords);
		}
	}
	int max1 = 0;
	for (int i = 0; i < coords.size(); ++i) {
		int tmp = 0;
		bool finite = true;
		for (auto &p : _map_) {
			if (p.second == coords[i].second) {
				if (!p.first.first || !p.first.second || p.first.second == max || p.first.first == max) {
					finite = false;
				}
				++tmp;
			}
		}
		if (finite && tmp > max1) {
			max1 = tmp;
		}
	}
	cout << max1 << endl;
	max1 = 0;
	for (auto &p : _map_) {
		if (sum_Manhathan(p.first, coords) < max_path) {
			++max1;
		}
	}
	cout << max1 << endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
