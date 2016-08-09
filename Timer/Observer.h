#ifndef OBSERVER_H 
#define OBSERVER_H 


class Subject;

/** This class represents an Observer of keyboard. */
class Observer 
{ 
public: 
	virtual ~Observer() {} 
	virtual void update(Subject *) = 0; 

protected: 
	Observer() {} 
};


#endif
