#include <iostream>

using namespace std;

int main() {
    char operation;
    double input1, input2, total;
    cout << "Simple Calculator\n\n";
    cout << "choose Operations\n";
    cout << "1-Addition\n";
    cout << "2-Subtraction\n";
    cout << "3-Multiplication\n";
    cout << "4-Division\n";
    cout << "Answer:";
    cin >> operation;
    cout << "Enter two inputs\n";
    cout << "Answer:";
    cin >> input1;
    cin >> input2;
    switch (operation) {
        case '1':
            operation = '+';
            total = input1 + input2;
            break;
        case '2':
            operation = '-';
            total = input1 - input2;
            break;
        case '3':
            operation = '*';
            total = input1 * input2;
            break;
        case '4':
            operation = '/';
            total = input1 / input2;
            break;
        default:
            cout << "invalid input";
    }
    cout << input1 << " " << operation << " " << input2 << " = " << total;
}
