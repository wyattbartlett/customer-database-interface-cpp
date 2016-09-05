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
 // File:        UI.cpp
 //
 // Description: The file contains the user-interface functions for Project 2
 //
 //***************************************************************/

#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include "record.h"
#include "func.h"
#include "llist.h"
using namespace std;

const int MINYEAR = 1;
const int MAXYEAR = 10000;
const int MAXADDRESS = 80;
const int MAXNAME = 25;
const int NUM_OPTIONS = 7;

int main(int argc, char *argv[]) {
#ifdef DEBUG
    cout << "**DEBUG MODE ACTIVATED**" << endl << endl << endl;
#endif
    llist mylist;
    int choice = 0;
    int accountno = 0;
    char name[MAXNAME];
    char address[MAXADDRESS];
    int yearofbirth = 0;
    char fieldChoice[80] = "";
    int recordsAccessed = 0;

    strncpy(name, "", (MAXNAME - 1));
    strncpy(address, "", (MAXADDRESS - 1));

    while (choice != NUM_OPTIONS) {
        displayMenu();
        choice = getChoice();
        switch (choice) {
        case 1:
            cout << "       1:   Add Record\n" << endl;
            accountno = getAccountNo();
            getName(name, MAXNAME);
            getfield(address, MAXADDRESS);
            yearofbirth = getBirthYear();
            cout << "Adding record..." << endl;
            mylist.addRecord(accountno, name, address, yearofbirth);
            cout << "Record added." << endl;
            break;
        case 2:
            cout << "       2:   Modify Record\n" << endl;
            /*if (!isListEmpty(mylist)) {*/
            accountno = getAccountNo();
            getfield(address, MAXADDRESS);
            cout << "Modifying record(s)..." << endl;
            recordsAccessed = mylist.modifyRecord(accountno, address);
            if (recordsAccessed > 0) {
                cout << recordsAccessed << " record(s) modified.\n";
                recordsAccessed = 0;
            } else {
                cout << "\nSorry... the record could not be modified, "
                        "because it could not be found." << endl;
            }
            /*} else {
             cout << "\nSorry... There are no records to modify." << endl;
             }*/
            break;
        case 3:
            cout << "       3:   Print Record\n" << endl;
            /*if (!isListEmpty(mylist)) {*/
            accountno = getAccountNo();
            cout << "Printing record(s)...\n" << endl;
            recordsAccessed = mylist.printRecord(accountno);
            if (recordsAccessed > 0) {
                cout << recordsAccessed << " record(s) printed.\n";
                recordsAccessed = 0;
            } else {
                cout << "\nSorry... the record could not be printed, "
                        "because it could not be found." << endl;
            }
            /*} else {
             cout << "\nSorry... There are no records to print." << endl;
             }*/
            break;
        case 4:
            cout << "       4:   Print All Records" << endl;
            /*if (!isListEmpty(mylist)) {*/
            cout << "\nPrinting all records...\n\n" << endl;
            cout << mylist;
            cout << "\nAll records printed." << endl;
            /*} else {
             cout << "\nSorry... There are no records to print." << endl;
             }*/
            break;
        case 5:
            cout << "       5:   Delete Record\n" << endl;
            /*if (!isListEmpty(mylist)) {*/
            accountno = getAccountNo();
            cout << "Deleting record(s)..." << endl;
            recordsAccessed = mylist.deleteRecord(accountno);
            if (recordsAccessed > 0) {
                cout << recordsAccessed << " record(s) deleted.\n";
                recordsAccessed = 0;
            } else {
                cout << "\nSorry... the record could not be deleted, "
                        "because it could not be found." << endl;
            }
            /*} else {
             cout << "\nSorry... There are no records to delete." << endl;
             }*/
            break;
        case 6:
            cout << "       6:   Reverse Records" << endl;
            cout << "\n\nReversing records..." << endl;
            mylist.reverse();
            cout << "Records reversed." << endl;
            break;
        case NUM_OPTIONS:
            cout << "       7:   Quit" << endl;
            cout << "\n\nClosing program..." << endl;
            cout << "Goodbye!" << endl;
        }/* end switch */

    }/* end while loop */

    return 0;
} /* end main */

