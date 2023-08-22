#include <iostream>
#include "vector"
#include "algorithm"

using namespace std;

void getOperator(string &, string &, string &, char &);

double getOperand(string &, string &, string &, bool);

vector<short> equationsOperators;
char allOperators[] = {'*', '/', '+', '-'};
char operators1[] = {'*', '+'};
char operators2[] = {'/', '-'};

int main() {
    string bigInput, backUpInput, firstOperand, secOperand, total, replacedStr;
    char operatR;
    size_t operatorPos = 0;
    int selectEquationLength = 0;
    cout << "CALCULATOR\n\n";
    cout << "ex:-5*3+12/2-1 (enter)\n";
    cout << "Answer:-5*3+12/2-1=-10\n\n";
    cout << "Input:";
    getline(cin, bigInput);
    backUpInput = bigInput;

    if (backUpInput[0] == '-')
        backUpInput.replace(0, 0, "0");


    for (int i = 0; i < backUpInput.length(); i++) {
        for (char oneOperator: allOperators) {
            operatorPos = backUpInput.find(oneOperator);
            if (operatorPos != string::npos) {
                backUpInput.replace(operatorPos, 1, "o");
                break;
            }
        }
        if (operatorPos != string::npos) {
            equationsOperators.push_back(operatorPos);
        }
    }

    backUpInput = bigInput;

    if (backUpInput[0] == '-')
        backUpInput.replace(0, 0, "0");

    sort(equationsOperators.begin(), equationsOperators.end());
    int x = equationsOperators.size();
    int k = 0;


    while (k < x) {
        getOperand(backUpInput, firstOperand, secOperand, false);
        int i = getOperand(backUpInput, firstOperand, secOperand, true);
        operatR = backUpInput[equationsOperators[i]];
        if (i == 0)
            operatorPos = -1;
        else
            operatorPos = equationsOperators[i - 1];
        selectEquationLength = (firstOperand + secOperand).size() + 1;

        getOperator(firstOperand, secOperand, total, operatR);
        equationsOperators.erase(equationsOperators.begin() + i);
        for (; i < equationsOperators.size(); i++)
            equationsOperators[i] -= selectEquationLength - total.length();
        backUpInput.replace(operatorPos + 1, selectEquationLength, total);

        printf("%.2f %c %.2f = %.2f\n", stod(firstOperand), operatR, stod(secOperand), stod(total));
        k++;
    }
    cout << endl << "Answer: " << bigInput << " = ";
    printf("%.2f\n", stod(total));

}


double
getOperand(string &backUpInput, string &firstOperand, string &secOperand, bool switcher) {
    int i;
    char backUpChar;
    if (!switcher) {
        for (int k = 0; k < 2; k++) {
            for (i = 0; i < equationsOperators.size(); i++) {
                backUpChar = backUpInput[equationsOperators[i]];
                if (operators1[k] == backUpChar || operators2[k] == backUpChar) {
                    if (i == 0)
                        firstOperand = backUpInput.substr(
                                0, equationsOperators[i]);
                    else
                        firstOperand = backUpInput.substr(
                                equationsOperators[i - 1] + 1,
                                equationsOperators[i] - equationsOperators[i - 1] - 1);

                    break;
                }
            }
            if (i < equationsOperators.size() && operators1[k] == backUpChar || operators2[k] == backUpChar)
                break;
        }
    } else {
        for (int k = 0; k < 2; k++) {
            for (i = 0; i < equationsOperators.size(); i++) {
                backUpChar = backUpInput[equationsOperators[i]];
                if (operators1[k] == backUpChar || operators2[k] == backUpChar) {
                    if (i == equationsOperators.size() - 1)
                        secOperand = backUpInput.substr(
                                equationsOperators[i] + 1,
                                backUpInput.size() - 1 - equationsOperators[i]);

                    else
                        secOperand = backUpInput.substr(
                                equationsOperators[i] + 1,
                                equationsOperators[i + 1] - equationsOperators[i] - 1);
                    break;
                }
            }
            if (i < equationsOperators.size() && operators1[k] == backUpChar || operators2[k] == backUpChar) {
                break;
            }
        }

        return i;
    }
    return equationsOperators.size();
}

void getOperator(string &firstOperand, string &secOperand, string &total, char &operatR) {
    switch (operatR) {
        case '+':
            total = to_string(stod(firstOperand) + stod(secOperand));
            break;
        case '-':
            total = to_string(stod(firstOperand) - stod(secOperand));
            break;
        case '*':
            total = to_string(stod(firstOperand) * stod(secOperand));
            break;
        case '/':
            total = to_string(stod(firstOperand) / stod(secOperand));
            break;
    }
}

