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
void Courses::setGPA() {gpa = totalPoints/totalCredits;}

//getters
float Courses::getTotalCredits() {return totalCredits;}
float Courses::getTotalPoints() {return totalPoints;}
float Courses::getGPA() {return gpa;}
size_t Courses::getAmountofCourses() {return courses.size();}

//other methods
bool Courses::addCourse(std::string code, std::string title, float credits, float grade) {
    for (const Course &course: courses)
        if (course.getCode() == code) {return false;}

    Course temp {code, title, credits, grade}; // create new course
    courses.push_back(temp); // push into courses vector
    setTotalCreditsnPoints(); // recalculate GPA

    std::sort(courses.begin(), courses.end()); // court courses
    return true;
}

bool Courses::editCourse(std::string code) {
    bool isPresent{false};
    int option{};

    for (const Course &course: courses)
        if (course.getCode() == code) {isPresent = true; break;}
    if (!isPresent) return false;

    std::cout << "\nSelect which field you want to edit:\n" << std::right
                << std::setw(6) << "1. " << "Code\n"
                << std::setw(6) << "2. " << "Title\n"
                << std::setw(6) << "3. " << "Credits\n"
                << std::setw(6) << "4. " << "Grade\n";

    while (true) {
        try{
            std::cout << "~ Enter the number of your choice:\t";
            std::cin >> option;
            if (!std::cin || option > 4 || option < 1) {throw IllegalInputException{};}
            break; //exit the loop if no exception was thrown
        } catch (const IllegalInputException &ex) {
            errorCatch("Selection must be between 0-4.");
            clearInput();
        }
    }

    std::cout << "\nEnter the following course detail...\n";
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
    bool isAdded {addCourse(code, title, credits, grade)};
    std::string message = "\n[ " + code + (std::string)(isAdded ? " was successfully added" : " failed to be added") + "! ]\n";
    illegal.coloredMessage( (isAdded ? FOREGROUND_GREEN : FOREGROUND_RED), message );
}
void Courses::edited (std::string code) {
    bool isEdited {editCourse(code)};
    std::string message = "\n[ " + code + (std::string)(isEdited ? " was successfully edited" : " does not exist") + "! ]\n";
    illegal.coloredMessage( (isEdited ? FOREGROUND_GREEN : FOREGROUND_RED), message );
}

void Courses::deleted (std::string code) {
    bool isDeleted {deleteCourse(code)};
    std::string message = "\n[ " + code + (std::string)(isDeleted ? " was successfully deleted" : " does not exist") + "! ]\n";
    illegal.coloredMessage( (isDeleted ? FOREGROUND_GREEN : FOREGROUND_RED), message );
}

// Prompt for inputs

void Courses::add_course() {
    std::cout << "\n***** ADD COURSE *****\n\n"
        << "Enter the following course details...\n";

    std::string code{};
    while (true) {
        try{
            code = get_code();
            for (const Course &course: courses)
                if (course.getCode() == code) {throw IllegalInputException{};}
            break;
        } catch (const IllegalInputException &ex) {
            errorCatch(code + " already exists. Press enter and");
        }
    }

    std::string title = get_title();
    float credits = get_credits();
    float grade = get_grade();

    added(code, title, credits, grade);
}

void Courses::edit_course() {
    std::cout << "\n***** EDIT COURSE *****\n\n";
    if (getAmountofCourses() == 0) {
        illegal.coloredMessage(FOREGROUND_RED, "<No courses available to edit.>\n\n");
    } else {
        std::cout << "Enter the following course detail...\n";
        edited(get_code());
    }
}

void Courses::delete_course() {
    std::cout << "\n***** DELETE COURSE *****\n\n";
    if (getAmountofCourses() == 0) {
        illegal.coloredMessage(FOREGROUND_RED, "<No courses available to delete.>\n\n");
    } else {
        std::cout << "Enter the following course detail...\n";
        deleted(get_code());
    }
}

void Courses::display() const {
    std::cout << "--------------------------------------------------------------------------------------\n"
            << std::setw(18) << std::left << "Code"
            << std::setw(50) << "Title"
            << std::setw(12) << "Credits"
            << "Letter"
            << "\n--------------------------------------------------------------------------------------" << std::endl;

    if (courses.size() == 0) {
        std::cout << std::setw(18) << "N\\A"
                << std::setw(50) << "N\\A"
                << std::setw(12) << "N\\A"
                << "N\\A" << std::endl;
    } else {
        for (const Course &course: courses) {course.display();}
        std::cout << std::setw(86) << std::right << "--------------------" << std::endl
            << std::setw(75) << std::right << "GPA:\t" << std::setprecision(2) << std::fixed << gpa << std::endl
            << "--------------------------------------------------------------------------------------\n";
    }
}

void Courses::exportCourses(std::ofstream &print) const {
    print << "--------------------------------------------------------------------------------------\n"
        << std::setw(18) << std::left << "Code"
        << std::setw(50) << "Title"
        << std::setw(12) << "Credits"
        << "Letter"
        << "\n--------------------------------------------------------------------------------------" << std::endl;

    if (courses.size() == 0) {
        print << std::setw(18) << "N\\A"
                << std::setw(50) << "N\\A"
                << std::setw(12) << "N\\A"
                << "N\\A" << std::endl;
    } else {
        for (const Course &course: courses) {course.exportCourse(print);}
        print << std::setw(86) << std::right << "------------------------" << std::endl
            << std::setw(75) << std::right << "GPA:\t" << std::setprecision(2) << std::fixed << gpa << std::endl
            << "--------------------------------------------------------------------------------------\n";
    }
}

//deconstructor
Courses::~Courses(){
}

