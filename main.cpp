// Matt Batman
// CSCI 202, Computer Science III
// Final Project
// main.cpp

/*

PROGRAM GOAL

The goal of this program is to be able to read an HTML document and output any 1) opened but unclosed tags or 2)
closed but unopened tags. Such tags are deemed "unmatched."

PROJECT INDEX

Program Files

main.cpp          - test program
htmlValidator.h   - function declarations of htmlValidator
htmlValidator.cpp - function definitions of class htmlValidator
htmlTag.h		  - function declarations of class htmlTag
htmlTag.cpp		  - function definitions of class htmlTag

Other Input Files

ignore.txt        - list of tags held externally from this project (but read by the program) that are to be ignored
                    for consideration of an unmatched tag
index.html        - the user will be prompted to enter an html file to analyze. index.html has been provided as a
                    default.

Output Files

output.txt        - created as the output from running this program. placed in the same folder directory as
                    the project file

					learning point for presentation: unsigned int vs int with length() (returns unsigned int)
*/

#include <iostream>
#include <string>
#include "htmlValidator.h"

using namespace std;

/*

Explanation of Main.cpp

The test program creates an htmlValidator object (which contains lists of objects of type htmlTag) and calls function
readFileByLine to "do everything else" (prompt the user for an input html file, call other functions to create the
list of unmatched tags, create output.txt, etc.).

Function "outputScreenPause" just pauses the command prompt screen until the user enters "-1" and exits
the program.

*/

void outputScreenPause();

int main()
{
	//create html tag list object
	htmlValidator htmlListObject;

	//from class htmlValidator
	htmlListObject.readFileByLine();

	// pause output screen, definition below
	outputScreenPause();
	
	return 0;

}//end main


//this is a piece of code I found on stack overflow and used all semester
void outputScreenPause()
{
	int userExit = 0;
	while (userExit != -1)
	{
		cout << "\nEnter -1 to quit: ";
		cin >> userExit;
		while (cin.fail())
		{
			cout << "\nEnter -1...";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> userExit;
		}
	}
}