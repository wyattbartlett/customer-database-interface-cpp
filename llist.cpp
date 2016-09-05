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
 // File:           llist.cpp
 //
 // Description:    This file contains the function definitions for the llist
 //                 class.
 //
 //***************************************************************/

/*Contains the function definitions for all the class member functions,
 * including the constructor and destructor. The constructor will initialize
 * the class variables. The destructor will deallocate the entire linked list.*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cerrno>
#include "record.h"
#include "func.h"
#include "llist.h"
using namespace std;

const int MAXADDRESS = 80;
const int MAXNAME = 25;

/*****************************************************************
 //
 // Function name:   llist
 //
 // DESCRIPTION:     A constructor for the llist class. This function
 //                  initializes the member variables of the Linked List.
 //
 // Parameters:      NONE
 //
 // Return values:   NONE
 //
 //****************************************************************/
llist::llist() {
#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: llist" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    this->start = NULL;
    strncpy((this->filename), "storage.txt", 12);
    readfile();
}

/*****************************************************************
 //
 // Function name:   llist
 //
 // DESCRIPTION:     A constructor for the llist class. This function
 //                  initializes the member variables of the Linked List.
 //
 // Parameters:      file (char[]) :     the name of the storage file
 //
 // Return values:   NONE
 //
 //****************************************************************/
llist::llist(char file[]) {
#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: llist" << endl;
    cout << "Parameters: file = " << file;
    cout << "\n";
    cout << "" << endl;
#endif

    this->start = NULL;
    strncpy((this->filename), file, 15);
    readfile();
}

/*****************************************************************
 //
 // Function name:   llist
 //
 // DESCRIPTION:     A destructor for the llist class. This function
 //                  deallocates the entire Linked List.
 //
 // Parameters:      NONE
 //
 // Return values:   NONE
 //
 //****************************************************************/
llist::~llist() {
#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: ~llist" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    writefile();
    cleanup();
}

/*****************************************************************
 //
 // Function name:   operator<<
 //
 // DESCRIPTION:     An overloaded output operator function. This function
 //                  prints all records that are held within the Linked List.
 //
 // Parameters:      os (ostream&) :        the ostream to which the Linked List
 //                                         will be printed
 //                  listref (llist&) :     the Linked List to be printed
 //
 // Return values:   Returns the ostream that was passed as a parameter.
 //
 //****************************************************************/
ostream& operator<<(ostream& os, llist& listref) {
    /*
     #ifdef DEBUG
     cout << "\n";
     cout << "**DEBUG**" << endl;
     cout << "Function name: operator<<" << endl;
     cout << "Parameters: os = " << os << ", listref = " << listref;
     cout << "\n";
     cout << "" << endl;
     #endif
     */

    if ((listref.start) != NULL) {
        struct record * currentRecord;
        currentRecord = (listref.start);

        while (currentRecord != NULL) {
            os << (*currentRecord).accountno << "\n";
            os << (*currentRecord).name << "\n";
            os << (*currentRecord).address << "\n";
            os << (*currentRecord).yearofbirth << "\n";
            os << "" << endl;
            currentRecord = (*currentRecord).next;
        }
    }
    return os;
}

/*****************************************************************
 //
 // Function name:   addRecord
 //
 // DESCRIPTION:     A database function. This function allows the user to add a
 //                  record to the Linked List.
 //
 // Parameters:      uaccountno (int) :     the account no. of the customer
 //                  uname (char []) :      the name of the customer
 //                  uaddr (char []) :      the address of the customer
 //                  uyob (int) :           the year of the customer's birth
 //
 // Return values:   0 if successful
 //                 -1 otherwise
 //
 //****************************************************************/
