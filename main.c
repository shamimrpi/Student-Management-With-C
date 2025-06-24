#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10

char subjects[MAX_SUBJECTS][30];
int subject_count = 0;

struct student {
    char id[30];
    char name[50];
    char department[50];
    float marks[MAX_SUBJECTS];
    float total;
    float actual_average;
    float average;
    float cgpa;
};

struct student students[MAX_STUDENTS];
int count = 0;

const char* getGrade(float avg) {
    if (avg >= 80) return "A+";
    else if (avg >= 75) return "A";
    else if (avg >= 70) return "A-";
    else if (avg >= 65) return "B+";
    else if (avg >= 60) return "B";
    else if (avg >= 55) return "B-";
    else if (avg >= 50) return "C+";
    else if (avg >= 45) return "C";
    else if (avg >= 40) return "D";
    else return "F";
}

float getCGPA(float mark) {
    if (mark >= 80) return 4.00;
    else if (mark >= 75) return 3.75;
    else if (mark >= 70) return 3.50;
    else if (mark >= 65) return 3.25;
    else if (mark >= 60) return 3.00;
    else if (mark >= 55) return 2.75;
    else if (mark >= 50) return 2.50;
    else if (mark >= 45) return 2.25;
    else if (mark >= 40) return 2.00;
    else return 0;
}

float getSubjectWiseNumber(float mark) {
    if (mark >= 80) return 80;
    else if (mark >= 75) return 75;
    else if (mark >= 70) return 70;
    else if (mark >= 65) return 65;
    else if (mark >= 60) return 60;
    else if (mark >= 55) return 55;
    else if (mark >= 50) return 50;
    else if (mark >= 45) return 45;
    else if (mark >= 40) return 40;
    else return 0;
}

void menu() {
    printf("\n====* Student Management Menu *====\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Sort by ID\n");
    printf("\033[1;31m0. Exit\033[0m\n");  
    printf("Enter your choice: ");
}

void setupSubjects() {
    printf("Enter number of subjects: ");
    scanf("%d", &subject_count);
    if (subject_count > MAX_SUBJECTS) {
        printf("Too many subjects. Max allowed: %d\n", MAX_SUBJECTS);
        subject_count = MAX_SUBJECTS;
    }

    for (int i = 0; i < subject_count; i++) {
        printf("Enter name of subject %d: ", i + 1);
        scanf(" %[^\n]", subjects[i]);
    }
}

void addStudent() {
    if (count >= MAX_STUDENTS) {
        printf("Cannot add more students.\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%s", students[count].id);
    printf("Enter Name: ");
    scanf(" %[^\n]", students[count].name);
    printf("Enter Department: ");
    scanf(" %[^\n]", students[count].department);

    float sum = 0, graded_sum = 0,sum_cgpa = 0;
    for (int i = 0; i < subject_count; i++) {
        printf("Enter marks for %s: ", subjects[i]);
        scanf("%f", &students[count].marks[i]);
        sum += students[count].marks[i];
        sum_cgpa += getCGPA(students[count].marks[i]) ;
        graded_sum += getSubjectWiseNumber(students[count].marks[i]);
    }

    students[count].total = sum;
    students[count].actual_average = sum / subject_count;
    students[count].average = graded_sum / subject_count;
    students[count].cgpa = sum_cgpa / subject_count;

    count++;
    printf("Student added successfully.\n");
}

void displayStudents() {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nID: %s\nName: %s\nDepartment: %s\n",
               students[i].id, students[i].name, students[i].department);
        for (int j = 0; j < subject_count; j++) {
            printf("%s Marks:  %.2f & Grade: %s\n", subjects[j], students[i].marks[j], getGrade(students[i].marks[j]));

        }
        printf("Total: %.2f, Average: %.2f, Grade: %s ,CGPA: %.2f\n",
               students[i].total, students[i].actual_average,
               getGrade(students[i].average),students[i].cgpa);
    }
}



void searchStudent() {
    char id[30];
    printf("Enter ID to search: ");
    scanf("%s", id);
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            printf("\nStudent found:\nName: %s\nDepartment: %s\n", students[i].name, students[i].department);
            for (int j = 0; j < subject_count; j++) {
                printf("%s Marks: %.2f\n", subjects[j], students[i].marks[j]);
            }
            printf("Total: %.2f, Average: %.2f, Grade: %s\n",
                   students[i].total, students[i].actual_average,
                   getGrade(students[i].average));
            return;
        }
    }
    printf("Student not found.\n");
}

void updateStudent() {
    char id[30];
    printf("Enter ID to update: ");
    scanf("%s", id);
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", students[i].name);
            printf("Enter new Department: ");
            scanf(" %[^\n]", students[i].department);

            float sum = 0, graded_sum = 0;
            for (int j = 0; j < subject_count; j++) {
                printf("Enter marks for %s: ", subjects[j]);
                scanf("%f", &students[i].marks[j]);
                sum += students[i].marks[j];
                graded_sum += getSubjectWiseNumber(students[i].marks[j]);
            }

            students[i].total = sum;
            students[i].actual_average = sum / subject_count;
            students[i].average = graded_sum / subject_count;

            printf("Student updated successfully.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void deleteStudent() {
    char id[30];
    printf("Enter ID to delete: ");
    scanf("%s", id);
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            printf("Student deleted successfully.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void sortStudents() {
    struct student temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(students[j].id, students[j + 1].id) > 0) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("Students sorted by ID.\n");
}

int main() {
    setupSubjects();  // First subject entry

    int choice;
    do {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: sortStudents(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
