#ifndef MINSECVIEW_H
#define MINSECVIEW_H

#include "TimerView.h"

#include <math.h>
#include <iomanip>


/** This class displays/outputs the time in 0:00 format. */
class MinSecView: public TimerView
{
public:
	MinSecView(Timer *timer): TimerView(timer) {}
	void display(std::ostream& os) const;
	
	// Inherited from TimerView -> Observer class
	void update(Subject *);	
};



/** Displays time in 0:00 format. */
inline 
void MinSecView::display(std::ostream& os) const {
	unsigned long getSec = TimerView::timer_->get();
	
	unsigned long min = getSec;
	unsigned long sec = getSec;
	
	min /= 60; 
	sec %= 60;
	
	os << floor(min) << ":" << std::setfill('0') << std::setw(2) 
		<< sec << std::endl;
}

/** Updates the timer periodically. */
inline 
void MinSecView::update(Subject *sub) {
	MinSecView::display(std::cout);
	if(sub == nullptr) return;
}

#endif