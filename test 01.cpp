#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// A class to demonstrate object-oriented programming
class Employee {
public:
    string name;
    int id;
    double salary;

    Employee() : name("Unknown"), id(0), salary(0.0) {}
    Employee(string n, int i, double s) : name(n), id(i), salary(s) {}

    void display() const {
        cout << "Name: " << name << "\nID: " << id << "\nSalary: " << salary << endl;
    }
};

// Function to generate a vector of random employees
vector<Employee> generateEmployees(int count) {
    vector<Employee> employees;
    string names[] = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Helen"};
    srand(time(0));
    for (int i = 0; i < count; ++i) {
        string name = names[rand() % 8];
        int id = 1000 + rand() % 9000;
        double salary = 30000 + (rand() % 20000);
        employees.push_back(Employee(name, id, salary));
    }
    return employees;
}

// Function to write employees to a file
void saveEmployeesToFile(const vector<Employee>& employees, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    for (const auto& emp : employees) {
        outFile << emp.name << " " << emp.id << " " << emp.salary << "\n";
    }
    outFile.close();
}

// Function to read employees from a file
vector<Employee> loadEmployeesFromFile(const string& filename) {
    vector<Employee> employees;
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return employees;
    }
    string name;
    int id;
    double salary;
    while (inFile >> name >> id >> salary) {
        employees.push_back(Employee(name, id, salary));
    }
    inFile.close();
    return employees;
}

// Sorting employees by salary
void sortEmployeesBySalary(vector<Employee>& employees) {
    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.salary < b.salary;
    });
}

// A function to simulate some calculations
double calculateAverageSalary(const vector<Employee>& employees) {
    if (employees.empty()) return 0.0;
    double total = 0;
    for (const auto& emp : employees) {
        total += emp.salary;
    }
    return total / employees.size();
}

// Main program
int main() {
    int numEmployees = 50;
    vector<Employee> employees = generateEmployees(numEmployees);

    cout << "Generated Employees:\n";
    for (const auto& emp : employees) {
        emp.display();
        cout << "-----------------------\n";
    }

    string filename = "employees.txt";

    // Save to file
    saveEmployeesToFile(employees, filename);

    // Load from file
    vector<Employee> loadedEmployees = loadEmployeesFromFile(filename);

    cout << "\nLoaded Employees from file:\n";
    for (const auto& emp : loadedEmployees) {
        emp.display();
        cout << "-----------------------\n";
    }

    // Sort employees by salary
    sortEmployeesBySalary(loadedEmployees);
    cout << "\nEmployees sorted by salary:\n";
    for (const auto& emp : loadedEmployees) {
        emp.display();
        cout << "-----------------------\n";
    }

    // Calculate average salary
    double avgSalary = calculateAverageSalary(loadedEmployees);
    cout << "\nAverage Salary: " << avgSalary << endl;

    // Demonstrate some loops
    cout << "\nCount from 1 to 10:\n";
    for (int i = 1; i <= 10; ++i) {
        cout << i << " ";
    }
    
    cout << "\n";

    // Using while loop
    int count = 10;
    cout << "Count down from 10:\n";
    while (count > 0) {
        cout << count << " ";
        --count;
    }
    cout << "\n";

    // Demonstrate a simple function call
    cout << "\nTest of a simple function:\n";
    auto factorial = [](int n) -> long long {
        long long result = 1;
        for (int i = 2; i <= n; ++i)
            result *= i;
        return result;
    };
    int number = 5;
    cout << "Factorial of " << number << " is " << factorial(number) << endl;

    return 0;
}