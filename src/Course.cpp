#include "Course.h"

//constructors
Course::Course()
    : Course{"Unknown", "Unknown", 0.0, 0.0} {
}
Course::Course(const Course &source)
    : Course{source.code, source.title, source.credits, source.grade} {
}
Course::Course(std::string code, std::string title, float credits, float grade)
    : code{code}, title{title}, credits{credits}, grade{grade} {
    setGPInLetter();
}

//setters
void Course::setCode(std::string code) {this->code = code;}
void Course::setTitle(std::string title) {this->title = title;}
void Course::setCredits(float credits) {this->credits = credits;}
void Course::setGrade(float grade) {this->grade = grade; setGPInLetter();}
void Course::setGPInLetter() {
    std::ifstream inGradeTable{"ndhuGradeTable.txt"}; //open file
    std::string letter{""};
    float gpi{0.0}, lowerPercent{0.0}, upperPercent{0.0};

    if (!inGradeTable){ //check if file is open
        std::cerr << "\n\nndhuGradeTable.txt was NOT found!\n";
        //return 1; //exit the program (main)
    }

    while (inGradeTable >> letter >> gpi >> lowerPercent >> upperPercent){ //read in the grade details
        if (grade >= lowerPercent && grade <= upperPercent){
            this->letter = letter;
            this->gpi = gpi;
            break;
        }
    } inGradeTable.close(); //close the file

    setPoints();
}
void Course::setPoints() {points = credits*gpi;}

//getters
std::string Course::getCode() const {return code;}
std::string Course::getTitle() const {return title;}
float Course::getCredits() const {return credits;}
float Course::getGrade() const {return grade;}

float Course::getGPI() const {return gpi;}
std::string Course::getLetter() const {return letter;}
float Course::getPoints() const {return points;}

//functions to input course details
std::string Course::get_code(){
    std::cout << std::setw(40) << std::left << "Course Code (e.g. CSIEB0010):";
    std::string cCode{""};
    std::cin.ignore();
    getline(std::cin, cCode);
    return cCode;
}
std::string Course::get_title() {
    std::cout << std::setw(40) << std::left << "Course Name (e.g. Programming I):";
    std::string cTitle{""};
    getline(std::cin, cTitle);
    return cTitle;
}
float Course::get_credits() {
    float cr{0.0};
    while (true) {
        try{
            std::cout << std::setw(40) << std::left << "Course Credits (i.e. 0-4):";
            std::cin >> cr;
            if (!std::cin || cr > 4 || cr < 0) {throw IllegalInputException{};}
            break;
        } catch (const IllegalInputException &ex) {
            clearInput();
            std::cerr << ex.what() << "***NOTE: Course Credits must be between 0 to 4 credit hours***\n" << std::endl;
        }
    } return cr;
}
float Course::get_grade() {
    float g{0.0};
    while (true) {
        try{
            std::cout << std::setw(40) << std::left << "Final Grade (i.e. 0-100):";
            std::cin >> g;
            if (!std::cin || g > 100 || g < 0) {throw IllegalInputException{};}
            break;
        } catch (const IllegalInputException &ex) {
            clearInput();
            std::cerr << ex.what() << "***NOTE: Grade must be between 0% to 100%***\n" << std::endl;
        }
    } return g;
}

//operator overloading
bool Course::operator < (const Course &obj) const {
    return (code < obj.code);
}

//other methods
void Course::display() const {
     std::cout << std::setw(18) << std::left << code << std::setw(50) << std::left << title
            << std::setw(12) << std::left << credits << std::setw(10) << std::left << letter << "\n";
}

void Course::exportCourse(std::ofstream &print) const {
     print << std::setw(18) << std::left << code << std::setw(50) << std::left << title
            << std::setw(12) << std::left << credits << std::setw(10) << std::left << letter << "\n";
}

//deconstructor
Course::~Course() {
}
