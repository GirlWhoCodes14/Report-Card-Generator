#include "Student.h"

//constructors
Student::Student()
    : Student{"N\\A", 410921000} {
}
Student::Student(std::string name, int id)
    : name(name), id(id) {
}

//setters
void Student::setName(std::string name) {this->name = name;}
void Student::setID(int id) {this->id = id;}

//getters
std::string Student::getName()const {return name;}
int Student::getID()const {return id;}

// functions to input student information
void Student::get_student(){
    system("cls");
    std::cout << "~~~~~STUDENT INFORMATION~~~~~\n\n\n"
        << "Please enter the following student information...\n\n";
    setName(get_student_name());
    setID(get_student_id());
    std::cout << "\n\n\n***Student information successfully editted!***\n\n\n";
    system("pause");
}
std::string Student::get_student_name(){
    std::cout << std::setw(32) << std::left << "Full Name (e.g. John Doe):";
    std::string fullName{};
    std::cin.clear();
    std::cin.ignore();
    getline(std::cin, fullName);
    return fullName;
}
int Student::get_student_id(){
    int studentID;
    while (true) {
        try{
            std::cout << std::setw(32) << std::left << "Student ID (e.g. 410921350):";
            std::cin >> studentID;
            if (!std::cin) {throw IllegalInputException{};}
            break;
        } catch (const IllegalInputException &ex) {
            clearInput();
            std::cerr << ex.what() << "***NOTE: Student ID must be a number***\n" << std::endl;
        }
    } return studentID;
}

//other methods
void Student::display() const {
    std::cout << std::setw(22) << std::left << "Student Name:" << name << "\n"
        << std::setw(22) << std::left << "Student ID:" << id << "\n";
}
void Student::exportStudent(std::ofstream &print) const {
    print << std::setw(22) << std::left << "Student Name:" << name << "\n"
        << std::setw(22) << std::left << "Student ID:" << id << "\n";
}

void Student::displayReportCard(Courses* myCourses) const {
    std::cout << std::setw(60) << std::right << "National Dong Hwa University" << std::endl
         << std::setw(52) << "REPORT CARD" << std::endl << std::endl;
    display();
    myCourses->display();
}
void Student::exportReportCard(std::ofstream &print, Courses* myCourses) const {
    if (!print){
        std::cerr << "\n\n***Export Failed!***\n\n\n";
    } else {
        print << std::setw(60) << std::right << "National Dong Hwa University" << std::endl
         << std::setw(52) << "REPORT CARD" << std::endl << std::endl;

        exportStudent(print);
        myCourses->exportCourses(print);
        print.close();
        std::cout << "\n***Export Successful!***\nYour file is named \"reportcard.txt\".\n\n\n";
    }
    system("pause");
}

void Student::export_report_card(Courses* myCourses) {
    std::cout << "~~~~~EXPORT REPORT CARD~~~~~\n\n\n";
    if (getName() == "N\\A") {
        std::cout << "***Sorry, no name associated with the report card.  (i.e., 1. Edit Student Information)***\n\n\n"; system("pause");
    }
    else if (myCourses->getAmountofCourses() == 0) {
        std::cout << "***Sorry, no courses added to print report card. (i.e., 2. Add a course)***\n\n\n"; system("pause");
    } else {
        std::string reportCardTitle = getName() + " Report Card.txt";
        std::ofstream outReportCard {reportCardTitle};
        exportReportCard(outReportCard, myCourses);
    }
}

//destructor
Student::~Student()
{
}
