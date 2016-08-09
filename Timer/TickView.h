#ifndef TICKVIEW_H
#define TICKVIEW_H  

#include "TimerView.h"

#include <iostream>


/** This class displays/output the time in '*' format. */
class TickView: public TimerView 
{
public:
	TickView(Timer *timer): TimerView(timer) {}
	void display(std::ostream& os) const;
	
	// Inherited from TimerView -> Observer class
	void update(Subject *);
};


/** This class displays/outputs the time in '*' format. */
inline 
void TickView::display(std::ostream& os) const {
	os << "*" << std::endl;
}

/** Updates the timer periodically. */
inline 
void TickView::update(Subject *sub) {
	TickView::display(std::cout);
	if(sub == nullptr) return;
}


#endif