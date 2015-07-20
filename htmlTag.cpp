// Matt Batman
// CSCI 202, Computer Science III
// Final Project
// htmlTag.cpp

#include "htmlTag.h"

using namespace std;



//BEGIN CLASS htmlTag FUNCTION DEFINITIONS



//getTag
string htmlTag::getTag() const
{
	return htmlTagType;
}
//end getTag



//getLineNumber
int htmlTag::getLineNumber() const
{
	return tagLineNumber;
}
//end getLineNumber



//getWordNumber
int htmlTag::getWordNumber() const
{
	return wordNumber;
}
//end getWordNumber



//constructor
htmlTag::htmlTag(string tag, int lineNumber, int wordNo)
{
	htmlTagType = tag;
	tagLineNumber = lineNumber;
	wordNumber = wordNo;
}
//end constructor



//default constructor
htmlTag::htmlTag()
{
	htmlTagType = " ";
	tagLineNumber = 0;
}
//end constructor



//destructor
htmlTag::~htmlTag()
{
}
//end destructor



//END CLASS htmlValidator FUNCTION DEFINITIONS