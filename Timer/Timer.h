#ifndef TIMER_H
#define TIMER_H 

#include "Observer.h"
#include "Subject.h"
#include "KeyboardController.h"

#include <thread> 
#include <atomic>
#include <unistd.h>
#include <iostream>
#include <string>


/** This class represents a timer. */
class Timer: public Observer, public Subject
{
public:
	Timer(Subject *);
	
	void start(); // start the timer
	void stop(); // stop the timer
	void reset(); // reset timer to 0
	unsigned long get() const; // returns number of seconds elapsed
	
	Timer(const Timer&) = delete; // (*)
	Timer& operator=(const Timer&) = delete; // (*)
	
	// Inherited from Observer class
	virtual void update(Subject *s); 
	
private:
	std::atomic_ulong sec_; // number of seconds elapsed
	std::atomic_bool ticking_; // is timer ticking or not?
	
	void run(); // function executed by thread (see below)
	
	// additional members if necessary
	Subject *sub_;
};


#endif