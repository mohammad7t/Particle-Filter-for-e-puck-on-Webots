#pragma once
#include<vector>
using namespace std;
class Observation
{
public:
	Observation(void);
	~Observation(void);
	vector<double> getPhysical();
	vector<double> getTheoretical();
	void setPhysical(vector<double> sensors);
	void setTheoretical(vector<double> sensors);

private:

	vector<double> physical;
	vector<double> theoretical;
};

