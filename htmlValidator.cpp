// Matt Batman
// CSCI 202, Computer Science III
// Final Project
// htmlValidator.cpp

#include "htmlValidator.h"

using namespace std;



//BEGIN CLASS htmlValidator FUNCTION DEFINITIONS

//printOpeningTagsAndLines
void htmlValidator::printOpeningTagsAndLines() const
{
	cout << "Opening tags and lines: " << endl;
	//iterator code from stack overflow http://stackoverflow.com/questions/6561567/how-do-i-access-objects-in-a-linked-list-in-c
	for (list<htmlTag>::const_iterator i = openingTagsAndLines.cbegin(); i != openingTagsAndLines.cend(); ++i)
	{
		cout << i->getTag() << " " << i->getLineNumber() << " ";
	}
}
//end printOpeningTagsAndLines



//printClosingTagsAndLines
void htmlValidator::printClosingTagsAndLines() const
{
	cout << "Closing tags and lines: " << endl;
	//stack overflow http://stackoverflow.com/questions/6561567/how-do-i-access-objects-in-a-linked-list-in-c
	for (list<htmlTag>::const_iterator i = closingTagsAndLines.cbegin(); i != closingTagsAndLines.cend(); ++i)
	{
		cout << i->getTag() << " " << i->getLineNumber() << " ";
	}
}
//end printClosingTagsAndLines



//printUnmatchedTagsAndLines
void htmlValidator::printUnmatchedTagsAndLines() const
{
	cout << "Unmatched tags and lines: " << endl;
	//stack overflow http://stackoverflow.com/questions/6561567/how-do-i-access-objects-in-a-linked-list-in-c
	for (list<htmlTag>::const_iterator i = unmatchedTagsAndLines.cbegin(); i != unmatchedTagsAndLines.cend(); ++i)
	{
		cout << i->getTag() << " " << i->getLineNumber() << " ";
	}
}
//end printUnmatchedTagsAndLines



//printUnmatchedTagsAndLinesAndWords
void htmlValidator::printUnmatchedTagsAndLinesAndWord() const
{
	cout << "Unmatched tags and lines: " << endl;
	//stack overflow http://stackoverflow.com/questions/6561567/how-do-i-access-objects-in-a-linked-list-in-c
	for (list<htmlTag>::const_iterator i = unmatchedTagsAndLines.cbegin(); i != unmatchedTagsAndLines.cend(); ++i)
	{
		cout << i->getTag() << " " << i->getLineNumber() << " " << i->getWordNumber();
	}
}
//end printUnmatchedTagsAndLinesAndWords



//setIgnoreTag
void htmlValidator::setIgnoreTags()
{
	ifstream infile;

	string tag;

	infile.open("ignore.txt");

	if (!infile)
	{
		cout << "The ignore file could not be opened";
		return;
	}

	while (infile >> tag)
	{
		ignoreTags.push_back(tag);
	}

	infile.close();

}
//end setIgnoreTag



//removeIgnoreTags
void htmlValidator::removeIgnoreTags()
{
	string removeMe;

	//stack overflow http://stackoverflow.com/questions/6561567/how-do-i-access-objects-in-a-linked-list-in-c
	for (list<string>::const_iterator i = ignoreTags.cbegin(); i != ignoreTags.cend(); ++i)
	{
		removeMe = *i;
		//cycle through each element on openingTagsListAndLines, "repointing" the list around the matching elements
		//loop from C++ Primer page 349, example of how to use function "erase" with a list
		auto iteratorSecondLoop = openingTagsAndLines.begin();
		while (iteratorSecondLoop != openingTagsAndLines.end())
		{
			if (iteratorSecondLoop->getTag() == removeMe) //if the inner loop and outer loop match AND found is set to false
			{
				iteratorSecondLoop = openingTagsAndLines.erase(iteratorSecondLoop);
			}
			else
			{
				++iteratorSecondLoop;
			}
		}//end nested while loop (inner loop 1)

		//cycle through each element on closingTagsAndLines, "repointing" the list around the matching elements
		auto iteratorThirdLoop = closingTagsAndLines.begin();
		while (iteratorThirdLoop != closingTagsAndLines.end())
		{
			if (iteratorThirdLoop->getTag() == removeMe)
			{
				iteratorThirdLoop = closingTagsAndLines.erase(iteratorThirdLoop);
			}
			else
			{
				++iteratorThirdLoop;
			}
		}//end nested while loop (inner loop 2)

	}//end outer for loop
}
//end removeIgnoreTags