int llist::addRecord(int uaccountno, char uname[], char uaddr[], int uyob) {

    /* Create a record */
    struct record *newRecord = NULL;
    int found = -2;
    newRecord = new struct record;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: addRecord" << endl;
    cout << "Parameters: uaccountno = " << uaccountno
    << ", uname = " << uname
    << ", uaddr = " << uaddr
    << ", uyob = " << uyob;
    cout << "\n";
    cout << "" << endl;
#endif

    /* Fill the record */
    (*newRecord).accountno = uaccountno;
    strncpy((*newRecord).name, uname, MAXNAME);
    strncpy((*newRecord).address, uaddr, MAXADDRESS);
    (*newRecord).yearofbirth = uyob;
    (*newRecord).next = NULL;

    /* Find position and add the record to the Linked List */
    if ((this->start) == NULL) {
        (this->start) = newRecord;
        found = 0;
    } else if (((this->start)) != NULL) {
        struct record * currentRecord;
        currentRecord = (this->start);
        found = -2;

        if ((*newRecord).accountno <= (*(this->start)).accountno) {
            (*newRecord).next = (this->start);
            (this->start) = newRecord;
            found = 0;
        }

        while ((*currentRecord).next != NULL && found != 0) {

            if ((*newRecord).accountno
                    <= (*((*currentRecord).next)).accountno) {
                (*newRecord).next = (*currentRecord).next;
                (*currentRecord).next = newRecord;
                found = 0;
            }

            if ((*newRecord).accountno > (*((*currentRecord).next)).accountno) {
                currentRecord = (*currentRecord).next;
            }

        }

        if (found == -2) {
            (*currentRecord).next = newRecord;
            found = 0;
        }
    }
    return found;
}

/*****************************************************************
 //
 // Function name:   modifyRecord
 //
 // DESCRIPTION:     A database function. This function allows the user to
 //                  modify a record that is held within the Linked List.
 //
 // Parameters:      uaccountno (int) :     the account no. of the customer
 //                  input (char []) :      the user input to be used to update
 //                                         the appropriate field
 //
 // Return values:   0 if successful
 //                 -1 otherwise
 //
 //****************************************************************/
int llist::modifyRecord(int uaccountno, char input[]) {
    int found = 0;
    int done = 0;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: modifyRecord" << endl;
    cout << "Parameters: uaccountno = " << uaccountno
    << ", input = " << input;
    cout << "\n";
    cout << "" << endl;
#endif

    if ((this->start) != NULL) {
        struct record *currentRecord;
        currentRecord = (this->start);

        if ((*(this->start)).accountno == uaccountno) {

            while (currentRecord != NULL && done != 1) {
                if ((*currentRecord).accountno == uaccountno) {
                    strncpy((*currentRecord).address, input, 80);
                    currentRecord = (*currentRecord).next;
                    found = found + 1;
                } else {
                    done = 1;
                }
            }

        } else {
            if ((*currentRecord).next != NULL) {
                currentRecord = (*currentRecord).next;
                while (currentRecord != NULL) {
                    if ((*currentRecord).accountno == uaccountno) {
                        strncpy((*currentRecord).address, input, 80);
                        currentRecord = (*currentRecord).next;
                        found = found + 1;
                    } else if ((*currentRecord).accountno != uaccountno) {
                        currentRecord = (*currentRecord).next;
                    }
                }
            }
        }
    }
    return found;
}

/*****************************************************************
 //
 // Function name:   printRecord
 //
 // DESCRIPTION:     A database function. This function allows the user to print
 //                  a record that is held within the Linked List.
 //
 // Parameters:      uaccountno (int) :     the account no. of the customer
 //
 // Return values:   0 if successful
 //                 -1 otherwise
 //
 //****************************************************************/
int llist::printRecord(int uaccountno) {
    int found = 0;
    int done = 0;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: printRecord" << endl;
    cout << "Parameters: uaccountno = " << uaccountno;
    cout << "\n";
    cout << "" << endl;
#endif

    if ((this->start) != NULL) {
        struct record *currentRecord;
        currentRecord = (this->start);

        if ((*(this->start)).accountno == uaccountno) {

            while (currentRecord != NULL && done != 1) {
                if ((*currentRecord).accountno == uaccountno) {
                    cout << (*currentRecord).accountno << "\n";
                    cout << (*currentRecord).name << "\n";
                    cout << (*currentRecord).address << "\n";
                    cout << (*currentRecord).yearofbirth << "\n";
                    cout << "" << endl;
                    currentRecord = (*currentRecord).next;
                    found = found + 1;
                } else {
                    done = 1;
                }
            }

        } else {
            if ((*currentRecord).next != NULL) {
                currentRecord = (*currentRecord).next;
                while (currentRecord != NULL) {
                    if ((*currentRecord).accountno == uaccountno) {
                        cout << (*currentRecord).accountno << "\n";
                        cout << (*currentRecord).name << "\n";
                        cout << (*currentRecord).address << "\n";
                        cout << (*currentRecord).yearofbirth << "\n";
                        cout << "" << endl;
                        currentRecord = (*currentRecord).next;
                        found = found + 1;
                    } else if ((*currentRecord).accountno != uaccountno) {
                        currentRecord = (*currentRecord).next;
                    }
                }
            }
        }
    }
    return found;
}

