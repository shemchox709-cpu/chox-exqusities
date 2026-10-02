#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

struct Employee {
    std::string name;
    double hoursWorked;
    double hourlyRate;
    double deductions;
    double taxRate;
};

double readPositiveNumber(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || value < 0) {
            std::cout << "Please enter a valid non-negative number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

Employee collectEmployeeData() {
    Employee employee;

    std::cout << "\n=== Employee Payroll Entry ===\n";
    std::cout << "Enter employee name: ";
    std::getline(std::cin, employee.name);

    employee.hoursWorked = readPositiveNumber("Enter hours worked: ");
    employee.hourlyRate = readPositiveNumber("Enter hourly rate: ");
    employee.deductions = readPositiveNumber("Enter deductions (insurance, loans, etc.): ");
    employee.taxRate = readPositiveNumber("Enter tax rate (%) : ");

    return employee;
}

void printPayslip(const Employee& employee) {
    const double grossPay = employee.hoursWorked * employee.hourlyRate;
    const double taxAmount = grossPay * (employee.taxRate / 100.0);
    const double netPay = grossPay - taxAmount - employee.deductions;

    std::cout << "\n=== Payslip for " << employee.name << " ===\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Hours worked: " << employee.hoursWorked << "\n";
    std::cout << "Hourly rate: $" << employee.hourlyRate << "\n";
    std::cout << "Gross pay: $" << grossPay << "\n";
    std::cout << "Tax rate: " << employee.taxRate << "%\n";
    std::cout << "Tax amount: $" << taxAmount << "\n";
    std::cout << "Deductions: $" << employee.deductions << "\n";
    std::cout << "Net pay: $" << netPay << "\n";
}

int main() {
    std::cout << "Welcome to UNIPATH Payroll System\n";
    std::cout << "================================\n";

    Employee employee = collectEmployeeData();
    printPayslip(employee);

    std::cout << "\nPayroll calculation complete.\n";
    return 0;
}