//findUnmatchedTagsAndLines
void htmlValidator::findUnmatchedTagsAndLines()
{
	//declare many variables used within this function
	list<htmlTag> tempClosingTagsList;
	string tempClosingTagElement = " ";
	unsigned int tempClosingTagLine = 0;
	unsigned int tempTagWordNo = 0;
	bool found = false;

	//copy closingTags to tempClosingTagsList and remove the '/' character
	for (list<htmlTag>::const_iterator i = closingTagsAndLines.cbegin(); i != closingTagsAndLines.cend(); ++i)
	{
		tempClosingTagElement = i->getTag();
		tempClosingTagElement.erase(1, 1); //remove the '/' character
		tempClosingTagLine = i->getLineNumber();
		tempTagWordNo = i->getWordNumber();
		htmlTag tempHtmlTagObject(tempClosingTagElement, tempClosingTagLine, tempTagWordNo);
		tempClosingTagsList.push_back(tempHtmlTagObject); //add stripped tag to tempClosingTagsList
	}

	//iterate through openingTags list
	for (list<htmlTag>::const_iterator iterator = openingTagsAndLines.cbegin(); iterator != openingTagsAndLines.cend(); ++iterator)
	{
		//on each iteration of the openingTags list, reset found variable to false
		found = false;
		//cycle through each element on tempClosingTagsList, "repointing" the list around the first matching element
		//loop from C++ Primer page 349, example of how to use function "erase" with a list
		list<htmlTag>::const_iterator iteratorSecondLoop = tempClosingTagsList.cbegin();
		while (iteratorSecondLoop != tempClosingTagsList.cend())
		{	//REMINDER: if a tag is erased from this list, it means it was a valid tag
			if (iterator->getTag() == iteratorSecondLoop->getTag() && found == false && iterator->getLineNumber() < iteratorSecondLoop->getLineNumber()) //if the inner loop and outer loop match AND found is set to false
			{
				iteratorSecondLoop = tempClosingTagsList.erase(iteratorSecondLoop);
				found = true; //set found to true for the duration of this outerloop cycle once a match has been found
			}
			else if (iterator->getTag() == iteratorSecondLoop->getTag() && found == false && iterator->getLineNumber() == iteratorSecondLoop->getLineNumber() && iterator->getWordNumber() < iteratorSecondLoop->getWordNumber())
			{
				iteratorSecondLoop = tempClosingTagsList.erase(iteratorSecondLoop);
				found = true; //set found to true for the duration of this outerloop cycle once a match has been found
			}
			else
			{
				++iteratorSecondLoop;
			}
		}//end nested while loop (inner loop)
		if (found == false) //if the tempClosingTagsList iteration made it through without a match
		{
			tempClosingTagElement = iterator->getTag();
			tempClosingTagLine = iterator->getLineNumber();
			tempTagWordNo = iterator->getWordNumber();
			htmlTag tempHtmlTagObject(tempClosingTagElement, tempClosingTagLine, tempTagWordNo);
			unmatchedTagsAndLines.push_back(tempHtmlTagObject); // add the opening tag to the unmatched list
		}
	}//end for

	//if anything is left in the tempClosingTagsList, add a '/' character back and push it on the unmatchedTags list
	for (list<htmlTag>::const_iterator i = tempClosingTagsList.cbegin(); i != tempClosingTagsList.cend(); ++i)
	{
		tempClosingTagElement = i->getTag();
		tempClosingTagElement.insert(1, "/");
		tempClosingTagLine = i->getLineNumber();
		tempTagWordNo = i->getWordNumber();
		htmlTag tempHtmlTagObject(tempClosingTagElement, tempClosingTagLine, tempTagWordNo); //create an object at the last second
		unmatchedTagsAndLines.push_back(tempHtmlTagObject); //add stripped tag to tempClosingTagsList
	}

	tempClosingTagsList.clear(); //clear the tempClosingTagsList before the function closes

	createOutputFile();

	cout << "\nYour file has been analyzed. See output.txt." << endl;
}
//end findUnmatchedTagsAndLines



