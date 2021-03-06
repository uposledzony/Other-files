// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <regex>
#include <fstream>
#include<utility>
#include <map>
using namespace std;
class graph {
public:
	vector<pair<pair<char, pair<bool,int>>,vector<char>>> adjacency_list = vector<pair<pair<char, pair<bool, int>>, vector<char>>>();
	pair<pair<char, pair<bool, int>>, vector<char>>* operator[](char c) {
		for (int i = 0; i < adjacency_list.size(); ++i) {
			if (adjacency_list[i].first.first == c) {
				return &adjacency_list[i];
			}
		}
		return NULL;
	}
	graph() {
		for (char c = 'A'; c <= 'Z'; c++) {
			adjacency_list.push_back(make_pair(make_pair(c, make_pair(false, 0)), vector<char>()));
		}
	}
	friend ostream& operator << (ostream& o, const graph& g) {
		for (int i = 0; i < g.adjacency_list.size(); ++i) {
			o << "Node: " << (g.adjacency_list[i].first.first) << endl;
			o << "Is visited?: " << g.adjacency_list[i].first.second.first << endl;
			o << "Parents' counter: " << g.adjacency_list[i].first.second.second << endl;
			o << "List of children: ";
			for (int j = 0; j < g.adjacency_list[i].second.size(); ++j) {
				o << g.adjacency_list[i].second[j] << ", ";
			}
			o << endl;
		}
		return o;
	}
};
int main(){
	cout << "Hello World!\n"; 
	fstream F("input3.txt", fstream::in);
	graph g;
	graph g2;
	if (F.is_open()) {
		cout << "file is already opened" << endl;
	}
	while (!(F.eof())) {
		smatch sm;
		string s;
		getline(F, s);
		string parent, child;
		regex re("[A-Z]");
		int i = 0;
		while(regex_search(s, sm, re)) {
			for (auto x : sm) {
				if (i == 1) parent = string(x);
				if (i == 2) child = string(x);
			}
			++i;
			if (i > 2) i = 0;
			s = sm.suffix().str();
		}
		g[parent[0]]->second.push_back(child[0]);
		g[child[0]]->first.second.second += 1;	
	}
	g2 = g;
	cout << g;
	vector<char> queue;
	for (auto p : g.adjacency_list) {
		if (!p.first.second.second) {
			queue.push_back(p.first.first);
		}
	}
	sort(queue.begin(), queue.end());
	string out = "";
	while (!queue.empty()) {
		sort(queue.begin(), queue.end());
		char c = queue[0];
		queue = [queue](char c)->vector<char> {vector<char> vec; for (auto ch : queue) if (ch != c) vec.push_back(ch); return vec;}(c);
		for (auto child : g[c]->second) {
			g[child]->first.second.second--;
			if (!g[child]->first.second.second) queue.push_back(child);
		}
		out += c;
	}
	cout << out << endl;
	unsigned int workingTime = 0;
	for (auto p : g2.adjacency_list) {
		if (!p.first.second.second) {
			queue.push_back(p.first.first);
		}
	}
	cout << g2 << endl;
	vector<pair<char, unsigned int>> part_two;
	part_two = [&part_two](vector<char> &q, int time)->vector<pair<char, unsigned int>> {while (part_two.size() < 5 && q.size()) { char x = *min_element(q.begin(), q.end()); q = [q](char c)->vector<char> {vector<char> vec; for (char ch : q) if (ch != c) vec.push_back(ch); return vec; }(x); part_two.push_back(make_pair(x, time + 61 + x - 'A'));} return part_two; }(queue, workingTime);
	while (part_two.size() || queue.size()) {
		pair<char, unsigned int> p = *min_element(part_two.begin(), part_two.end(), [](pair<char, unsigned> p1, pair<char, unsigned> p2) {return p1.second < p2.second; });
		char c = p.first;
		workingTime = p.second;
		part_two = [&part_two](pair<char, unsigned int> p) {vector<pair<char, unsigned int>> vec; for (auto p1 : part_two) if (p != p1) vec.push_back(p1); return vec; }(p);
		for (auto child : g2[c]->second) {
			g2[child]->first.second.second--;
			if (!g2[child]->first.second.second) queue.push_back(child);
		}
		part_two = [&part_two](vector<char> &q, int time)->vector<pair<char, unsigned int>> {while (part_two.size() < 5 && q.size()) { char x = *min_element(q.begin(), q.end()); q = [q](char c)->vector<char> {vector<char> vec; for (char ch : q) if (ch != c) vec.push_back(ch); return vec; }(x); part_two.push_back(make_pair(x, time + 61 + x - 'A')); }return part_two; }(queue, workingTime);
	}
	cout << workingTime << endl;
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