/*****************************************************************
 //
 // Function name:   printAllRecords
 //
 // DESCRIPTION:     A database function. This function allows the user to print
 //                  all of the records that are held within the Linked List.
 //
 // Parameters:      NONE
 //
 // Return values:   NONE
 //
 //****************************************************************/
void llist::printAll() {
#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: printAllRecords" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    if ((this->start) != NULL) {
        struct record * currentRecord;
        currentRecord = (this->start);

        while (currentRecord != NULL) {
            cout << (*currentRecord).accountno << "\n";
            cout << (*currentRecord).name << "\n";
            cout << (*currentRecord).address << "\n";
            cout << (*currentRecord).yearofbirth << "\n";
            cout << "" << endl;
            currentRecord = (*currentRecord).next;
        }
    }

}

/*****************************************************************
 //
 // Function name:   deleteRecord
 //
 // DESCRIPTION:     A database function. This function allows the user to
 //                  delete a record that is held within the Linked List.
 //
 // Parameters:      uaccountno (int) :     the account no. of the customer
 //
 // Return values:   0 if successful
 //                 -1 otherwise
 //
 //****************************************************************/
int llist::deleteRecord(int uaccountno) {
    int found = 0;
    int done = 0;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: deleteRecord" << endl;
    cout << "Parameters: uaccountno = " << uaccountno;
    cout << "\n";
    cout << "" << endl;
#endif

    if ((this->start) != NULL) {

        if ((*(this->start)).accountno == uaccountno) {

            while ((this->start) != NULL && done != 1) {
                if ((*(this->start)).accountno == uaccountno) {
                    struct record *tempRecord;
                    tempRecord = (this->start);
                    (this->start) = (*(this->start)).next;
                    (*tempRecord).next = NULL;
                    delete tempRecord;
                    found = found + 1;
                } else {
                    done = 1;
                }
            }

        } else {
            if ((*(this->start)).next != NULL) {
                struct record *previous = (this->start);
                struct record *current = (*(this->start)).next;

                while (current != NULL) {
                    if ((*current).accountno == uaccountno) {
                        struct record *temp;
                        (*previous).next = (*current).next;
                        (*current).next = NULL;
                        temp = current;
                        current = (*previous).next;
                        delete temp;
                        found = found + 1;
                    } else if ((*current).accountno != uaccountno) {
                        current = (*current).next;
                        previous = (*previous).next;
                    }
                }
            }
        }
    }
    return found;
}

/*****************************************************************
 //
 // Function name:   reverse
 //
 // DESCRIPTION:     This function is a public wrapper for the private reverse
 //                  function, which reverses the order of all of the records
 //                  that are held within the Linked List.
 //
 // Parameters:      NONE
 //
 // Return values:   NONE
 //
 //****************************************************************/
void llist::reverse() {
#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: reverse" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    if ((this->start) != NULL) {
        (this->start) = reverse((this->start));
    }
}

/*****************************************************************
 //
 // Function name:   reverse
 //
 // DESCRIPTION:     This function reverses the order of all of the records
 //                  that are held within the Linked List.
 //
 // Parameters:      currentRecord (record*) :  a pointer to the current record
 //
 // Return values:   Returns a pointer to the new head of the Linked List.
 //
 //****************************************************************/
record * llist::reverse(record *currentRecord) {

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: reverse" << endl;
    cout << "Parameters: currentRecord = " << currentRecord;
    cout << "\n";
    cout << "" << endl;
#endif

