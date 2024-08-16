#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
#include "attendance.h"

Employee *createEmployee(int id, char *name, EmployeeType type)
{
    Employee *newEmployee = (Employee *)malloc(sizeof(Employee));
    if (newEmployee == NULL)
    {
         fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newEmployee->id = id;
    
    newEmployee->name = (char *)malloc(strlen(name) + 1);
    if (newEmployee->name == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        free(newEmployee);
        exit(EXIT_FAILURE);
    }
    strcpy(newEmployee->name, name);

    newEmployee->type = type;

    newEmployee->usedVacationDays = 0;
    return newEmployee;
}

int addEmployee(Employee employee)
{
    FILE *file = fopen("employee_database.txt", "a"); // Store data in files and use the FILE pointer.

    if (file == NULL)
    {
        fprintf(stderr, "Dosya açma hatası\n");
        return -1; 
    }

char* nameCopy = strdup(employee.name);
if(nameCopy == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    fclose(file);
    return -1; 
}
fprintf(file, "%d,%s,%d\n", employee.id, nameCopy, employee.type);
free(nameCopy);

    fclose(file);

    return 0; 
}
int updateEmployee(int id, Employee updatedEmployee) {
    FILE *file = fopen("employee_database.txt", "r+");
    if (file == NULL) {
        fprintf(stderr, "File opening error\n");
        return -1; 
    }
    Employee currentEmployee;

    while (fscanf(file, "%d,%49[^,],%d\n", &currentEmployee.id, currentEmployee.name, &currentEmployee.type) == 3) {
        if (currentEmployee.id == id) {

            fseek(file, -1 * (strlen(currentEmployee.name) + 1 + sizeof(currentEmployee.type)), SEEK_CUR);

            fprintf(file, "%d,%s,%d\n", updatedEmployee.id, updatedEmployee.name, updatedEmployee.type);
            fclose(file);
            return 0; 
        }
    }
    if (updatedEmployee.usedVacationDays <= 5) {
                fprintf(file, "%d,%s,%d\n", updatedEmployee.id, updatedEmployee.name, updatedEmployee.type);
                fclose(file);
                return 0; 
            } else {
                printf("Updated days off exceed limits.\n");
                fclose(file);
                return -1; 
            }
    fclose(file);
    return -1; 
}

int deleteEmployee(int id) {
   FILE *file = fopen("employee_database.txt", "r+");
    if (file == NULL) {
        fprintf(stderr, "File opening error for reading\n");
        return -1; 
    }

    Employee currentEmployee;
    FILE *tempFile = fopen("temp_database.txt", "w");
    if (tempFile == NULL) {
        fprintf(stderr, "File opening error for writing\n");
        fclose(file);
        return -1; 
    }

    int deleted = 0;

    while (fscanf(file, "%d,%49[^,],%d\n", &currentEmployee.id, currentEmployee.name, &currentEmployee.type) == 3) {
        if (currentEmployee.id == id) {
           
    currentEmployee.usedVacationDays = 0;

    deleted = 1;
    continue;
}

    fprintf(tempFile, "%d,%s,%d\n", currentEmployee.id, currentEmployee.name, currentEmployee.type);
}

    fclose(file);
    fclose(tempFile);

    if (!deleted) {
        fprintf(stderr, "Employee ID %d not found\n", id);
        remove("temp_database.txt");
        return -1; 
    }

    remove("employee_database.txt");
    rename("temp_database.txt", "employee_database.txt");

    return 0; 
}
void findEmployeeInFile(int id) {
    FILE *file = fopen("employee_database.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "File opening error\n");
        return;
    }

    Employee currentEmployee;

    while (fscanf(file, "%d,%49[^,],%d\n", &currentEmployee.id, currentEmployee.name, &currentEmployee.type) == 3) {
        if (currentEmployee.id == id) {
            printf("Employee found in file.\n");
            printf("ID: %d\n", currentEmployee.id);
            printf("Name: %s\n", currentEmployee.name);
            printf("Type: %s\n", currentEmployee.type == WORKER ? "Worker" : "Manager");
            fclose(file);
            return;
        }
    }

    printf("Employee not found in file.\n");
    fclose(file);
}