/*****************************************************************
 //
 // Function name:   isListEmpty
 //
 // DESCRIPTION:     This function checks if the LinkedList is empty or not.
 //
 // Parameters:      start (struct record *) :  a pointer to the start of the
 //                                             LinkedList
 //
 // Return values:  1 if the list is empty
 //                 0 otherwise
 //
 //****************************************************************/
int isListEmpty(llist& linkedList) {
    int status = 1;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: isListEmpty" << endl;
    cout << "Parameters: linkedList = " << linkedList;
    cout << "\n";
    cout << "" << endl;
#endif

    /* if (linkedList.start == NULL) {
     status = 1;
     } else {
     status = 0;
     }*/
    return status;
}

/*****************************************************************
 //
 // Function name:   displayMenu
 //
 // DESCRIPTION:     This function displays the menu options for the user.
 //
 // Parameters:      NONE
 //
 // Return values:   NONE
 //
 //****************************************************************/
void displayMenu() {
#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: displayMenu" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    cout << "\n";
    cout << "----------------------------------------\n";
    cout << "Menu:" << endl;
    cout << "\n";
    cout << "Option #" << endl;
    cout << "       1:   Add Record" << endl;
    cout << "       2:   Modify Record" << endl;
    cout << "       3:   Print Record" << endl;
    cout << "       4:   Print All Records" << endl;
    cout << "       5:   Delete Record" << endl;
    cout << "       6:   Reverse Records" << endl;
    cout << "       7:   Quit" << endl;
    cout << "----------------------------------------\n";
    cout << "" << endl;
}

/*****************************************************************
 //
 // Function name:  getChoice
 //
 // DESCRIPTION:    A user interface function. This function obtains the number
 //                 representing the user's selected menu option.
 //
 // Parameters:     NONE
 //
 // Return values:  Returns the user input if it is a valid integer greater than
 //                 zero.
 //
 //****************************************************************/
int getChoice() {
    int input;
    input = 0;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: getChoice" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    cout << "Please select an option by typing in the associated option #, then"
            " pressing the ENTER key. Options are represented by numbers "
            "1-7: ";
    cin >> input;

    if (cin.fail() || input < 1 || input > NUM_OPTIONS) {
        do {
            cin.clear();
            cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
            cout << "Sorry... please enter a number from 1 to 7: ";
            cin >> input;
        } while (cin.fail() || input < 1 || input > NUM_OPTIONS);
    }

    eatTrash(); /*eats the left over characters*/

    cout << "\n";
    cout << "Input accepted: " << input << "\n" << "\n";
    cout << "\n";
    cout << "" << endl;
    return input;
}

/*****************************************************************
 //
 // Function name:  getAccountNo
 //
 // DESCRIPTION:    A user interface function. This function obtains the user's
 //                 account number.
 //
 // Parameters:     NONE
 //
 // Return values:  Returns the user input if it is a valid integer greater than
 //                 zero.
 //
 //****************************************************************/
int getAccountNo() {
    int input;
    input = 0;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: getAccountNo" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    cout << "Please enter the customer's account number (greater than zero) "
            "followed \nby the ENTER key: ";
    cin >> input;

    if (cin.fail() || input <= 0) {
        do {
            cin.clear();
            cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
            cout << "Sorry... please enter a number greater than zero: ";
            cin >> input;
        } while (cin.fail() || input <= 0);
    }

    eatTrash(); /*eats the left over characters*/

    cout << "\n";
    cout << "Input accepted: " << input << "\n" << "\n";
    cout << "\n";
    cout << "" << endl;
    return input;
}

/*****************************************************************
 //
 // Function name:   getName
 //
 // DESCRIPTION:     This function gets the name that the user inputs.
 //
 // Parameters:      field (char[]) :      the field to update
 //                  maxLength (int) :     the maximum number of characters + 2
 //
 // Return values:   NONE
 //
 //****************************************************************/
void getName(char field[], int maxLength) {
    char inString[25];

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: getName" << endl;
    cout << "Parameters: field = " << field << ", maxLength = "
    << maxLength;
    cout << "\n";
    cout << "" << endl;
#endif

    strncpy(inString, "", (maxLength - 1));
    cout << "Please enter the customer's name (up to " << (maxLength - 2)
            << " characters long) followed \nby the ENTER key: ";
    cin.getline(inString, maxLength, '\n');
    removeTrailingSpace(inString);

    strncpy(field, inString, (maxLength - 1));
    cout << "\n";
    cout << "Input accepted: " << field << "\n" << "\n";
    cout << "\n";
    cout << "" << endl;
}

