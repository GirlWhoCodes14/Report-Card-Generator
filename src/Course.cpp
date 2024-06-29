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
    std::ifstream inGradeTable{"grade_table.txt"}; //open file
    std::string letter{""};
    float gpi{0.0}, lowerPercent{0.0}, upperPercent{0.0};

    if (!inGradeTable){ //check if file is open
        //std::cerr << "\n\ngrade_table.txt was NOT found!\n";
        message.coloredMessage(FOREGROUND_RED, "\n<grade_table.txt was NOT found!>\n<Please put grade_table.txt file in the same folder as the application>\n\n");
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
    std::string cCode{""};
    std::cin.clear();
    std::cin.ignore();

    while (true) {
        try{
            std::cout << std::setw(6) << std::right << "~ " << "Course Code:\t";
            getline(std::cin, cCode);
            if (cCode.empty()) {throw IllegalInputException{};}
            break;
        } catch (const IllegalInputException &ex) {
            errorCatch("Course code CANNOT be blank!");
        }
    }
    // using transform with toupper to convert mystr to uppercase
    transform(cCode.begin(), cCode.end(), cCode.begin(), ::toupper);
    return cCode;
}
std::string Course::get_title() {
    std::string cTitle{""};
    while (true) {
        try{
            std::cout << std::setw(6) << std::right << "~ " << "Course Name:\t";
            getline(std::cin, cTitle);
            if (cTitle.empty()) {throw IllegalInputException{};}
            break;
        } catch (const IllegalInputException &ex) {
            errorCatch("Course name CANNOT be blank!");
        }
    }
    return cTitle;
}
float Course::get_credits() {
    float cr{0.0};
    while (true) {
        try{
            std::cout << std::setw(6) << std::right << "~ " << "Course Credits:\t";
            std::cin >> cr;
            if ( !std::cin || cr > 4 || cr < 0 || int(cr*10)%5 ) {throw IllegalInputException{};}
            break;
        } catch (const IllegalInputException &ex) {
            errorCatch("Course credits MUST be 0-4 credit hours (multiple of 0.5)!");
            clearInput();
        }
    }
    return cr;
}
float Course::get_grade() {
    float g{0.0};
    while (true) {
        try{
            std::cout << std::setw(6) << std::right << "~ " << "Final Grade:\t";
            std::cin >> g;
            if (!std::cin || g > 100 || g < 0) {throw IllegalInputException{};}
            break;
        } catch (const IllegalInputException &ex) {
            errorCatch("Grade MUST be 0-100!");
            clearInput();
        }
    }
    return g;
}

//operator overloading
bool Course::operator < (const Course &obj) const {
    return (code < obj.code);
}

//other methods
void Course::display() const {
     std::cout << std::setw(18) << std::left << code << std::setw(50) << title
            << std::setw(12) << std::fixed << std::setprecision(1) << credits << letter << "\n";
}

void Course::exportCourse(std::ofstream &print) const {
     print << std::setw(18) << std::left << code << std::setw(50) << title
            << std::setw(12) << std::fixed << std::setprecision(1) << credits << letter << "\n";
}

//deconstructor
Course::~Course() {
}
