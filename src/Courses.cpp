#include "Courses.h"

//constructor
Courses::Courses()
    : totalCredits(0.0), totalPoints(0.0), gpa(0.0) {
}

//setters
void Courses::setTotalCreditsnPoints() {
    totalCredits = 0.0;
    totalPoints = 0.0;

    for (const Course &course: courses) {
        totalCredits += course.getCredits();
        totalPoints += course.getPoints();
    }
    setGPA();
}
void Courses::setGPA() {
    gpa = 0.0;
    gpa = totalPoints/totalCredits;
}

//getters
float Courses::getTotalCredits() {return totalCredits;}
float Courses::getTotalPoints() {return totalPoints;}
float Courses::getGPA() {return gpa;}
size_t Courses::getAmountofCourses() {return courses.size();}

//other methods
bool Courses::addCourse(std::string code, std::string title, float credits, float grade) {
    for (const Course &course: courses)
        if (course.getCode() == code) {return false;}

    Course temp {code, title, credits, grade};
    courses.push_back(temp);
    setTotalCreditsnPoints();

    std::sort(courses.begin(), courses.end());
    return true;
}

bool Courses::editCourse(std::string code) {
    bool isFound{false};
    int option{};

    for (const Course &course: courses) {
        if (course.getCode() == code) {
            isFound = true;
            break;
        }
    }

    if (!isFound) return false;

    std::cout << "\n\nPlease select which field you want to edit:\n"
                << "1.\tCode\n"
                << "2.\tTitle\n"
                << "3.\tCredits\n"
                << "4.\tGrade\n\n"
                << "Enter the corresponding number of your choice:\t";
    std::cin >> option;

    std::cout << "\n\n";

    for (Course &course: courses){
        if (course.getCode() == code) {
            switch(option){
                case 1:
                    {
                        course.setCode(course.get_code());
                        break;
                    }
                case 2:
                    {
                        clearInput();
                        course.setTitle(course.get_title());
                        break;
                    }
                case 3:
                    {
                        course.setCredits(course.get_credits());
                        course.setPoints();
                        setTotalCreditsnPoints();
                        break;
                    }
                case 4:
                    {
                        course.setGrade(course.get_grade());
                        setTotalCreditsnPoints();
                        break;
                    }
            }
        }
    }
    return true;
}

bool Courses::deleteCourse(std::string code) {
    for (size_t i{0}; i < courses.size(); ++i) {
        if (courses.at(i).getCode() == code) {
            courses.erase(courses.begin() + i);
            setTotalCreditsnPoints();
            return true;
        }
    }
    return false;
}

void Courses::added (std::string code, std::string title, float credits, float grade) {
    std::cout << "\n\n***" << code << ((addCourse(code, title, credits, grade)) ? " was successfully added" : " already exists") << "!***\n\n\n";
    system("pause");
}
void Courses::edited (std::string code) {
    std::string response {((editCourse(code)) ? " was successfully edited" : " does not exist")};
    std::cout << "\n\n***" << code << response << "!***\n\n\n";
    system("pause");
}
void Courses::deleted (std::string code) {
    std::cout << "\n\n***" << code << ((deleteCourse(code)) ? " was successfully deleted" : " does not exist") << "!***\n\n\n";
    system("pause");
}

// Prompt for inputs

void Courses::add_course() {
    std::cout << "\n\n\n\n~~~~~ADD COURSE~~~~~\n\n\n"
        << "Please enter the following course details...\n\n";

    std::string code = get_code(),
            title = get_title();
    float credits = get_credits(),
            grade = get_grade();

    added(code, title, credits, grade);
}

void Courses::edit_course() {
    std::cout << "\n\n\n\n~~~~~EDIT COURSE~~~~~\n\n\n";
    if (getAmountofCourses() == 0) {
        std::cout << "***Sorry, no courses available to edit.***\n\n\n";
        system("pause");
    } else {
        std::cout << "Please enter the following course details...\n\n";
        edited(get_code());
    }
}

void Courses::delete_course() {
    std::cout << "\n\n\n\n~~~~~DELETE COURSE~~~~~\n\n\n";
    if (getAmountofCourses() == 0) {
        std::cout << "***Sorry, no courses available to delete.***\n\n\n";
        system("pause");
    } else {
        std::cout << "Please enter the following course details...\n\n";
        deleted(get_code());
    }
}

void Courses::display() const {
    std::cout << "_________________________________________________________________________________________\n"
            << std::setw(18) << std::left << "Code"
            << std::setw(50) << "Title"
            << std::setw(12) << "Credits"
            << std::setw(10) << "Letter" << std::endl << std::endl;

    if (courses.size() == 0) {
        std::cout << std::setw(18) << "N\\A"
                << std::setw(50) << "N\\A"
                << std::setw(12) << "N\\A"
                << std::setw(10) << "N\\A" << std::endl;
    } else {
        for (const Course &course: courses) {course.display();}
        std::cout << std::endl << std::setw(89) << std::right << "-----------------------" << std::endl
            << std::setw(75) << std::right << "GPA:\t" << std::setprecision(2) << std::fixed << gpa << std::endl
            << "_________________________________________________________________________________________\n";
    }
}
void Courses::exportCourses(std::ofstream &print) const {
    print << "_________________________________________________________________________________________\n"
                << std::setw(18) << std::left << "Code"
                << std::setw(50) << "Title"
                << std::setw(12) << "Credits"
                << std::setw(10) << "Letter" << std::endl << std::endl;

    if (courses.size() == 0) {
        print << std::setw(18) << "N\\A"
                << std::setw(50) << "N\\A"
                << std::setw(12) << "N\\A"
                << std::setw(10) << "N\\A" << std::endl;
    } else {
        for (const Course &course: courses) {course.exportCourse(print);}
        print << std::endl << std::setw(89) << std::right << "-----------------------" << std::endl
            << std::setw(75) << std::right << "GPA:\t" << std::setprecision(2) << std::fixed << gpa << std::endl
            << "_________________________________________________________________________________________\n";
    }
}

//deconstructor
Courses::~Courses(){
}

