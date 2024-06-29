#include "Student.h"

//constructors
// set default student name and ID
Student::Student()
    : Student{"N\\A", 000000000} {
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
    std::cout << "***** STUDENT INFORMATION *****\n\n"
        << "Enter the following student information...\n";
    setName(get_student_name());
    setID(get_student_id());
    message.coloredMessage(FOREGROUND_GREEN, "\n[ Student information successfully edited! ]\n");
}
std::string Student::get_student_name(){
    std::string fullName{};

    std::cin.clear();
    std::cin.ignore();

    while (true) {
        try{
            std::cout << std::setw(6) << std::right << "~ " << "Full Name:\t";
            getline(std::cin, fullName);
            if (fullName.empty()) {throw IllegalInputException{};}
            break;
        } catch (const IllegalInputException &ex) {
            errorCatch("Name CANNOT be blank!");
        }
    }
    return fullName;
}
int Student::get_student_id(){
    int studentID;
    while (true) {
        try{
            std::cout << std::setw(6) << std::right << "~ " << "Student ID:\t";
            std::cin >> studentID;
            if (!std::cin) {throw IllegalInputException{};}
            break;
        } catch (const IllegalInputException &ex) {
            errorCatch("Student ID must be a number!");
            clearInput();
        }
    }
    return studentID;
}

//other methods
void Student::display() const {
    std::cout << std::setw(22) << std::left << "Student Name:" << name << "\n";
    std::cout << std::setw(22) << "Student ID:";
        if (id == 000000000) std::cout << "N\\A";
        else std::cout << id;
    std::cout << std::endl;
}
void Student::exportStudent(std::ofstream &print) const {
    print << std::setw(22) << std::left << "Student Name:" << name << "\n"
        << std::setw(22) << std::left << "Student ID:" << id << "\n";
}

// display the student's report card on the console
void Student::displayReportCard(Courses* myCourses) const {
    std::cout << std::setw(48) << std::right << "REPORT CARD" << std::endl << std::endl;
    display();
    myCourses->display();
}

// display on console that report card was exported
void Student::export_report_card(Courses* myCourses) {
    std::cout << "***** EXPORT REPORT CARD *****\n\n";

    // if student information or courses are NOT filled out
    if (getName() == "N\\A" || myCourses->getAmountofCourses() == 0) {
        setConsoleColor(FOREGROUND_RED);

        if (getName() == "N\\A" && myCourses->getAmountofCourses() == 0) {
            std::cout << "<Report card requires student information.>" << std::endl << "\t1. Add Student Information\n\n";
            std::cout << "<Report card does NOT have any courses.>" << std::endl << "\t2. Add a course\n\n";
        }
        else if (getName() == "N\\A") {
            std::cout << "<Report card requires student information.>" << std::endl << "\t1. Add Student Information\n\n";
        }
        else if (myCourses->getAmountofCourses() == 0) {
            std::cout << "<Report card does NOT have any courses.>" << std::endl << "\t2. Add a course\n\n";
        }

        resetColorAndPause();
        return;
    }

    // set report card title
    std::ofstream outReportCard { (std::string)(getName() + " - Report Card.txt") };

    if (!outReportCard){
        setConsoleColor(FOREGROUND_RED);
        std::cerr << std::endl << "<Export Failed!>\n\n";
    } else {
        // export the student's report card to .txt file
        outReportCard << std::setw(48) << std::right << "REPORT CARD" << std::endl << std::endl;
        exportStudent(outReportCard);
        myCourses->exportCourses(outReportCard);
        outReportCard.close();

        setConsoleColor(FOREGROUND_GREEN);
        std::cout << "[ Export Successful! ]" << std::endl
            << "File Name:\t" << getName() << " - Report Card.txt\n\n";
    }
    resetColorAndPause();
}

//destructor
Student::~Student()
{
}
