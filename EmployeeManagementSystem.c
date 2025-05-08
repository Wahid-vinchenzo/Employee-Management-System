#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char name[256];
  char department[256];
  float salary;
} Employee;

#define MAX_EMPLOYEES 100
Employee employees[MAX_EMPLOYEES];
int numEmployees;

#define EMPLOYEE_FILE "employees.txt"

int readEmployeesFromFile(Employee *employees) {
  FILE *file = fopen(EMPLOYEE_FILE, "r");
  if (file == NULL) {
    return 0;
  }

  // Read each employee from the file and store them in the employees array
  int numEmployees = 0;
  while (fscanf(file, "%d %s %s %f", &employees[numEmployees].id,
                employees[numEmployees].name,
                employees[numEmployees].department,
                &employees[numEmployees].salary) == 4) {
    numEmployees++;
  }

  // Close the file and return the number of employees read
  fclose(file);
  return numEmployees;
}

void writeEmployeesToFile(Employee *employees, int numEmployees) {
  // Open the file for writing
  FILE *file = fopen(EMPLOYEE_FILE, "w");
  if (file == NULL) {
    printf("Error opening file!\n");
    return;
  }

  // Write each employee to the file
  for (int i = 0; i < numEmployees; i++) {
    fprintf(file, "%d %s %s %.2f\n", employees[i].id, employees[i].name,
            employees[i].department, employees[i].salary);
  }

  // Close the file
  fclose(file);
}

void addEmployee(char *name, char *department, float salary) {
  int id;

  // strupr(name);
  // strupr(department);
  employees[numEmployees].id = numEmployees + 1;
  Employee *employee = &employees[numEmployees];
  strncpy(employee->name, name, 256);
  strncpy(employee->department, department, 256);
  employee->salary = salary;
  numEmployees++;
  writeEmployeesToFile(employees, numEmployees);
}

void addEmployees() {
  numEmployees = readEmployeesFromFile(employees);
  int id;
  char name[256], department[256];
  float salary;
  int highestId = 0;
  int i;
  for (i = 0; i < numEmployees; i++) {
    if (employees[i].id > highestId) {
      highestId = employees[i].id;
    }
  }
  employees[numEmployees].id = highestId + 1;
  printf("Enter the employee's name: ");
  scanf("%s", name);
  printf("Enter the employee's department: ");
  scanf("%s", department);
  printf("Enter the employee's salary: ");
  // scanf("%.2f", &salary);
  scanf("%f", &salary);
  for (int i = 0; department[i] != '\0'; i++) {
    department[i] = toupper(department[i]);
  }

  Employee *employee = &employees[numEmployees];
  strncpy(employee->name, name, 256);
  strncpy(employee->department, department, 256);
  employee->salary = salary;
  numEmployees++;
  writeEmployeesToFile(employees, numEmployees);
}

void printEmployees() {
  // Read the employee list from the file
  int numEmployees = readEmployeesFromFile(employees);
  // Print the details of each employee
  for (int i = 0; i < numEmployees; i++) {
    Employee *employee = &employees[i];
    printf("ID: %d, Name: %s, Department: %s, Salary: %.2f\n", employee->id,
           employee->name, employee->department, employee->salary);
  }
}

void printMenu() {
  printf("Employee Management System\n");
  printf("1. Add Employee\n");
  printf("2. View Employees\n");
  printf("3. Search Employee\n");
  printf("4. Modify Employee\n");
  printf("5. Delete Employee\n");
  printf("6. Reset All\n");
  printf("7. Quit\n");
}
void searchSalaryDescending(Employee *employees, int numEmployees) {
  // Sort the employees array by salary in descending order
  numEmployees = readEmployeesFromFile(employees);
  for (int i = 0; i < numEmployees - 1; i++) {
    for (int j = i + 1; j < numEmployees; j++) {
      if (employees[i].salary < employees[j].salary) {
        Employee temp = employees[i];
        employees[i] = employees[j];
        employees[j] = temp;
      }
    }
  }

  // Print the sorted employee list
  printf("Employees sorted by salary (descending):\n");
  printf("\n");
  for (int i = 0; i < numEmployees; i++) {
    Employee *employee = &employees[i];
    printf("ID: %d, Name: %s, Department: %s, Salary: %.2f\n", employee->id,
           employee->name, employee->department, employee->salary);
  }
  printf("\n");
}

