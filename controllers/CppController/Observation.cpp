#include "Observation.h"


Observation::Observation(void)
{
}
vector<double> Observation::getPhysical(){
	return physical;
}
vector<double> Observation::getTheoretical(){
	return theoretical;
}
void Observation::setPhysical(vector<double> input){
	physical = input;
}
void Observation::setTheoretical(vector<double> input){
	theoretical = input;
}
Observation::~Observation(void)
{
}
