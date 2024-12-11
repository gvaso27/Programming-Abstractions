/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

//checks if result vector contains all of the cities
bool ifResultIsValid(Set<string>& cities, Vector< Set<string> >& result);

int main() {
	/* TODO: Add testing code here! */
	//cities = { "A", "B", "C", "D", "E", "F" }
	Set<string> cities;
	cities.add("A");
	cities.add("B");
	cities.add("C");
	cities.add("D");
	cities.add("E");
	cities.add("F");

	//locations ={"A", "B", "C"}, {"A", "C", "D"}, {"B", "F"}, {"C", "E", "F"} 
	Set<string> one;
	Set<string> two;
	Set<string> three;
	Set<string> four;
	one.add("A");
	one.add("B");
	one.add("C");
	two.add("A");
	two.add("C");
	two.add("D");
	three.add("B");
	three.add("F");
	four.add("C");
	four.add("E");
	four.add("F");
	Vector< Set<string> > locations;
	locations.add(one);
	locations.add(two);
	locations.add(three);
	locations.add(four);

	int numHospitals = 4;

	Vector<Set<string>> result;
	if (canOfferUniversalCoverage(cities, locations, numHospitals, result)){
		cout<<result<<endl;
	}
    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, 
							   int numHospitals, Vector< Set<string> >& result){

    //base cases
	if(result.size() > numHospitals)return false;
	if(result.size() <= numHospitals && ifResultIsValid(cities, result))return true;

	for(int i = 0; i < locations.size(); i++){
		result[result.size()-1] = locations[i];

		//i am using this if for the recursion to keep going even if this particular if is false
		if(canOfferUniversalCoverage(cities, locations, numHospitals, result)){
			return true;
		}

	}
	return false;
}

bool ifResultIsValid(Set<string> cities, Vector< Set<string> > result){
	int m;
	Set<string> copy = cities;
	if(result.size()>0){
		for(int i = 0; i < result.size(); i++){
			m = result[i].size();
			for(int j = 0; j < m; j++){
				if(copy.contains(result[j].first())){
					copy.remove(result[j].first());
				}
			}
		}
	}
	if(copy.isEmpty())return true;
	return false;
}
