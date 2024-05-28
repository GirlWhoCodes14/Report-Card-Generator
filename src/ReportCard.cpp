#include "ReportCard.h"

ReportCard::ReportCard()
{
    //ctor
}

void ReportCard::displayReportCard() const {
    myStudent.display();
    myCourses.display();
}

void ReportCard::exportReportCard() {
}

ReportCard::~ReportCard()
{
    //dtor
}
