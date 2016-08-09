#include "Subject.h"


/** Subscribes an Observer in the subject's list. */
void Subject::subscribe(Observer *obs) { 
	Subject::observers_.emplace_back(obs);
}

/** Un-subscribes an Observer in the subject's list. */
void Subject::unsubscribe(Observer *obs) { 
	Subject::observers_.remove(obs);
}

/** Notifies each subscribed observer to update itself. */
void Subject::notify() { // ask each subscribed observer to update itself 
	for(auto& o : Subject::observers_) {
		o->update(this);
	}
}
