#include <iostream>
#include <iomanip>
#include "vector"
#include "algorithm"

using namespace std;

void getOperator(string &, string &, string &, char &);

double getOperand(string &, string &, string &, bool);

inline void inputAgain(string &bigInput, string &total);

vector<long long> equationsOperators;
char allOperators[] = {'*', '/', '+', '-'};
char operators1[] = {'*', '+'};
char operators2[] = {'/', '-'};

int main() {
    string bigInput, backUpInput, firstOperand, lastOperand, secOperand, total, replacedStr;
    char operatR, lastOperator;
    size_t operatorPos;
    int selectEquationLength;
    cout << "Advanced Calculator\n\n";
    cout << "ex:-5*3+12/2-1\n\n";
    cout << "Enter an Equation: Input a mathematical equation to proceed on previous result.\n"
            "Press 'Enter': Use this to repeat the previous operation.\n"
            "Press 'C': Use this to clear the input or any previous calculations.\n"
            "Press 'N': Use this to exit the program.";
    cout << "Answer:-5*3+12/2-1=-10\n";
    cout << "Input:+10-20\n";
    cout << "Answer:-10+10-20=-20\n\n";
    c:
    cout << "Input:";
    getline(cin, bigInput);
    do {
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
        lastOperand = backUpInput.substr(equationsOperators.back(), backUpInput.size() - 1);
        lastOperator = lastOperand[0];
        lastOperand.replace(0, 1, "");
        try {
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

                k++;
            }

            cout << endl << "Answer: " << bigInput << " = ";
            printf("%.2Lf\n", stold(total));
            cout << "Input:";


            bigInput = total;
            getline(cin, total);

            if (total.empty()) {
                ostringstream stream;
                stream << fixed << setprecision(2) << stold(lastOperand);
                total = lastOperator + stream.str();

            }
            if (tolower(total[0]) == 'c')
                goto c;
            else inputAgain(bigInput, total);
        } catch (...) {
            cerr << "Math Error " << "\n";
            exit(0);

        }
    } while (!total.empty());

    return 0;
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
    ostringstream stream;
    stream << fixed << setprecision(2);
    switch (operatR) {
        case '+':
            stream << (stold(firstOperand) + stold(secOperand));
            total = stream.str();
            break;
        case '-':
            stream << (stold(firstOperand) - stold(secOperand));
            total = stream.str();
            break;
        case '*':
            stream << (stold(firstOperand) * stold(secOperand));
            total = stream.str();
            break;
        case '/':
            stream << (stold(firstOperand) / stold(secOperand));
            total = stream.str();
            break;
    }
}

void inputAgain(string &bigInput, string &total) {
    if (tolower(total[0]) == 'n')
        total.clear();
    else {
        int i, k;
        int firstOperator;
        bool userError = true;
        //fixing not writing an operator by mistake
        for (i = 0; i < total.size(); i++) {
            for (k = 0; k < 4; k++)
                if (total[i] == allOperators[k]) {
                    firstOperator = i;
                    break;
                }
            if (total[i] == allOperators[k])
                break;
        }


        for (char oneOperator: allOperators)
            if (total[0] == oneOperator)
                userError = false;

        if (userError)
            total.replace(0, firstOperator, "");

        bigInput += total;
    }
}
