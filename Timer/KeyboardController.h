#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "Subject.h"

#include <iostream>
#include <string>


/** This class represents the Controller in the MVC */
class KeyboardController: public Subject 
{
public:
	void start(); // start the loop to get user commands
	std::string getCommand() const; // return the command
	
private:
	std::string cmd_;
};


#endif