void searchEmployee() {
  int c = 0;
  printf("1. Search by ID\n");
  printf("2. Search by name\n");
  printf("3. Search by department\n");
  printf("4. Search by Salary\n");
  printf("Enter your choice: ");
  int searchType;
  scanf("%d", &searchType);
  printf("\n");

  switch (searchType) {
  case 1: {
    // ID Search
    int id;
    printf("Enter the employee's ID: ");
    scanf("%d", &id);
    printf("\n");

    for (int i = 0; i < numEmployees; i++) {
      Employee *employee = &employees[i];
      if (employee->id == id) {
        printf("ID: %d, Name: %s, Department: %s\n", employee->id,
               employee->name, employee->department);
        return;
      }
    }
    printf("Employee not found.\n");
    break;
  }
  case 2: {
    // Name Search
    char name[256];
    printf("Enter the employee's name: ");
    scanf("%s", name);
    printf("\n");

    for (int i = 0; i < numEmployees; i++) {
      Employee *employee = &employees[i];
      if (strcmp(employee->name, name) == 0) {
        printf("ID: %d, Name: %s, Department: %s\n", employee->id,
               employee->name, employee->department);
        return;
      }
    }

    printf("Employee not found.\n");
    break;
  }
  case 3: {
    // Dept Search
    char department[256];
    printf("Enter the employee's department: ");
    scanf("%s", department);
    printf("\n");
    for (int i = 0; department[i] != '\0'; i++) {
      department[i] = toupper(department[i]);
    }

    for (int i = 0; i < numEmployees; i++) {
      Employee *employee = &employees[i];
      if (strcmp(employee->department, department) == 0) {
        printf("ID: %d, Name: %s, Department: %s\n", employee->id,
               employee->name, employee->department);
        c += 1;
        // return;
      }
    }
    printf("\n");

    if (c == 0)
      printf("Employee not found.\n");
    break;
  }
  case 4: {
    searchSalaryDescending(employees, numEmployees);
    break;
  }
  default:
    printf("Invalid option selected.\n");
  }
}
void modifySalary(int id) {
  // Read the employee list from the file
  int numEmployees = readEmployeesFromFile(employees);

  // Prompt the user to enter the employee's ID
  // printf("Enter the employee's ID: ");
  // scanf("%d", &id);

  // Find the employee with the specified ID
  int employeeIndex = -1;
  for (int i = 0; i < numEmployees; i++) {
    if (employees[i].id == id) {
      employeeIndex = i;
      break;
    }
  }

  // If the employee was found, ask the user for their password
  if (employeeIndex >= 0) {
    Employee *employee = &employees[employeeIndex];
    printf("Current salary: %f\n", employee->salary);
    char password[256];
    while (1) {
      printf("Enter the password to modify the salary: ");
      scanf("%s", password);

      // Check if the password is correct
      if (strcmp(password, "admin") == 0) {
        // If the password is correct, ask the user for the new salary
        printf("Enter the new salary: ");
        scanf("%f", &employee->salary);

        // Write the updated employee list to the file
        writeEmployeesToFile(employees, numEmployees);
        break;
      } else if (strcmp(password, "cancel") == 0) {
        // If the user entered "cancel", cancel the operation and return to the
        // main menu
        printf("Operation cancelled.\n");
        break;
      } else {
        // If the password is incorrect, ask the user to try again
        printf("Incorrect password. Try again or enter 'cancel' to cancel the "
               "operation.\n");
      }
    }
  } else {
    printf("Employee not found.\n");
  }
}
void modifyEmployee() {
  // Read the employee list from the file
  int numEmployees = readEmployeesFromFile(employees);

  // Prompt the user to enter the employee's ID
  int id;
  printf("Enter the employee's ID: ");
  scanf("%d", &id);

  // Find the employee with the specified ID
  int employeeIndex = -1;
  for (int i = 0; i < numEmployees; i++) {
    if (employees[i].id == id) {
      employeeIndex = i;
      break;
    }
  }

  // If the employee was found, ask the user for the new details
  if (employeeIndex >= 0) {
    Employee *employee = &employees[employeeIndex];
    char name[256], department[256];
    strncpy(name, employee->name, 256);
    strncpy(department, employee->department, 256);
    printf("Current name: %s\n", name);
    printf("Enter the new name (enter 'skip' to skip): ");
    scanf("%s", employee->name);
    if (strcmp(employee->name, "skip") == 0) {
      // If the user entered "skip", use the current name
      strncpy(employee->name, name, 256);
    }
    printf("Current department: %s\n", department);
    printf("Enter the new department: ");
    scanf("%s", employee->department);
    for (int i = 0; employee->department[i] != '\0'; i++) {
      employee->department[i] = toupper(employee->department[i]);
    }
    if (strcmp(employee->department, "SKIP") == 0) {
      // If the user entered "skip", use the current dept name
      strncpy(employee->department, department, 256);
    }
    char confirm[256];
    printf("Do you want to modify the salary?(yes/no):");
    scanf("%s", confirm);
    if (strcmp(confirm, "yes") == 0) {
      modifySalary(id);
      // If the user wants to modify the salary,
    }
    // Write the updated employee list to the file

    writeEmployeesToFile(employees, numEmployees);
  } else {
    printf("Employee not found.\n");
  }
}