/*****************************************************************
 //
 // Function name:  getfield
 //
 // DESCRIPTION:    This function gets the address that the user inputs.
 //
 // Parameters:     field (char[]) :    the field to update
 //                 maxLength (int) :   the maximum number of characters + 2
 //
 // Return values:  NONE
 //
 //****************************************************************/
void getfield(char field[], int maxLength) {
    char inString[80];
    char tempString[80] = "\0";
    int c = 0;
    int carrot = 0;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: getfield" << endl;
    cout << "Parameters: field = " << field << ", maxLength = "
    << maxLength;
    cout << "\n";
    cout << "" << endl;
#endif

    strncpy(inString, "", (maxLength - 1));

    cout << "Please enter the customer's address (up to " << (maxLength - 2)
            << " characters long) followed \nby the '^' key and then the ENTER "
                    "key: " << endl;
    while ((carrot != 1 && (strlen(inString) < (maxLength - 1)))) {
        c = cin.get();
        if (c != 94) {
            tempString[0] = (char) c;
            strcat(inString, tempString);
        } else {
            carrot = 1;
        }
    }
    removeTrailingSpace(inString);
    strncpy(field, inString, (maxLength - 1));
    eatTrash();
    cout << "\n";
    cout << "Input accepted: " << field << "\n" << "\n";
    cout << "\n";
    cout << "" << endl;
}

/*****************************************************************
 //
 // Function name:  getBirthYear
 //
 // DESCRIPTION:    A user interface function. This function obtains the user's
 //                 year of birth.
 //
 // Parameters:     NONE
 //
 // Return values:  Returns the user input if it is a valid integer greater than
 //                 zero and less than 10000.
 //
 //****************************************************************/
int getBirthYear() {
    int input;
    input = 0;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: getBirthYear" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    cout << "Please enter the customer's year of birth followed \nby the ENTER "
            "key: ";
    cin >> input;

    if (cin.fail() || input < (MINYEAR) || input >= MAXYEAR) {
        do {
            cin.clear();
            cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
            cout << "Sorry... please enter a year greater than "
                    << (MINYEAR - 1) << " and less than " << MAXYEAR << ": ";
            cin >> input;
        } while (cin.fail() || input < (MINYEAR) || input >= MAXYEAR);
    }

    eatTrash(); /*eats the left over characters*/

    cout << "\n";
    cout << "Input accepted: " << input << "\n" << "\n";
    cout << "\n";
    cout << "" << endl;
    return input;
}

/*****************************************************************
 //
 // Function name:  removeTrailingSpace
 //
 // DESCRIPTION:    This function removes any trailing space from the end of a
 //                 given string (including newline characters).
 //
 // Parameters:     string (char[]):    the given string from which to remove
 //                                     the newline character
 //
 // Return values:  NONE
 //
 //****************************************************************/
void removeTrailingSpace(char string[]) {
    int i;
    char temp[100];
    char c;
    int copychars = strlen(string);
    strncpy(temp, "", 99);

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: removeTrailingSpace" << endl;
    cout << "Parameters: string = " << string;
    cout << "\n";
    cout << "" << endl;
#endif

    c = string[(copychars - 1)]; /*starting from the right-most position*/

    while (isspace((int) c)) {
        copychars = copychars - 1;
        c = string[(copychars - 1)];
    }

    for (i = 0; i < (copychars); i++) {
        temp[i] = string[i];
    }
    strncpy(string, temp, strlen(string));
}

/*****************************************************************
 //
 // Function name:  eatTrash
 //
 // DESCRIPTION:    This function eats all remaining input from stdin up to and
 //                 including the first '\n'.
 //
 // Parameters:     NONE
 //
 // Return values:  NONE
 //
 //****************************************************************/
void eatTrash() {
    char temp = 0;

#ifdef DEBUG
    cout << "\n";
    cout << "**DEBUG**" << endl;
    cout << "Function name: eatTrash" << endl;
    cout << "Parameters: NONE";
    cout << "\n";
    cout << "" << endl;
#endif

    cin.get(temp);
    while (temp != '\n') {
        cin.get(temp);
    }
}
