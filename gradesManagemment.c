#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gradesManagement.h"

typedef struct {
    int id;
    char firstName[50], lastName[50];
    float mark1, mark2;
} Student;

void addStudent() {
    FILE *file = fopen("data.txt", "a");
    if (file == NULL) {
        return;
    }
    Student s , temp ;
    printf("Enter student ID: ");
    scanf("%d", &s.id);

    FILE *checkFile = fopen("data.txt", "r");
    if (checkFile != NULL) {
        while (fscanf(checkFile, "%d %s %s %f %f", &temp.id, temp.firstName, temp.lastName, &temp.mark1, &temp.mark2) == 5) {
            if (temp.id == s.id) {
                printf("Student with ID %d already exists.\n", s.id);
                fclose(file);
                fclose(checkFile);
                return;
            }
        }
        fclose(checkFile);
    }

    printf("Enter first name: ");
    scanf("%s", s.firstName);
    printf("Enter last name: ");
    scanf("%s", s.lastName);
    printf("Enter mark 1: ");
    scanf("%f", &s.mark1);
    printf("Enter mark 2: ");
    scanf("%f", &s.mark2);

    fprintf(file, "%d %s %s %.2f %.2f\n", s.id, s.firstName, s.lastName, s.mark1, s.mark2);
    fclose(file);
    printf("Student with ID %d added successfully.\n", s.id);
}

void displayGrades() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    Student s;
    printf("\n Student Grades \n");
    printf("ID\tName\t\tMark 1\tMark 2\n");

    while (fscanf(file, "%d %s %s %f %f", &s.id, s.firstName, s.lastName, &s.mark1, &s.mark2) == 5) {
        printf("%d\t%s %s\t%.2f\t%.2f\n", s.id, s.firstName, s.lastName, s.mark1, s.mark2);
    }

    fclose(file);
}

void modifyStudentName() {
    FILE *file = fopen("data.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        return;
    }

    Student s;
    int sID , found = 0;

    printf("Enter the ID of the student you want to modify: ");
    scanf("%d", &sID);

    while (fscanf(file, "%d %s %s %f %f", &s.id, s.firstName, s.lastName, &s.mark1, &s.mark2) == 5) {
        if (s.id == sID) {
            found = 1;
            printf("Enter new first name for student with ID %d: ", sID);
            scanf("%s", s.firstName);
            printf("Enter new last name for student with ID %d: ", sID);
            scanf("%s", s.lastName);
        }
        fprintf(tempFile, "%d %s %s %.2f %.2f\n", s.id, s.firstName, s.lastName, s.mark1, s.mark2);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("data.txt");
        rename("temp.txt", "data.txt");
        printf("Student with ID %d name modified successfully.\n", sID);
    } else {
        remove("temp.txt");
        printf("Student with ID %d not found.\n", sID);
    }
}

void deleteStudent() {
    FILE *file = fopen("data.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        return;
    }

    Student s;
    int sID, found = 0;

    printf("Enter the ID of the student you want to delete: ");
    scanf("%d", &sID);

    while (fscanf(file, "%d %s %s %f %f", &s.id, s.firstName, s.lastName, &s.mark1, &s.mark2) == 5) {
        if (s.id == sID) {
            found = 1;
            printf("Student with ID %d deleted.\n", sID);
            continue; 
        }
        fprintf(tempFile, "%d %s %s %.2f %.2f\n", s.id, s.firstName, s.lastName, s.mark1, s.mark2);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("data.txt");
        rename("temp.txt", "data.txt");
    } else {
        remove("temp.txt");
        printf("Student with ID %d not found.\n", sID);
    }
}
void calculateClassAverage() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        return;
    }

    Student s;
    float totalMarks = 0;
    int numStudents = 0;

    while (fscanf(file, "%d %s %s %f %f", &s.id, s.firstName, s.lastName, &s.mark1, &s.mark2) == 5) {
        totalMarks += (s.mark1 + s.mark2) / 2;
        numStudents++;
    }

    fclose(file);

    if (numStudents > 0) {
        float classAverage = totalMarks / numStudents;
        printf("Class Average: %.2f\n", classAverage);
    } else {
        printf("No students in the class.\n");
    }
}

void makeAdmittedList() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        return;
    }

    Student s;

    printf("\nAdmitted Students \n");
    printf("ID\tName\t\tAverage\n");

    while (fscanf(file, "%d %s %s %f %f", &s.id, s.firstName, s.lastName, &s.mark1, &s.mark2) == 5) {
        float average = (s.mark1 + s.mark2) / 2;
        if (average >= 10.0) {
            printf("%d\t%s %s\t%.2f\n", s.id, s.firstName, s.lastName, average);
        }
    }

    fclose(file);
}