//readFileByLine
void htmlValidator::readFileByLine()
{
	ifstream infile;
	char fileName[50];
	string line, textBlock;

	string potentialTag = " ";
	unsigned int lineNumber = 0;
	unsigned int wordNo = 0;

	//prompt the user for a file name
	cout << "Enter the name of the file to evaluate: ";
	cin >> fileName;
	cout << endl;

	//open the filename entered by the user
	infile.open(fileName);

	//if the file could not be opened
	if (!infile)
	{
		cout << "The file could not be opened...";
		return;
	}

	//while the end of the file has not been reached, get each line
	while (getline(infile, line))
	{
		lineNumber++; //track the line we're on
		wordNo = 0; //reset the word count of the line

		istringstream textBlock(line);

		//pull in each block of text in the line
		while (textBlock >> potentialTag)
		{
			//increment the word within the line that we're on
			wordNo++;

		//if a bracket and backslash are in the first and second position of the string
		//(add to closingTagsByLine)
		if (potentialTag[0] == '<' && potentialTag[1] == '/')
		{
			//create temp variable to block of text isn't destroyed
			string tempTag = potentialTag;

			//loop through each character, find the final bracket and erase everything that remains after said bracket in copied tempTag
			for (unsigned int i = 0; i < tempTag.length(); i++)
			{
				if (tempTag[i] == '>')
					tempTag.erase(i + 1, tempTag.length() - i);
			}
			htmlTag tagObject(tempTag, lineNumber, wordNo);
			closingTagsAndLines.push_back(tagObject);
		}//end closing tag in first loop

		//if the first character is an opening bracket and the second character is not the backslash
		//(add to openingTagsByLine)
		if (potentialTag[0] == '<' && potentialTag[1] != '/')
		{
			string tempTag = potentialTag;

			//look for the closing bracket
			for (unsigned int i = 0; i < tempTag.length(); i++)
			{
				if (tempTag[i] == '>')
				{
					tempTag.erase(i + 1, tempTag.length() - i + 1); //erase all characters after the closing bracket
				}
			}
			//add a closing bracket if it's not on the end
			if (tempTag[tempTag.length() - 1] != '>')
			{
				tempTag += '>';
			}

			htmlTag tagObject(tempTag, lineNumber, wordNo);
			openingTagsAndLines.push_back(tagObject);
		}//end opening tag in first loop

		//cycle through everything pulled in by tag
		//(to find tags that weren't in the first position of the block of text)
		for (unsigned int i = 0; i != potentialTag.length(); i++)
		{
			// if a bracket and backslash are found next to each other in any other position than 0 and 1
			if (potentialTag[i + 1] == '/' && potentialTag[i] == '<' && i != 0)
			{
				string tempTag = potentialTag;

				//erase everything before the bracket
				tempTag.erase(0, i);

				//find the final bracket and erase everything that remains
				for (unsigned int i = 0; i < tempTag.length(); i++)
				{
					if (tempTag[i] == '>')
						tempTag.erase(i + 1, tempTag.length() - i);
				}
				wordNo++;//increment the word within the line that we're on
				htmlTag tagObject(tempTag, lineNumber, wordNo);
				closingTagsAndLines.push_back(tagObject);
			}//end if, for still ongoing

			// if a forwards and backwards bracket are found next to each other in any other position than 0 and 1
			if (potentialTag[i + 1] == '<' && potentialTag[i] == '>' && potentialTag[i + 2] != '/')
			{
				string tempTag = potentialTag;
				//erase everything before the bracket
				tempTag.erase(0, i + 1);
				//find the final bracket and erase everything that remains
				for (unsigned int i = 0; i < tempTag.length(); i++)
				{
					if (tempTag[i] == '>')
						tempTag.erase(i + 1, tempTag.length() - i);
				}
				//add a closing bracket if it's not on the end
				if (tempTag[tempTag.length() - 1] != '>')
				{
					tempTag += '>';
				}
				wordNo++;//increment the word within the line that we're on
				htmlTag tagObject(tempTag, lineNumber, wordNo);
				openingTagsAndLines.push_back(tagObject);
			}//end if
		}// end for
		}// end while(textBlock >> potentialTag)
	}//end while(getline(infile, line))

	infile.close();

	removeIgnoreTags();

	findUnmatchedTagsAndLines();
}
//end readFileByLine



//createOutputFile
void htmlValidator::createOutputFile()
{
	ofstream outputfile;

	outputfile.open("output.txt");

	outputfile << "WELCOME TO OUTPUT.TXT";
	outputfile << endl;
	outputfile << endl;
	outputfile << endl;

	if (unmatchedTagsAndLines.empty())
	{
		outputfile << "What a relief! You had no unmatched tags.";
	}
	else
	{
		outputfile << "Here are your unmatched tags and the line number of the violator: " << endl;
		outputfile << endl;
		//stack overflow http://stackoverflow.com/questions/6561567/how-do-i-access-objects-in-a-linked-list-in-c
		for (list<htmlTag>::const_iterator i = unmatchedTagsAndLines.cbegin(); i != unmatchedTagsAndLines.cend(); ++i)
		{
			outputfile << i->getTag() << " from line " << i->getLineNumber() << endl;
		}

	}//end else

	outputfile << endl;
	outputfile << endl;
	outputfile << endl;

	outputfile << "DEBUGGING" << endl;
	outputfile << "Here were the non-ignored opening tags, line numbers, and approximate word number on the line: " << endl;
	//stack overflow http://stackoverflow.com/questions/6561567/how-do-i-access-objects-in-a-linked-list-in-c
	for (list<htmlTag>::const_iterator i = openingTagsAndLines.cbegin(); i != openingTagsAndLines.cend(); ++i)
	{
		outputfile << i->getTag() << " from line " << i->getLineNumber() << " in position " << i->getWordNumber() << endl;
	}

	outputfile << endl;

	outputfile << "Here were the non-ignored closing tags, line numbers, and approximate word number on the line: " << endl;
	//stack overflow http://stackoverflow.com/questions/6561567/how-do-i-access-objects-in-a-linked-list-in-c
	for (list<htmlTag>::const_iterator i = closingTagsAndLines.cbegin(); i != closingTagsAndLines.cend(); ++i)
	{
		outputfile << i->getTag() << " from line " << i->getLineNumber() << " in position " << i->getWordNumber() << endl;
	}

	outputfile.close();
}
//end createOutputFile


//constructor
htmlValidator::htmlValidator()
{
	list<string> ignoreTags;
	list<htmlTag> openingTagsAndLines;
	list<htmlTag> closingTagsAndLines;
	list<htmlTag> unmatchedTagsAndLines;

	setIgnoreTags();

}
//end constructor

//destructor
htmlValidator::~htmlValidator()
{
}
//end destructor

//END CLASS htmlValidator FUNCTION DEFINITIONS