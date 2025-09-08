#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int roll_no;
    char name[50];
    int marks;
} Student;

Student students[MAX];
int n = 0;  // Current number of students

// Insert a student
void insert_student(int roll_no, char name[], int marks) {
    if (n >= MAX) {
        printf("Student list is full!\n");
        return;
    }
    students[n].roll_no = roll_no;
    strcpy(students[n].name, name);
    students[n].marks = marks;
    n++;
}

// Display all students
void display_students() {
    if (n == 0) {
        printf("No records to display.\n");
        return;
    }
    printf("Roll No\tName\t\tMarks\n");
    printf("----------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%-15s%d\n", students[i].roll_no, students[i].name, students[i].marks);
    }
}

// Linear Search by roll number
int linear_search(int roll_no) {
    for (int i = 0; i < n; i++) {
        if (students[i].roll_no == roll_no)
            return i;
    }
    return -1;
}

// Binary Search by roll number (array must be sorted by roll_no)
int binary_search(int roll_no) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (students[mid].roll_no == roll_no)
            return mid;
        else if (students[mid].roll_no < roll_no)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Delete student by roll number
void delete_student(int roll_no) {
    int pos = linear_search(roll_no);
    if (pos == -1) {
        printf("Student with roll no %d not found.\n", roll_no);
        return;
    }
    for (int i = pos; i < n - 1; i++) {
        students[i] = students[i + 1];
    }
    n--;
    printf("Student deleted successfully.\n");
}

// Update student by roll number
void update_student(int roll_no) {
    int pos = linear_search(roll_no);
    if (pos == -1) {
        printf("Student with roll no %d not found.\n", roll_no);
        return;
    }
    printf("Enter new name: ");
    scanf(" %[^\n]", students[pos].name);
    printf("Enter new marks: ");
    scanf("%d", &students[pos].marks);
    printf("Student updated successfully.\n");
}

// Bubble sort by marks (descending)
void bubble_sort_by_marks() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].marks < students[j + 1].marks) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// Bubble sort by roll number (ascending)
void bubble_sort_by_roll_no() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].roll_no > students[j + 1].roll_no) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// Filter students with marks above threshold
void filter_students(int min_marks) {
    printf("Students with marks >= %d:\n", min_marks);
    printf("Roll No\tName\t\tMarks\n");
    printf("----------------------------------\n");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (students[i].marks >= min_marks) {
            printf("%d\t%-15s%d\n", students[i].roll_no, students[i].name, students[i].marks);
            found = 1;
        }
    }
    if (!found)
        printf("No students found with marks >= %d\n", min_marks);
}

int main() {
    int choice, roll_no, marks;
    char name[50];

    while (1) {
        printf("\nStudent Record Manager\n");
        printf("1. Insert Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Display All Students\n");
        printf("5. Linear Search (by Roll No)\n");
        printf("6. Binary Search (by Roll No)\n");
        printf("7. Sort by Marks (Descending)\n");
        printf("8. Sort by Roll No (Ascending)\n");
        printf("9. Filter Students by Marks\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Roll No: ");
                scanf("%d", &roll_no);
                printf("Enter Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Marks: ");
                scanf("%d", &marks);
                insert_student(roll_no, name, marks);
                break;

            case 2:
                printf("Enter Roll No to delete: ");
                scanf("%d", &roll_no);
                delete_student(roll_no);
                break;

            case 3:
                printf("Enter Roll No to update: ");
                scanf("%d", &roll_no);
                update_student(roll_no);
                break;

            case 4:
                display_students();
                break;

            case 5:
                printf("Enter Roll No to search (Linear Search): ");
                scanf("%d", &roll_no);
                {
                    int pos = linear_search(roll_no);
                    if (pos != -1)
                        printf("Found: %d, %s, %d\n", students[pos].roll_no, students[pos].name, students[pos].marks);
                    else
                        printf("Student not found.\n");
                }
                break;

            case 6:
                bubble_sort_by_roll_no(); // Make sure array is sorted for binary search
                printf("Enter Roll No to search (Binary Search): ");
                scanf("%d", &roll_no);
                {
                    int pos = binary_search(roll_no);
                    if (pos != -1)
                        printf("Found: %d, %s, %d\n", students[pos].roll_no, students[pos].name, students[pos].marks);
                    else
                        printf("Student not found.\n");
                }
                break;

            case 7:
                bubble_sort_by_marks();
                printf("Students sorted by marks (descending).\n");
                break;

            case 8:
                bubble_sort_by_roll_no();
                printf("Students sorted by roll no (ascending).\n");
                break;

            case 9:
                printf("Enter minimum marks to filter: ");
                scanf("%d", &marks);
                filter_students(marks);
                break;

            case 10:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}