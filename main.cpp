/*
    Report Card Generator
    Powered by Alexis Ayuso
*/

//headers
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <exception>
#include <limits>

#include "IllegalInputException.h"
#include "Student.h"
#include "Courses.h"
#include "Grading.h"

//function prototypes
void displayMenu();
int getSelection();
void menuOptions(const int &option, Student* myStudent, Courses* myCourses, Grading* myGrading);
void quit();

// global variables
IllegalInputException illegal;

//main function
int main()
{
    Student* newStudent = new Student;
    Courses* newCourses = new Courses;
    Grading* newGrading = new Grading;

    int selection{};
    do {
        system("cls"); // clear screen

        // display the student's report card
        newStudent->displayReportCard(newCourses);

        // display menu options
        displayMenu();

        // get the option the user inputted
        selection = getSelection();

        // navigate to the screen corresponding to the option the user inputted
        menuOptions(selection, newStudent, newCourses, newGrading);
    } while (selection != 0);

    delete newStudent;
    delete newCourses;
    delete newGrading;
    return 0;
}

//function declarations
void displayMenu(){
    std::cout << "\n\n*** MENU ***\n" << std:: right
            << std::setw(6) << "1. " << "Add Student Information\n"
            << std::setw(6) << "2. " << "Add Course\n"
            << std::setw(6) << "3. " << "Edit Course\n"
            << std::setw(6) << "4. " << "Delete Course\n"
            << std::setw(6) << "5. " << "View Grading System\n"
            << std::setw(6) << "6. " << "Export Report Card\n"
            << std::setw(6) << "0. " << "Quit\n";
}

int getSelection() {
    int choice{};
    while (true) {
        try{
            std::cout << "~ Enter the number of your choice:\t";
            std::cin >> choice;
            if (!std::cin || choice > 6 || choice < 0) {throw IllegalInputException{};}
            break; //exit the loop if no exception was thrown
        } catch (const IllegalInputException &ex) {
            illegal.errorCatch("Selection must be between 0-6.");
            illegal.clearInput();
        }
    }
    return choice;
}

void menuOptions(const int &option, Student* myStudent, Courses* myCourses, Grading* myGrading){
    system("cls");
    switch(option) {
        case 1:
            {
                myStudent->get_student(); break;
            }
        case 2:
            {
                myCourses->display();
                myCourses->add_course(); break;
            }
        case 3:
            {
                myCourses->display();
                myCourses->edit_course(); break;
            }
        case 4:
            {
                myCourses->display();
                myCourses->delete_course(); break;
            }
        case 5:
            myGrading->display(); break;
        case 6:
            myStudent->export_report_card(myCourses); break;
        case 0:
            {
                quit(); break;
            }
    }
}

void quit() {
    system("cls");
    illegal.setConsoleColor(FOREGROUND_GREEN);
    std::cout << "\n*** Thank you for using the Report Card Generator by Alexis Ayuso! ***\n"
            << std::right << std::setw(35) << "Goodbye.\n\n";
    illegal.resetColorAndPause();
}
