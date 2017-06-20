#pragma once
#include<complex>
using namespace std;

typedef  complex<double> Point;
class Particle
{
public:
	Particle(void);
	~Particle(void);
	Point getPostion();
	double getAngle();
private:
	Point position;
	double angle;
};

