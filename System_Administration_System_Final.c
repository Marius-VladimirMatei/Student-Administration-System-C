#include <stdio.h>
#include <string.h>

// Variable to define the array/struct size
#define max_students 30

// Define the structure for articles using typedef
typedef struct {
    char name[50];
    int matriculationNumber;
    float grade[5];
    float average;
} Student;

/*Functions prototypes |
int* itemCount = > the pointer that indicates to the item number / order in the array */



//rename: addStudent searchStudent 
void studentAdd(Student students[], int* studentCount);
void showStudents(Student students[], int studentCount);
void seekStudent(Student students[], int studentCount);
void calculateAverageOfAllStudents(Student students[], int studentCount);
float calculateAverageGrade(float grades[], int numGrades);

int main() {
    Student students[max_students];
    int studentCount = 0;
    int choice;


    while (1) {
        // Display the menu
        printf_s("1. Add new student\n");
        printf_s("2. Show all students\n");
        printf_s("3. Search for a student\n");
        printf_s("4. Calculate the average grade of all students\n");
        printf_s("5. Exit\n");
        printf_s("Choose an option (1-5): \n");
        printf_s("_________________________________________\n");
        scanf_s("%d", &choice);

        // Clear input buffer
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            studentAdd(students, &studentCount);
            break;
        case 2:
            showStudents(students, studentCount);
            break;
        case 3:
            seekStudent(students, studentCount);
            break;
        case 4:
            calculateAverageOfAllStudents(students, studentCount);
            break;
        case 5:
            printf_s("Exiting...\n");
            return 0;
        default:
            printf_s("Invalid choice. Please try again.\n");
        }
    }
}


// Function to add a student to the list
void studentAdd(Student students[], int* studentCount) {
    if (*studentCount >= max_students) {
        printf_s("Student list is full.\n");
        printf_s("_________________________________________\n");
        return;
    }

    Student newStudent;

    // Input student name
    printf_s("Enter the name of the student: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);

    // Remove newline from fgets
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; 

    // Input matriculation number
    printf_s("Enter matriculation number (positive integer): ");
    while (scanf_s("%d", &newStudent.matriculationNumber) != 1 || newStudent.matriculationNumber <= 0) {
        printf_s("Invalid matriculation number. Enter a positive integer: ");

        // Clear input buffer
        while (getchar() != '\n'); 
    }

    // Input grades
    printf_s("Enter 5 grades (between 1.0 and 5.0):\n");
    for (int i = 0; i < 5; i++) {
        do {
            printf_s("Grade %d: ", i + 1);
            scanf_s("%f", &newStudent.grade[i]);
            if (newStudent.grade[i] < 1.0 || newStudent.grade[i] > 5.0) {
                printf_s("Invalid grade. Please enter a grade between 1.0 and 5.0.\n");
                printf_s("_________________________________________\n");
            }
        } while (newStudent.grade[i] < 1.0 || newStudent.grade[i] > 5.0);
    }

    // Calculate and assign average grade
    newStudent.average = calculateAverageGrade(newStudent.grade, 5);

    // Add student to array
    students[*studentCount] = newStudent;
    (*studentCount)++;
}

// Function to display all students
void showStudents(Student students[], int studentCount) {
    if (studentCount == 0) {
        printf_s("No students in the list.\n");
        printf_s("_________________________________________\n");
        return;
    }
    

    printf_s("Student list:\n");
    for (int i = 0; i < studentCount; i++) {
        printf_s("Student %d:\n", i + 1);
        printf_s("Name: %s\n", students[i].name);
        printf_s("Matriculation Number: %d\n", students[i].matriculationNumber);
        printf_s("Grades: ");
        for (int j = 0; j < 5; j++) {
            printf_s("%.2f ", students[i].grade[j]);
        }
        printf_s("\nAverage: %.2f\n", students[i].average);
    }
    printf_s("_________________________________________\n");
}


// Function to search for a student by matriculation number
void seekStudent(Student students[], int studentCount) {
    int matriculationNumber;
    printf_s("Enter the matriculation number to search for: \n");
    printf_s("_________________________________________\n");
    scanf_s("%d", &matriculationNumber);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].matriculationNumber == matriculationNumber) {
            printf_s("Student found:\n");
            printf_s("Name: %s\n", students[i].name);
            printf_s("Matriculation Number: %d\n", students[i].matriculationNumber);
            printf_s("Grades: ");
            for (int j = 0; j < 5; j++) {
                printf_s("%.2f ", students[i].grade[j]);
            }
            printf_s("\nAverage: %.2f\n", students[i].average);
            return;
        }
    }
    printf_s("Student with matriculation number %d not found.\n", matriculationNumber);
    printf_s("_________________________________________\n");
}


// Function to calculate the average of all students' averages
void calculateAverageOfAllStudents(Student students[], int studentCount) {
    if (studentCount == 0) {
        printf_s("No students in the list.\n");
        printf_s("_________________________________________\n");
        return;
    }

    float totalAverage = 0.0;
    for (int i = 0; i < studentCount; i++) {
        totalAverage += students[i].average;
    }
    printf_s("Average grade of all students: %.2f\n", totalAverage / studentCount);
    printf_s("_________________________________________\n");
}

// Helper function to calculate the average grade for a single student
float calculateAverageGrade(float grades[], int numGrades) {
    float sum = 0.0;
    for (int i = 0; i < numGrades; i++) {
        sum += grades[i];
    }
    return sum / numGrades;
}
