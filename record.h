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
 // Description: This file contains the definition for the struct record.
 //
 //***************************************************************/

#ifndef H_RECORD
#define H_RECORD

struct record {
    int accountno;
    char name[25];
    char address[80];
    int yearofbirth;
    struct record* next;
};

#endif /* #ifndef H_RECORD */