void resetDatabase() {
  char password[256];
  while (1) {
    printf("Enter the password to reset the data: ");
    scanf("%s", password);

    if (strcmp(password, "admin") == 0) {
      // If the password is correct, reset the data
      numEmployees = 0;
      writeEmployeesToFile(employees, numEmployees);
      break;
    } else if (strcmp(password, "cancel") == 0) {
      // If the user entered "cancel", cancel the operation and return to the
      // main menu
      printf("Operation cancelled.\n");
      break;
    } else {
      // If the password is incorrect
      printf("Incorrect password. Try again or enter 'cancel' to cancel the "
             "operation.\n");
    }
  }
}

void deleteEmployee() {
  // Print the current list of employees
  printEmployees();

  // Read the employee list from the file
  int numEmployees = readEmployeesFromFile(employees);

  // Prompt the user for their password
  char password[256];
  while (1) {
    printf("Enter the password to delete an employee: ");
    scanf("%s", password);

    // Check if the password is correct
    if (strcmp(password, "admin") == 0) {
      // If the password is correct, prompt the user to enter the employee's ID
      int id;
      printf("Enter the employee's ID: ");
      scanf("%d", &id);

      // Find the employee with the specified ID
      int employeeIndex = -1;
      for (int i = 0; i < numEmployees; i++) {
        if (employees[i].id == id) {
          employeeIndex = i;
          break;
        }
      }

      // If the employee was found, delete them from the array
      if (employeeIndex >= 0) {
        for (int i = employeeIndex; i < numEmployees - 1; i++) {
          employees[i] = employees[i + 1];
        }
        numEmployees--;

        // Write the updated employee list to the file
        writeEmployeesToFile(employees, numEmployees);
        printf("Employee deleted.\n");
      } else {
        printf("Employee not found.\n");
      }
      break;
    } else if (strcmp(password, "cancel") == 0) {
      // If the user entered "cancel", cancel the operation and return to the
      // main menu
      printf("Operation cancelled.\n");
      break;
    } else {
      // If the password is incorrect, ask the user to try again
      printf("Incorrect password. Try again or enter 'cancel' to cancel the "
             "operation.\n");
    }
  }
}

int main() {
  numEmployees = readEmployeesFromFile(employees);

  // first e nije theke neya sample
  if (numEmployees == 0) {
    addEmployee("A", "CSE", 12000);
    addEmployee("B", "EEE", 20000);
    addEmployee("C", "CCE", 15000);
    // addEmployee("D", "CSE", 25000);
    // addEmployee("E", "ETE", 20000);
  }

  // erpor main program
  while (1) {
    printMenu();
    printf("Enter your choice: ");
    int option;
    scanf("%d", &option);
    // eta diye ager lekha gula muche dibe

    // For Linux
    //system("clear");

    // For Windows
      system("cls");

    switch (option) {
    case 1:
      addEmployees();
      break;
    case 2:
      printEmployees();
      break;
    case 3:
      searchEmployee();
      break;
    case 4:
      modifyEmployee();
      break;
    case 5:
      deleteEmployee();
      break;
    case 6:
      resetDatabase();
      break;
    case 7:
      return 0;
    default:
      printf("Invalid option selected.\n");
    }
  }

  return 0;
}
