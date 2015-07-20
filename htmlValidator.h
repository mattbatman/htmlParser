// Matt Batman
// CSCI 202, Computer Science III
// Final Project
// htmlValidator.h

#ifndef HTMLVALIDATOR_H
#define HTMLVALIDATOR_H

#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "htmlTag.h"

class htmlValidator: public htmlTag
{
public:
	void printOpeningTagsAndLines() const;
	  //prints the contents of openingTagsAndLines to the screen
	  //separated by a space

	void printClosingTagsAndLines() const;
	  //prints the contents of closingTagsAndLines to the screen
	  //separated by a space

	void printUnmatchedTagsAndLines() const;
	  //prints the contents of openingTagsAndLines to the screen
	  //separated by a space

	void printUnmatchedTagsAndLinesAndWord() const;
	  //prints the contents of openingTagsAndLines to the screen
	  //separated by a space

	void setIgnoreTags();
	  //called by constructor
	  //opens file called "ignore.txt"
	  //and adds the tags to ignoreTags member list

	void removeIgnoreTags();
	  //called by readFileByLine()
	  //removes the tags in ignoreTags list from openingTagsAndLines and closingTagsAndLines lists
	  //uses standard function "erase" to repoint lists around the elements to remove

	void findUnmatchedTagsAndLines();
	  //fills member list unmatchedTagsByLine
	  //called by readFileByLine() after readFileByLine() calls removeIgnoreTags()
	  //copies closingTagsByLine to a temporary list, removing the backslash '/'
	  //searches through each tag in openingTags for matching tag in temporary closing tag list
	  //if a corresponding opening tag is found in the temporary closing tag list
	  //the temporary closing tag list is "repointed" around that element
	  //if a corresponding tag is not found, that element of the openingTagsByLne member is added to unmatchedTagsByLine
	  //after the search of the openingTag list, a backslash is added back to any remaining elements
	  //in the temporary closing tag list and it's added to the end of the unmatched tag list
	 
	void readFileByLine();
	  //prompts user to enter a file name
	  //scans the file and passes appropriate values to member lists openingTags and closingTags
	  //reads file line by line until the end
	  //read line string by string until the end
	  //if the first characters of a string indicate a closing or opening tag, add it to the appropriate list
	    //along with the line number and approximate word count within the line
	  //also cycle through the string to find characters indicating a closing or opening tag, add it to the appropriate list
	  //calls "removeIgnoreTags" and "findUnmatchedTagsByLine"
	  //when "adding to the appropriate list," a copy of the string is made and unnecessary characters are deleted
	    //from the copy before adding

	void createOutputFile();
	  //creates a file called "output.txt"
	  //prints the opening tags detected, closing tags detected, and unmatched tags

	htmlValidator();
	  //constructor
	  //creates each of the four member lists
	  //calls setIgnoreTags()

	~htmlValidator();
	  //destructor

private:
	std::list<std::string> ignoreTags; //list of tags as strings to ignore when looking for unmatched tags
	std::list<htmlTag> openingTagsAndLines; //list of opening tags found (as htmlTag objects)
	std::list<htmlTag> closingTagsAndLines; //list of closing tags found (as htmlTag objects)
	std::list<htmlTag> unmatchedTagsAndLines; //list of unmatched tags found (as htmlTag objects)

};

#endif