#include "Animals.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>


Animals::Animals()
{
	parseBunny();
	parseDragon();
}


Animals::~Animals()
{
}

void Animals::parseBunny() {
	cout << "Parsing bunny.xyz ... ";
	vector<double> t, n;
	double d;

	ifstream fin;
	fin.open("bunny.xyz");

	if (!fin.good()) return;

	int i = 0;
	while (fin >> d) {
		if((i%6)<3) t.push_back(d);
		else n.push_back(d);
		i++;
	}
	//bun = t;

	cout << "generating normals ... ";

	double x1 = 1, x2 = 0, y1 = 1, y2 = 0, z1 = 1, z2 = 0;
	for (unsigned int i = 0; i < t.size(); i += 3) {
		bun.push_back(*new Vector3(t[i], t[i + 1], t[i + 2]));
		bunv.push_back(*new Vector3(n[i], n[i + 1], n[i + 2]));
		if (t[i] < x1) x1 = t[i];
		else if (t[i] > x2) x2 = t[i];
		if (t[i + 1] < y1) y1 = t[i + 1];
		else if (t[i + 1] > y2) y2 = t[i + 1];
		if (t[i + 2] < z1) z1 = t[i + 2];
		else if (t[i + 2] > z2) z2 = t[i + 2];
	}
	smallB = (*new Vector3(x1, y1, z1));
	largeB = (*new Vector3(x2, y2, z2));

	cout << bun.size() << "/" << bunv.size() << " ";

	for (unsigned int j = 0; j < bunv.size(); j++)
		bunv[j].normalize();

	cout << "done." << endl;
}

void Animals::parseDragon() {
	cout << "Parsing dragon.xyz ... ";
	vector<double> t, n;
	double d;

	ifstream fin;
	fin.open("dragon.xyz");

	if (!fin.good()) return;

	int i = 0;
	while (fin >> d) {
		if((i%6)<3) t.push_back(d);
		else n.push_back(d);
		i++;
	}
	//drag = t;

	cout << "generating normals ... "; 
	
	double x1 = 1, x2 = 0, y1 = 1, y2 = 0, z1 = 1, z2 = 0;
	for (unsigned int i = 0; i < t.size(); i += 3) {
		drag.push_back(*new Vector3(t[i], t[i + 1], t[i + 2]));
		dragv.push_back(*new Vector3(n[i], n[i + 1], n[i + 2]));
		if (t[i] < x1) x1 = t[i];
		else if (t[i] > x2) x2 = t[i];
		if (t[i + 1] < y1) y1 = t[i + 1];
		else if (t[i + 1] > y2) y2 = t[i + 1];
		if (t[i + 2] < z1) z1 = t[i + 2];
		else if (t[i + 2] > z2) z2 = t[i + 2];
	}
	smallD = (*new Vector3(x1, y1, z1));
	largeD = (*new Vector3(x2, y2, z2));

	cout << drag.size() << "/" << dragv.size() << " ";

	for (unsigned int j = 0; j < dragv.size(); j++)
		dragv[j].normalize();

	cout << "done." << endl;
}

vector<Vector3> Animals::getBunny() {
	return bun;
}

vector<Vector3> Animals::getBunnyNorm() {
	return bunv;
}

vector<Vector3> Animals::getDragon() {
	return drag;
}

vector<Vector3> Animals::getDragonNorm() {
	return dragv;
}

Vector3 Animals::getSmallBunny() {
	return smallB;
}

Vector3 Animals::getLargeBunny() {
	return largeB;
}

Vector3 Animals::getSmallDragon() {
	return smallD;
}

Vector3 Animals::getLargeDragon() {
	return largeD;
}