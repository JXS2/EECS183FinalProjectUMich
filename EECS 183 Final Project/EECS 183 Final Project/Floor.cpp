/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include <algorithm>
#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
	int numExploded = 0;
	for (int i = 0; i < numPeople; i++)
	{
		if (people[i].tick(currentTime)) {
			numExploded++;
		}
	}
    return numExploded;
}

void Floor::addPerson(Person newPerson, int request) {
	numPeople++;
	if (numPeople < MAX_PEOPLE_PER_FLOOR) {
		people[numPeople] = newPerson;
	}
	resetRequests();
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
	int removedPeople = 0;
	int count = 0;
	numPeople -= numPeopleToRemove;
	Person temp[MAX_PEOPLE_PER_FLOOR];
	Person reset[MAX_PEOPLE_PER_FLOOR];

	// Sort indices array

	sort(indicesToRemove, indicesToRemove + numPeopleToRemove);

	// Create temp array 

	for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++)
	{
		temp[i] = people[i];
	}

	// Clear class array

	for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++)
	{
		people[i] = reset[i];
	}

	// add ONLY indices not marked for removal

	while (removedPeople < numPeopleToRemove)
	{
		if (indicesToRemove[removedPeople] == count){
			removedPeople++;
		}
		else
		{
			people[(numPeople)-(numPeople - removedPeople)] = temp[count];
		}
		count++;
	}
	
	resetRequests();

}

void Floor::resetRequests() {
	int countUp = 0;
	int countDown = 0;
	for (int i = 0; i < numPeople; i++)
	{
		if (people[i].getTargetFloor() - people[i].getCurrentFloor() > 0) {
			countUp++;
		}
		if (people[i].getTargetFloor() - people[i].getCurrentFloor() < 0) {
			countDown++;
		}
	}
	if (countUp > 0) {
		hasUpRequest = true;
	}
	else
	{
		hasUpRequest = false;
	}
	if (countDown > 0) {
		hasDownRequest = true;
	}
	else
	{
		hasDownRequest = false;
	}
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