    if ((currentRecord->next) == NULL) {
        return currentRecord;
    } else {
        record* newHead = reverse(currentRecord->next);
        /* Now currentRecord->next is reversed, temp is the new head.*/
        (currentRecord->next->next) = currentRecord;
        /* currentRecord->next is the current tail, so currentRecord becomes the
         *  new tail.*/
        (currentRecord->next) = NULL;
        return newHead;
    }

    return currentRecord;
}

/*****************************************************************
 //
 // Function name:   cleanup
 //
 // DESCRIPTION:     A database function. This function wipes the entire
 //                  Linked List clean.
 //
 // Parameters:      NONE
 //
 // Return values:   NONE
 //
 //****************************************************************/
void llist::cleanup() {
#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: cleanup" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    if ((this->start) != NULL) {
        struct record * currentRecord;
        currentRecord = (this->start);

        while (currentRecord != NULL) {
            struct record * tempRecord;
            tempRecord = (*currentRecord).next;
            delete currentRecord;
            currentRecord = tempRecord;
        }
    }

}

/*****************************************************************
 //
 // Function name:  readfile
 //
 // DESCRIPTION:    This function reads in from a file and stores what is read
 //                 in the nodes of the Linked List.
 //
 // Parameters:     NONE
 //
 // Return values:  0: if successful
 //                -1: if an error occurs
 //
 //****************************************************************/
int llist::readfile() {
    char line[100] = "\0";
    char empty[2] = "";

    ifstream infilebuffer;

    int accountno;
    char name[MAXNAME];
    char address[MAXADDRESS];
    int yearofbirth;
    char tempString[2] = "\0"; /* gives {\0, \0} */
    int c = 0;
    int status = 0;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: readfile" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    infilebuffer.open((this->filename), ios_base::in);

    if (infilebuffer.is_open()) {

        while (!infilebuffer.eof()) {
            strncpy(line, empty, 10);
            infilebuffer.getline(line, 9, '\n');
            if (!infilebuffer.eof()) {

                /*removeTrailingSpace(line);*/
                accountno = atoi(line);

                strncpy(line, empty, 10);
                infilebuffer.getline(line, 99, '\n');
                /*removeTrailingSpace(line);*/
                strncpy(name, line, (MAXNAME - 1));

                strncpy(line, empty, 10);
                while ((c != 94)) {
                    c = infilebuffer.get();
                    if (c != 94) {
                        tempString[0] = (char) c;
                        strcat(line, tempString);
                    }
                }
                strncpy(address, line, (MAXADDRESS - 1));
                while ((c != 10)) {
                    c = infilebuffer.get();
                }

                strncpy(line, empty, 10);
                infilebuffer.getline(line, 99, '\n');
                /*removeTrailingSpace(line);*/
                yearofbirth = atoi(line);

                addRecord(accountno, name, address, yearofbirth);
            }

        }
        status = 0;
        infilebuffer.close();
    } else {
        status = -1;
    }

    return (status);
}

/*****************************************************************
 //
 // Function name:  writefile
 //
 // DESCRIPTION:    This function writes out each field of the records in the
 //                 Linked List (in which start is the first node) to a file. If
 //                 the file already exists, it is overwritten.
 //
 // Parameters:     NONE
 //
 // Return values:  0: if successful
 //                -1: if an error occurs
 //
 //****************************************************************/
int llist::writefile() {
    ofstream outfilebuffer;
    int status = 0;
#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: writefile" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    outfilebuffer.open((this->filename), ios_base::trunc);

    if (outfilebuffer.is_open()) {
        if ((this->start) == NULL) {

        } else if ((this->start) != NULL) {
            struct record * currentRecord;
            currentRecord = (this->start);

            while (currentRecord != NULL) {
                outfilebuffer << (*currentRecord).accountno << "\n";
                outfilebuffer << (*currentRecord).name << "\n";
                outfilebuffer << (*currentRecord).address << "^\n";
                outfilebuffer << (*currentRecord).yearofbirth << "\n";
                currentRecord = (*currentRecord).next;
            }
        }
        outfilebuffer.close();
    } else {
        status = -1;
        cerr << "\n(File could not be opened)";
    }

    return status;
}
