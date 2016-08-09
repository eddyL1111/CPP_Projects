#include <iostream> 

#include "Subject.h"
#include "KeyboardController.h"
#include "Observer.h"
#include "Timer.h"
#include "TimerView.h"
#include "SecView.h"
#include "TickView.h"
#include "MinSecView.h"



using namespace std;

int main() {
	
	// Creates keyboard controller
	KeyboardController kc;
	Subject *pSub = &kc;
	
	// Creates timer object
	Timer timer(pSub);
	Timer *pTimer = &timer;
	
	
	// Create 3 views of the timer object
	SecView secView(pTimer);
	TimerView *sec_timerView = &secView;
	
	
	MinSecView minSecView(pTimer);
	TimerView *minSec_timerView = &minSecView;
	
	TickView tickView(pTimer);
	TimerView *tick_timerView = &tickView;
	
	// Create observers and subscribe
	Observer *obs0 = &timer;
	Observer *obs1 = sec_timerView; 
	Observer *obs2 = minSec_timerView; 
	Observer *obs3 = tick_timerView; 

	pSub->subscribe(obs0);
	pSub->subscribe(obs1);
	pSub->subscribe(obs2);
	pSub->subscribe(obs3);
	
	// Starts getting the keyboard command
	kc.start();
	
	
	// Unsubscribing each observer 
	pSub->unsubscribe(obs0);
	pSub->unsubscribe(obs1);	
	pSub->unsubscribe(obs2);	
	pSub->unsubscribe(obs3);	
}
