#pragma once
#include <vector>
#include "Vector3.h"

using namespace std;
class Animals
{
protected:
	vector<Vector3> bun, drag;
	vector<Vector3> bunv, dragv;
	Vector3 smallB, largeB, smallD, largeD;

public:
	Animals();
	~Animals();

	vector<Vector3> getBunny();
	vector<Vector3> getBunnyNorm();

	vector<Vector3> getDragon();
	vector<Vector3> getDragonNorm();

	Vector3 getSmallBunny();
	Vector3 getLargeBunny();
	Vector3 getSmallDragon();
	Vector3 getLargeDragon();

	void parseBunny();
	void parseDragon();
};

