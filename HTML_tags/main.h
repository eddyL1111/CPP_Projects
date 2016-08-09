/** 
Name: Eddy Lau
*/

#ifndef MAIN_H
#define MAIN_H

#include <iostream> 
#include <fstream>
#include <map>
#include <sstream>
#include <regex>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

string assignEscapeCode(const string& value);
void replaceGreaterThan(string& line);
void replaceLessThan(string& line);
map<string,string> storeConfig(ifstream& is);
string validateEscapeCode(const string& value);
bool applyTagIfValid(string& line, const vector<string>& tagOrder, map<string,string>& config);
bool checkTextTag(const vector<string>& tagOrder, const string& line);
bool isValidEscapeCode(const string& escCode) ;
bool isValidTagName(const string& tagName);
bool checkMatchingTagNames(const vector<string>& vTag, map<string,string>& config);
bool applyTagIfValid(string& line, const vector<string>& tagOrder, map<string,string>& config);



#endif