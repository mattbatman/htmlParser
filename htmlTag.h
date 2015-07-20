// Matt Batman
// CSCI 202, Computer Science III
// Final Project
// htmlTag.h

#ifndef HTMLTAG_H
#define HTMLTAG_H

#include <iostream>
#include <string>

class htmlTag
{
public:
	std::string getTag() const;
	  //returns htmlTagType

	int getLineNumber() const;
	  //returns tagLineNumber

	int getWordNumber() const;
	  //returns wordNumber

	htmlTag(std::string, int, int);
	  //constructor

	htmlTag();
	  //default constructor

	~htmlTag();
	  //destructor

private:
	std::string htmlTagType; // ie. "<p>" "</p>" "<h1>"
	int tagLineNumber; // the line of the file from which the tag was pulled
	int wordNumber; // the approximate count of the word from within the line that the tag was pulled
};

#endif