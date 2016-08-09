#ifndef SECVIEW_H
#define SECVIEW_H 

#include "TimerView.h"

#include <iostream>


/** This class displays/output the time in seconds format. */
class SecView: public TimerView 
{
public:
	SecView(Timer *timer): TimerView(timer) {}
	void display(std::ostream& os) const;
	
	// Inherited from TimerView -> Observer class
	void update(Subject *);
};


/** This class displays/outputs the time in seconds format. */
inline 
void SecView::display(std::ostream& os) const {
	// std::cout << "SecView display()" << std::endl;
	unsigned long sec = TimerView::timer_->get();
	os << sec << std::endl;
}

/** Updates the timer periodically. */
inline 
void SecView::update(Subject *sub) {
	SecView::display(std::cout);
	if(sub == nullptr) return;
}


#endif