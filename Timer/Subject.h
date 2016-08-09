#ifndef SUBJECT_H
#define SUBJECT_H 

#include "Observer.h"


#include <iostream>
#include <list>


/** This class is the Subject */
class Subject
{
public:
	virtual ~Subject() {}
	virtual void subscribe(Observer *obs); // Subscribe an observer 
	virtual void unsubscribe(Observer *obs); // Unsubscribe an observer 
	virtual void notify(); // ask each subscribed observer to update itself 

protected: 
	Subject() {} 
	
private: 
	std::list<Observer *> observers_; // list of observers
};


#endif