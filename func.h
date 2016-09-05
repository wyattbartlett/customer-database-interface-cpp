/*****************************************************************
 // Name:        Wyatt Bartlett
 //
 // Homework:    Project 2
 //
 // Class:       ICS 212
 //
 // Instructor:  Ravi Narayan
 //
 // Date:        April 26, 2016
 //
 // File:        func.h
 //
 // Description: The file contains the prototypes for the Project 2 functions.
 //
 //***************************************************************/

#ifndef H_FUNC
#define H_FUNC

#include "llist.h"

int isListEmpty(llist&);
void displayMenu();
int getChoice();
int getAccountNo();
void getName(char[], int);
void getfield(char[], int);
int getBirthYear();
void removeTrailingSpace(char string[]);
void eatTrash();

#endif /* #ifndef H_FUNC */
