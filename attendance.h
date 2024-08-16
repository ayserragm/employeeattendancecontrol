#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#define STATUS_TO_STRING(status) (status == ABSENT ? "Absent" : "Present") //Using at least one macro function


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

// attendance.h dosyasına ekleyin
extern int attendanceCount;


typedef struct {
    int day;
    int month;
    int year;
} Date;

// Enum
enum Status {
    ABSENT = 0,
    PRESENT = 1
};

typedef struct {
    int employeeId;
    Date date;
    enum Status status; // 0: Absent, 1: Present
} Attendance;

 // Function prototypes
void addAttendanceToMemory(Attendance* attendance);
void findAttendanceInMemory(int employeeId);

// 2 Function pointers in a struct
typedef struct {
    void (*addAttendance)(Attendance* );
    void (*findAttendance)(int);
} AttendanceOperations;

#endif