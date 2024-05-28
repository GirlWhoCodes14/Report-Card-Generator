#ifndef REPORTCARD_H
#define REPORTCARD_H

#include "Student.h"
#include "Courses.h"

class ReportCard
{
    public:
        ReportCard();
        void exportReportCard();
        void displayReportCard() const;
        virtual ~ReportCard();

    private:
        Student myStudent;
        Courses myCourses;
};

#endif // REPORTCARD_H
