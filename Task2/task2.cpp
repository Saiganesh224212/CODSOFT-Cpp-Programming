#include <iostream>
#include <limits>
class Calculator {
public:
    double add(double a, double b) { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    
    // Handles division by zero
    double divide(double a, double b) {
        if (b == 0) {
            std::cerr << "Error: Division by zero is not allowed.\n";
            return std::numeric_limits<double>::quiet_NaN();
        }
        return a / b;
    }
};

class CalculatorUI {
private:
    Calculator calculator;
    double getValidNumber(const std::string& prompt) {
        double num;
        while (true) {
            std::cout << prompt;
            std::cin >> num;

            if (std::cin.fail()) { 
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                std::cerr << "Invalid input! Please enter a valid number.\n";
            } else {
                return num;
            }
        }
    }

    char getValidOperation() {
        char op;
        while (true) {
            std::cout << "\nChoose an operation:\n";
            std::cout << "  + : Addition\n";
            std::cout << "  - : Subtraction\n";
            std::cout << "  * : Multiplication\n";
            std::cout << "  / : Division\n";
            std::cout << "Enter your choice: ";
            std::cin >> op;

            if (op == '+' || op == '-' || op == '*' || op == '/') {
                return op;
            } else {
                std::cerr << "Invalid choice! Please enter +, -, *, or /.\n";
            }
        }
    }
    std::string formatNumber(double num) {
        return (num < 0) ? "(" + std::to_string(num) + ")" : std::to_string(num);
    }

public:
    void start() {
        std::cout << "===================================\n";
        std::cout << "       SIMPLE CALCULATOR (C++)     \n";
        std::cout << "===================================\n";

        while (true) {
            double num1 = getValidNumber("\nEnter first number: ");
            double num2 = getValidNumber("Enter second number: ");
            char operation = getValidOperation();

            double result;
            switch (operation) {
                case '+': result = calculator.add(num1, num2); break;
                case '-': result = calculator.subtract(num1, num2); break;
                case '*': result = calculator.multiply(num1, num2); break;
                case '/': result = calculator.divide(num1, num2); break;
                default: continue;
            }
            std::cout << "\nResult: " << formatNumber(num1) << " " << operation << " " << formatNumber(num2) << " = " << result << "\n";

            char choice;
            std::cout << "\nDo you want to perform another calculation? (y/n): ";
            std::cin >> choice;
            if (choice != 'y' && choice != 'Y') {
                std::cout << "\nThank you for using the calculator. Goodbye!\n";
                break;
            }
        }
    }
};

int main() {
    CalculatorUI ui;
    ui.start();
}
