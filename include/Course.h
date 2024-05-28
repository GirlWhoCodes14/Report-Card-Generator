#ifndef COURSE_H
#define COURSE_H

#include "IllegalInputException.h"

class Course : public IllegalInputException
{
    public:
        //constructors
        Course(); //default constructor
        Course(const Course &source); //copy constructor
        Course(std::string code, std::string title, float credits, float grade);

        //setters
        void setCode(std::string code);
        void setTitle(std::string title);
        void setCredits(float credits);
        void setGrade(float grade);
        void setGPInLetter();
        void setPoints();

        //getters
        std::string getCode() const;
        std::string getTitle() const;
        float getCredits() const;
        float getGrade() const;
        float getGPI() const;
        std::string getLetter() const;
        float getPoints() const;

        //functions to input course details
        std::string get_code();
        std::string get_title();
        float get_credits();
        float get_grade();

        //operator overloading
        bool operator < (const Course &obj) const; //used for the sort function

        //other methods
        float calcPoints();
        void display() const;
        void exportCourse(std::ofstream &print) const;

        //deconstructor
        ~Course();

    private:
        std::string code;
        std::string title;
        float credits;
        float grade;
        float gpi;
        std::string letter;
        float points;
};

#endif // COURSE_H
