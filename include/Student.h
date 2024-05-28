#ifndef STUDENT_H
#define STUDENT_H

#include "IllegalInputException.h"
#include "Courses.h"

class Student : public IllegalInputException
{
    public:
        //constructors
        Student();
        Student(std::string name, int id);

        //setters
        void setName(std::string name);
        void setID(int id);

        //getters
        std::string getName()const;
        int getID()const;

        //functions to input student information
        void get_student();
        std::string get_student_name();
        int get_student_id();

        //other methods
        void display() const;
        void exportStudent(std::ofstream &print) const;

        void displayReportCard(Courses* myCourses) const;
        void exportReportCard(std::ofstream &print, Courses* myCourses) const;
        void export_report_card(Courses* myCourses);;

        //deconstructor
        virtual ~Student();

    private:
        std::string name;
        int id;
};

#endif // STUDENT_H
