PROGRAM INTENTIONS

This was created as a final project for a "computer science III" class.

The goal of this project was to create a rudimentary HTML parser -- a program
that could detect opened tags that weren't closed, or closed tags that were
never opened.

The program prompts the user to enter an html file, and writes all results
to output.txt.

INCLUDED FILES

main.cpp - test program
htmlValidator.h - function declarations of htmlValidator
htmlValidator.cpp - function definitions of class htmlValidator
htmlTag.h - function declarations of class htmlTag
htmlTag.cpp - function definitions of class htmlTag
ignore.txt - holds list of tags that are to be ignored for consideration of an unmatched tag