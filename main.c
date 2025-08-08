#include <stdio.h>
#include <stdlib.h>
#include "gradesManagement.h"

int main() {
    int choice;
    do {
        printf("1. Add Student \n");
        printf("2. Display Grades \n");
        printf("3. Modify Student Data \n");
        printf("4. Delete Student\n");
        printf("5. Display Class Average \n");
        printf("6. Make List of Admitted Students \n");
        printf("7. Exit Program \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addStudent(); 
			break;
            case 2: displayGrades();
			 break;
            case 3: modifyStudentName();
			 break;
            case 4: deleteStudent(); 
			break;
            case 5: calculateClassAverage();
			 break;
            case 6: makeAdmittedList();
			 break;
            case 7:
            return 0;
            default: printf("Invalid choice\n");
			 break;
        }
    } while (choice != 7);
    return 0;
}