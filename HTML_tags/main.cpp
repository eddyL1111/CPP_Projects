/** 
Name: Eddy Lau
*/

#include "main.h"

/** This program simulates how to format sections of text as in HTML, 
using tags as mark-ups. */
int main(int argc, char * argv[]) {
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " [srcfile] /n ";
		return 1; 
	}
	ifstream in(argv[1], ios_base::in|ios_base::binary);
	if(!in) {
		cerr << "unable to open " << argv[1] << endl; 
		return 2; 
	}	
	
	
	string line1 ("<text>Read these instructions <italic>carefully</italic>. This is a closed-book"
		" exam. There are 6 questions with a total of 25 marks. Answer <bold>all</bold>" 
		" questions. Time allowed: <underline>80 minutes</underline>.</text>"
	);
	string line2 ("<text>Read this is a closed-book 2" 
		"  <bold> if 2 &gt; 3 </bold> whatever" 
		" </text>"
	);
	string line3 ("<text>this <bold>is a <italic>short</bold> simple </italic>test</text>");
	

	string line;
	// Read the user input. Can be tested with input redirection
	char c;
	while(cin.get(c)) {
		line += c;
	}
	
	regex re(R"(\<(.+?)\>)"); // Regex for any type of <...> tags
	smatch sm;
	vector<string> tagOrder; // container for order of tag found in string
	map<string,string> config = storeConfig(in);
		
	
	#ifdef DEBUG
		cout << "*** In DEBUG Mode ***" << endl;
		auto it = config.find("text");
		
		if(it == config.end()) {
			cerr << "The text tag was not found" << endl;
		} else {
			string escCode = it->second;	
			for(auto x: config) {
				cout << x.second << x.first << escCode << endl;	
			}
		}		
		cout << "---------------------" << endl;
		
	#endif
	
	
	
	// Stores tags in order found from beginning of the paragraph to the end
	for(auto it = line.cbegin(), end = line.cend();
		regex_search(it,end,sm,re); it = sm.suffix().first)
	{
		// tags are stored without the '<' and '>'
		// eg. "bold", "/bold" and not like "<bold>", "</bold>"
		tagOrder.push_back(sm.str(1)); 
	}	
	
	if(!checkTextTag(tagOrder, line) || !checkMatchingTagNames(tagOrder, config)) {
		return 0;
	}
	
	if(applyTagIfValid(line, tagOrder, config)) {
		replaceLessThan(line);
		replaceGreaterThan(line);		
		cout << endl << line << endl;
	}
}



/** Replaces the tags and colours the text after the tag depending of the tag. */
bool applyTagIfValid(string& line, const vector<string>& tagOrder, map<string,string>& config) {
	vector<string> tempVec;
	
	for(auto it=tagOrder.begin(); it != tagOrder.end();	++it) {
		string str = *it;
		regex tempRe("<"+str+">");

		// If it's not an end tag, store in container to have a reference for
		// the previous tag, and replace the tag with the escape code
		if(str[0] != '/') {	
			tempVec.emplace_back(*it);
			line = regex_replace(line, tempRe, config[str], regex_constants::format_first_only);
		}
		else // If it's an end tag, revert colour to previous tag
		{
			auto it2 = tempVec.end()-1;
			string prevTag = *it2;
			string currTag = *it;
			currTag.erase(currTag.begin());
			// If the end tag is not the same type as the previous one, it's an error
			if(currTag != prevTag) {
				//reverts back to the starting colour
				line = regex_replace(line, tempRe, config["text"]); 
				//cout << line << endl;
				cerr << "ERROR: end tag mismatch - <" << prevTag << ">" << " <" << *it << ">" << endl;			
				return false;
			}
			if(!tempVec.empty()) {
				tempVec.pop_back(); // Deletes the starting tag of the current end tag in the container
			}
			if(!tempVec.empty()) {
				line = regex_replace(line, tempRe, config[tempVec.back()], regex_constants::format_first_only); // Highlight text
			}			
		}
		
		if(it == tagOrder.end()-1) {
			line = regex_replace(line, tempRe, ""); // Deletes the last ending tag
		}	
	}// for
	// Searches for '<' or '>' that are not tag related
	regex reGtLt (R"(>|<)");
	if(regex_search(line.begin(), line.end(), reGtLt)==1) {
		cerr << "ERROR: '<' or '>' must be written as '&lt' or '&gt' respectively" << endl;
		return false;
	}
	
	return true;
}


/** Replaces the '&gt' with '>' of the line from input text. */
void replaceGreaterThan(string& line) {
	regex re(R"(&gt;)");
	line = regex_replace(line, re, ">");
}


/** Replaces the '&lt' with '<' of the line from input text. */ 
void replaceLessThan(string& line) {
	regex re(R"(&lt;)");
	line = regex_replace(line, re, "<");
}


