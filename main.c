#include <stdio.h>
#include <stdlib.h>
#include "employee.h"
#include "attendance.h"

#define MAX_ATTENDANCES 100
Attendance *attendanceList[MAX_ATTENDANCES];
int attendanceCount = 0;

int main()
{
    AttendanceOperations attendanceOps;
    attendanceOps.addAttendance = addAttendanceToMemory;
    attendanceOps.findAttendance = findAttendanceInMemory;

    int employeeId;
    int requestedDays;
    int usedVacationDays = 0;
    Employee employees[4];

    FILE *file = fopen("employee_database.txt", "r");
    int i = 0;
    if (file != NULL)
    {
        while (fscanf(file, "%d,%49[^,],%d\n", &employees[i].id, employees[i].name, &employees[i].type) == 3)
        {
            i++;
        }
        fclose(file);
    }

    FILE *saveFile = fopen("employee_database.txt", "w");
    if (saveFile != NULL)
    {
        for (int i = 0; i < 4; i++)
        {
            fprintf(saveFile, "%d,%s,%d\n", employees[i].id, employees[i].name, employees[i].type);
        }
        fclose(saveFile);
    }

    employees[0] = *createEmployee(1, "Ayse Serra Gumustakim", MANAGER);
    employees[1] = *createEmployee(2, "Beyzanur Sevigen", MANAGER);
    employees[2] = *createEmployee(3, "Sumeyra Akpinar", WORKER);
    employees[3] = *createEmployee(4, "Eren Yeager", WORKER);

    printf("Calisanlar:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s - %s\n", employees[i].id, employees[i].name,
               employees[i].type == WORKER ? "Worker" : "Manager");
    }

    Attendance attendance1 = {1, {15, 12, 2023}, PRESENT};
    Attendance attendance2 = {2, {15, 12, 2023}, ABSENT};
    Attendance attendance3 = {3, {15, 12, 2023}, PRESENT};
    Attendance attendance4 = {4, {15, 12, 2023}, ABSENT};

    attendanceOps.addAttendance(&attendance1);
    attendanceOps.addAttendance(&attendance2);
    attendanceOps.addAttendance(&attendance3);
    attendanceOps.addAttendance(&attendance4);

    attendanceOps.findAttendance(1);
    attendanceOps.findAttendance(2);
    attendanceOps.findAttendance(3);
    attendanceOps.findAttendance(4);

    int requestVacation(int employeeId, int requestedDays)
    {
        for (int i = 0; i < 4; i++)
        {
            if (employees[i].id == employeeId)
            {

                employees[i].usedVacationDays += requestedDays;
                printf("Leave request approved. Leave days used: %d\n", employees[i].usedVacationDays);
                return 0;
            }
        }
        printf("Employee not found.\n");
        return -2;
    }

    employeeId = 4;
    requestedDays = 2;

    requestVacation(employeeId, requestedDays);

    employeeId = 2;
    requestedDays = 1;

    int result = requestVacation(employeeId, requestedDays);

    if (result == 0)
    {
        printf("Permission request completed successfully.\n");
    }
    else if (result == -1)
    {
        printf("Permission request failed. Weekly leave limit exceeded.\n");
    }
    else
    {
        printf("Employee not found.\n");
    }

    int deleteResult = deleteEmployee(4);
    if (deleteResult == 0)
    {
        printf("Employee information was successfully deleted.\n");
    }
    else
    {
        printf("An error occurred while deleting employee information.\n");
    }
    
    Employee updatedEmployee;
    updatedEmployee.id = 4;
    updatedEmployee.name = "Mikasa Ackermann";
    updatedEmployee.type = WORKER;
    updatedEmployee.usedVacationDays = 0;
    int updateResult = updateEmployee(4, updatedEmployee);
    if (updateResult == 0)
    {
        printf("Employee information has been successfully updated.\n");
    }
    else
    {
        printf("An error occurred while updating employee information.\n");
    }

    return 0;
}
