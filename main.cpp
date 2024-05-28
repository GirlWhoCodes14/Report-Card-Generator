/*
Alexis Ayuso
410921355
Report Card Generator
*/

// THESE ARE THE ERRORS YOU WANT TO FIX*****************************************
// put a length requirement for the Student ID and allow letters in the ID for exchange students
// be able to add multiple students
// change the color of the error warnings to red and an alert sound
// credits must be even number or half credits only
// credits cannot be -0
// add the ability to withdraw (can only be done once and ask to confirm) and have satisfactory or unsatisfactory course
// once you edit the student information once, for delete course and withdraw course, ask "Are you sure you want to edit?"


//headers
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

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
void clearInput();


//main function
int main()
{
    Student* newStudent = new Student;
    Courses* newCourses = new Courses;
    Grading* newGrading = new Grading;

    int selection{};
    do {
        system("cls");
        newStudent->displayReportCard(newCourses);
        displayMenu();
        selection = getSelection();
        menuOptions(selection, newStudent, newCourses, newGrading);
    } while (selection != 0);

    delete newStudent;
    delete newCourses;
    delete newGrading;

    return 0;
}

//function declarations
void displayMenu(){
    std::cout << "\n\n\n\nMENU\n\n"
            << "1.\tEdit Student Information\n"
            << "2.\tAdd Course\n"
            << "3.\tEdit Course\n"
            << "4.\tDelete Course\n"
            << "5.\tView Grading System\n"
            << "6.\tExport Report Card\n"
            << "0.\tQuit\n\n";
}
int getSelection() {
    int choice{};
    while (true) {
        try{
            std::cout << "Enter the corresponding number of your choice:\t";
            std::cin >> choice;
            if (!std::cin || choice > 6 || choice < 0) {throw IllegalInputException{};}
            break; //exit the loop if no exception was thrown
        } catch (const IllegalInputException &ex) {
            clearInput();
            std::cerr << ex.what() << "***NOTE: Selection must be between 0-6***\n" << std::endl;
        }
    } return choice;
}

void menuOptions(const int &option, Student* myStudent, Courses* myCourses, Grading* myGrading){
    system("cls");
    switch(option){
        case 1:
            myStudent->get_student(); break;
        case 2:
            {
                myStudent->displayReportCard(myCourses);
                myCourses->add_course(); break;
            }
        case 3:
            {
                myStudent->displayReportCard(myCourses);
                myCourses->edit_course(); break;
            }
        case 4:
            {
                myStudent->displayReportCard(myCourses);
                myCourses->delete_course(); break;
            }
        case 5:
            {
                system("cls");
                myGrading->display();
                system("pause"); break;
            }
        case 6:
            myStudent->export_report_card(myCourses); break;
        case 0:
            quit(); break;
    }
}

void quit() {
    system("cls");
    std::cout << "\n\n\n***Thank you for using my Report Card Generator! Goodbye.***\n\n\n";
}
void clearInput() {// clears input stream after illegal inputs are entered
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
