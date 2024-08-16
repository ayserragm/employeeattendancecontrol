#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum
{
    WORKER,
    MANAGER,
} EmployeeType;

// Structs
typedef struct
{
    int id;
    char *name;
    EmployeeType type; 
   int usedVacationDays;
} Employee;

Employee *createEmployee(int id, char *name,EmployeeType type);
int addEmployee(Employee employee);
int updateEmployee(int id, Employee updatedEmployee);
int deleteEmployee(int id);
void findEmployeeInFile(int id);

#endif