#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a student
struct Student {
  char name[50];
  int studentId;
  float marks;
};

// Global variables to manage the list of students
struct Student *students = NULL;
int studentCount = 0;
int capacity = 0;

// Function to add a new student
void addStudent() {
  // Increase capacity if needed
  if (studentCount >= capacity) {
    if (capacity == 0) {
      capacity = 10;
    } else {
      capacity = capacity * 2;
    }
    students =
        (struct Student *)realloc(students, capacity * sizeof(struct Student));
  }

  printf("Enter name: ");
  scanf(" %[^\n]s", students[studentCount].name);
  printf("Enter Student ID: ");
  scanf("%d", &students[studentCount].studentId);
  printf("Enter marks: ");
  scanf("%f", &students[studentCount].marks);

  // Check pass/fail
  if (students[studentCount].marks > 40) {
    printf("Result: PASS\n");
  } else {
    printf("Result: FAIL\n");
  }

  studentCount++;
  printf("Student added successfully.\n");
}

// Function to display all students
void displayStudents() {
  if (studentCount == 0) {
    printf("No records found.\n");
    return;
  }
  printf("\n%-20s %-10s %-10s\n", "Name", "Student ID", "Marks");
  printf("--------------------------------------------\n");
  for (int i = 0; i < studentCount; i++) {
    printf("%-20s %-10d %-10.2f\n", students[i].name, students[i].studentId,
           students[i].marks);
  }
}

// Function to search for a student by Student ID
void searchStudent() {
  int id;
  printf("Enter Student ID to search: ");
  scanf("%d", &id);

  for (int i = 0; i < studentCount; i++) {
    if (students[i].studentId == id) {
      printf("\nStudent Found:\n");
      printf("Name: %s\n", students[i].name);
      printf("Student ID: %d\n", students[i].studentId);
      printf("Marks: %.2f\n", students[i].marks);
      return;
    }
  }
  printf("Student not found.\n");
}

// Function to modify a student's record
void modifyStudent() {
  int id;
  printf("Enter Student ID to modify: ");
  scanf("%d", &id);

  for (int i = 0; i < studentCount; i++) {
    if (students[i].studentId == id) {
      printf("Enter new name: ");
      scanf(" %[^\n]s", students[i].name);
      printf("Enter new marks: ");
      scanf("%f", &students[i].marks);
      printf("Student record updated.\n");
      return;
    }
  }
  printf("Student not found.\n");
}

// Function to remove a student
void removeStudent() {
  int id;
  printf("Enter Student ID to remove: ");
  scanf("%d", &id);

  int found = 0;
  for (int i = 0; i < studentCount; i++) {
    if (students[i].studentId == id) {
      // Shift elements to the left
      for (int j = i; j < studentCount - 1; j++) {
        students[j] = students[j + 1];
      }
      studentCount--;
      found = 1;
      printf("Student removed successfully.\n");
      break;
    }
  }
  if (found == 0) {
    printf("Student not found.\n");
  }
}

// Function to calculate average marks
void calculateAverage() {
  if (studentCount == 0) {
    printf("No students to calculate average.\n");
    return;
  }
  float sum = 0;
  for (int i = 0; i < studentCount; i++) {
    sum = sum + students[i].marks;
  }
  printf("Average Marks: %.2f\n", sum / studentCount);
}

// Function to sort students using Bubble Sort
void sortStudents() {
  int choice;
  printf("Sort by marks: 1. Ascending 2. Descending\nChoice: ");
  scanf("%d", &choice);

  struct Student temp;
  for (int i = 0; i < studentCount - 1; i++) {
    for (int j = 0; j < studentCount - i - 1; j++) {
      int swap = 0;
      if (choice == 1) {
        if (students[j].marks > students[j + 1].marks) {
          swap = 1;
        }
      } else if (choice == 2) {
        if (students[j].marks < students[j + 1].marks) {
          swap = 1;
        }
      }

      if (swap == 1) {
        temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
  printf("Students sorted.\n");
}

// Function to save records to a file
void saveToFile() {
  FILE *file = fopen("students.txt", "w");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }
  fprintf(file, "%d\n", studentCount);
  for (int i = 0; i < studentCount; i++) {
    fprintf(file, "%s\n%d\n%.2f\n", students[i].name, students[i].studentId,
            students[i].marks);
  }
  fclose(file);
  printf("Records saved.\n");
}

// Function to load records from a file
void loadFromFile() {
  FILE *file = fopen("students.txt", "r");
  if (file == NULL) {
    return; // File might not exist yet
  }

  int fileCount;
  fscanf(file, "%d", &fileCount);

  // Resize array if needed
  if (fileCount > capacity) {
    capacity = fileCount;
    students =
        (struct Student *)realloc(students, capacity * sizeof(struct Student));
  }

  studentCount = 0;
  for (int i = 0; i < fileCount; i++) {
    fscanf(file, " %[^\n]s", students[i].name);
    fscanf(file, "%d", &students[i].studentId);
    fscanf(file, "%f", &students[i].marks);
    studentCount++;
  }
  fclose(file);
  printf("Records loaded.\n");
}

int main() {
  char userName[50];

  printf("Welcome to the Student Record System!\n");
  printf("Please enter your name: ");
  scanf(" %[^\n]s", userName);
  printf("Hello, %s!\n", userName);

  loadFromFile();

  int choice;
  while (1) {
    printf("\n--- Menu ---\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student\n");
    printf("4. Modify Student\n");
    printf("5. Remove Student\n");
    printf("6. Calculate Average Marks\n");
    printf("7. Sort Students\n");
    printf("8. Save and Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
      addStudent();
    } else if (choice == 2) {
      displayStudents();
    } else if (choice == 3) {
      searchStudent();
    } else if (choice == 4) {
      modifyStudent();
    } else if (choice == 5) {
      removeStudent();
    } else if (choice == 6) {
      calculateAverage();
    } else if (choice == 7) {
      sortStudents();
    } else if (choice == 8) {
      saveToFile();
      printf("Exiting...\n");
      break;
    } else {
      printf("Invalid choice.\n");
    }
  }

  free(students);
  return 0;
}