/** Validating the text tag, which should be the first word and 
the ending tag should be last word. Also, text is a must have. */ 
bool checkTextTag(const vector<string>& tagOrder, const string& line) {
	int textTagCounter = 0;
	string text("<text>"), endText("</text>");
	
	// Checks if the first word is "<text>"
	for(auto it = line.cbegin(); it != line.cend(); ++it) {
		if(isspace(*it)) {
			continue;
		}
		else if (*it == '<') // If there are spaces, then check 
		{										// if the first word is <text>
			for(auto it2 = it, bIt = text.cbegin(); 
				bIt != text.cend(); ++it2, ++bIt) 
			{
				if(*it2 != *bIt) {
					cerr << "ERROR: first word is not <text>" << endl;
					return false;
				}	
			}
			break;
		}
		else {
			cerr << "ERROR: first word is not <text>" << endl;
			return false;
		}
		return true;
	}
	//Checks if the last word is "</text>"
	for(auto reIt = line.crbegin(); reIt != line.crend(); ++reIt) 
	{
		if(isspace(*reIt)) {
			continue;
		} 
		else if(*reIt == '>') // if there are no ending spaces, check 
		{											// if the last word is </text>
			for(auto reIt2 = reIt, endReIt = endText.crbegin();
				endReIt != endText.crend(); ++reIt2, ++endReIt) 
			{
				if(*reIt2 != *endReIt) {
					cerr << "ERROR: last word is not </text>" << endl;
					return false;
				}	
			}
			break;
		} else {
			cerr << "ERROR: last word is not </text>" << endl;
			return false;
		}
	}
	// Checks if there's only text tag, excluding its end tag
	for(const auto& t : tagOrder) {
		if(t == "text") {
			textTagCounter++;
		}
		if(textTagCounter > 1) {
			cerr << "ERROR: only one text tag with ending tag allowed" << endl;
			return false;
		}
	}
	// There must be 1 text tag
	if(textTagCounter != 1) {
		cerr << "ERROR: text tag is a must have" << endl;
		return false;
	}
	
	return true;
}


/** Validating the tag name; can't contain spaces and it's made out of 
alphanumeric. */
bool isValidTagName(const string& tagName) {
	// Checks if the tag name is made up of alphanumeric characters
	for(auto it = tagName.cbegin(); it != tagName.end(); ++it) {
		if(!isalpha(*it) && !isdigit(*it)) {
			cerr << "ERROR: tag name must be only alphanumeric" << endl;
			return false;
		}
	}
	
	return true;
}


/** Checks if tag names taken from the input text are identified in the config.txt 
and they should not have spaces. */
bool checkMatchingTagNames(const vector<string>& vTag, map<string,string>& config) {
	
	// Checks for unknown tags that aren't in config.txt	
	for(auto& t : vTag) {
		string tagName = t;		
		if(tagName.front() == '/') { // Treat ending tags as starting tags
			tagName.erase(tagName.begin());
		}
		auto it = config.find(tagName);
		if(it == config.end()) { // Looking for the not-matching tags
			cerr << "ERROR: Unknown tag name -- " << tagName << endl;
		}
	}
	
	// Checks if the tag name has spaces
	for(auto it = vTag.cbegin(); it != vTag.end(); ++it) {
		string tagName = *it;
		if(isspace(tagName.front()) != isspace(tagName.back())) {
			cerr << "ERROR: tag name can't have spaces -- " << tagName << endl;
			return false;
		}
	}

	return true;
}


/** Validating the escape code, which is the second word from a read line. */
bool isValidEscapeCode(const string& escCode) {
	if(escCode[0] != '\\' && escCode[1] != 'e') {
		cerr << "ERROR: escape code doesn't start with '\\e'" << endl;
		return false;
	}
	
	return true;
}


/** After storing the configuration tags in a map, assign the proper escape code */
string assignEscapeCode(const string& value) {
	if(value.compare("\\e[0;30m") == 0) return "\033[0;30m"; //  # black
	if(value.compare("\\e[0;31m") == 0) return "\033[0;31m"; //  # red
	if(value.compare("\\e[0;32m") == 0) return "\033[0;32m"; //  # green
	if(value.compare("\\e[0;33m") == 0) return "\033[0;33m"; //  # brown
	if(value.compare("\\e[0;34m") == 0) return "\033[0;34m"; //  # blue
	if(value.compare("\\e[0;35m") == 0) return "\033[0;35m"; //  # purple
	if(value.compare("\\e[0;36m") == 0) return "\033[0;36m"; //  # cyan
	if(value.compare("\\e[0;37m") == 0) return "\033[0;37m"; //  # grey
	if(value.compare("\\e[39;49m") == 0) return "\033[39;49m"; //  # text
	
	return "\033[0;37m"; // normal text # grey
}


/** Validating and checks if line has more than 1 word. */
bool isValidConfigFile(const string& line) {
	int countWords = 1;

	for(auto it = line.cbegin(), it2 = line.cbegin()+1; it2 != line.cend(); ++it, ++it2) {
		if(!isspace(*it) && isspace(*it2)) {
			countWords++;
		}
	}
	if(countWords <= 1) {
		cerr << "ERROR: line is too short" << endl;
		return false;
	}

	return true;
}


/** Reads the config.txt file and stores it in a map(tagName, escCode) if its valid. */
map<string,string> storeConfig(ifstream& is) {
	map<string,string> config;
	string line;
	string key; // tag name
	string value; // escape code
	
	// Reads line from file and stores the 
	// first two words in the line, key and value.
	while(getline(is, line)) {
		if(!isValidConfigFile(line)) {
			//cout << "Skipped" << endl;
			continue;
		}
		
		istringstream iss(line); 
		
		iss >> key;
		auto findIt = config.find(key);
		if(findIt != config.end()) { // Skip reassigning a tag that was already mapped
			continue;
		}
		if(!isValidTagName(key)) {
			//cout << "Skipped" << endl;
			continue;
		}		
		iss >> value;
		if(isValidEscapeCode(value)) { // If all conditions meet, assign the proper
			config[key] = assignEscapeCode(value); // escape code colour
		}
		
	}
	
	return config;
}

