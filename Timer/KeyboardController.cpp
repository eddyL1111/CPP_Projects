#include "KeyboardController.h"



/** Key Controller notifies all subscribed observers in the 
*	Subject list when a command is input.
*/
void KeyboardController::start() {
	while(std::getline(std::cin, KeyboardController::cmd_)) {
		if(KeyboardController::cmd_ == "s") {
			Subject::notify();
		}
		if(KeyboardController::cmd_ == "h") {
			Subject::notify();
		}
		if(KeyboardController::cmd_ == "r") {
			Subject::notify();			
		}
	}
	
}

/** Gets the currently input command. */
std::string KeyboardController::getCommand() const {
	return KeyboardController::cmd_;
}