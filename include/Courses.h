#ifndef COURSES_H
#define COURSES_H

#include <vector>
#include <algorithm>

#include "Course.h"

class Courses : public Course
{
    public:
        //constructor
        Courses();

        //setters
        void setTotalCreditsnPoints();
        void setGPA();

        //getters
        float getTotalCredits();
        float getTotalPoints();
        float getGPA();
        size_t getAmountofCourses();

        //other methods
        bool addCourse(std::string code, std::string title, float credits, float grade);
        bool editCourse(std::string code);
        bool deleteCourse(std::string code);

        void added(std::string code, std::string title, float credits, float grade);
        void editted(std::string code);
        void deleted(std::string code);

        void add_course();
        void edit_course();
        void delete_course();

        void display() const;
        void exportCourses(std::ofstream &print) const;

        //deconstructor
        ~Courses();

    private:
        std::vector<Course> courses;
        float totalCredits;
        float totalPoints;
        float gpa;

};

#endif // COURSES_H
