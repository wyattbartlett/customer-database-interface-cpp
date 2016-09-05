/*****************************************************************
 // Name:           Wyatt Bartlett
 //
 // Homework:       Project 2
 //
 // Class:          ICS 212
 //
 // Instructor:     Ravi Narayan
 //
 // Date:           April 26, 2016
 //
 // File:           llist.h
 //
 // Description:    This file contains the function prototypes and member
 //                 variables for the llist class.
 //
 //***************************************************************/

#ifndef H_LLIST
#define H_LLIST
#include <ostream>
#include "record.h"

class llist {
private:
    record * start; /*a record pointer to the start of the Linked List*/
    char filename[16];
    int readfile();
    int writefile();
    record * reverse(record *);
    void cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord(int, char[], char[], int);
    int printRecord(int);
    int modifyRecord(int, char[]);
    void printAll();
    int deleteRecord(int);
    void reverse();
    friend std::ostream& operator<<(std::ostream&, llist&);
};

#endif /* #ifndef H_LLIST */
