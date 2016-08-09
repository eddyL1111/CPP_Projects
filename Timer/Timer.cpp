#include "Timer.h"


/** Timer's Constructor. */
Timer::Timer(Subject* sub) : sub_(sub){
	Timer::sec_ = 0;
	Timer::ticking_ = false; 
	
	std::thread timerThread(&Timer::run, this);
	timerThread.detach();
}

/** Starts the timer. */
void Timer::start() {
	Timer::ticking_ = true;
}

/** Stops the timer. */
void Timer::stop() {
	Timer::ticking_ = false;
}

/** Resets the timer to 0 seconds. */
void Timer::reset() {
	Timer::sec_ = 0;
}

/** Gets and the returns number of seconds elapsed. */
unsigned long Timer::get() const { 
	return Timer::sec_;
}

/** Runs the timer; when it's ticking, the timer increases 
*	at each second.
*/
void Timer::run() { // function executed by thread (see below)
	while(1) {
		if(ticking_) {
			Timer::sub_->notify();
			sleep(1);
			++Timer::sec_;
		}
	}
}

/** Starts, stops, or resets according to the command */
void Timer::update(Subject *sub) {
	KeyboardController *kc = static_cast<KeyboardController *>(sub);
	std::string cmd = kc->getCommand(); 
	
	
	if (cmd == "s") Timer::start();
	if (cmd == "h") Timer::stop();
	if (cmd == "r") Timer::reset();

}