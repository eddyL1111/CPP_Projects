#ifndef TIMERVIEW_H 
#define TIMERVIEW_H 

#include "Observer.h"

#include <string>
#include <iostream>

class Subject;
class Timer;

/** This abstract class */
class TimerView: public Observer 
{
public:
	TimerView(Timer *timer);
	virtual void display(std::ostream& os) const = 0;
	
	// Inherited from Observer class
	virtual void update(Subject *); 
	
protected:
	Timer *timer_;
};



/** TimerView's constructor. */
inline
TimerView::TimerView(Timer *timer): timer_(timer) {}

/** Updates the view. */
inline
void TimerView::update(Subject *sub) {
	if(sub == nullptr) return;
}


#endif