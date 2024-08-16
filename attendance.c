#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
#include "attendance.h"
#define MAX_ATTENDANCES 100  

extern Attendance* attendanceList[MAX_ATTENDANCES];
extern int attendanceCount;

Employee *employees;


void addAttendanceToMemory(Attendance* attendance) {
    attendanceList[attendanceCount] = attendance;
    attendanceCount++;
}

// Function to find attendance in memory based on employeeId
void findAttendanceInMemory(int employeeId) {
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceList[i]->employeeId == employeeId) {
            printf("Attendance found in memory.\n");
            printf("Employee ID: %d\n", attendanceList[i]->employeeId);
            printf("Date: %d-%d-%d\n", attendanceList[i]->date.day, attendanceList[i]->date.month, attendanceList[i]->date.year);
            printf("Status: %s\n", STATUS_TO_STRING(attendanceList[i]->status)); //j. Using at least one macro function

            return;
        }
    }
    printf("Attendance not found in memory.\n");
}
