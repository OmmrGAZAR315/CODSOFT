#include <iostream>
#include <random>

using namespace std;

int main() {
    char choice;
    int max;
    int chances;
    replay:
    cout << "Number Guessing Game\n\n";
    cout << "Please select difficulty:\n";
    cout << "1-Baby (0-10)\n";
    cout << "2-Normal (0-100)\n";
    cout << "3-Hard (0-1000)\n";
    cout << "4-Impossible (0-10000)\n";
    cout << "Answer:";
    cin >> choice;
    switch (choice) {
        case '1':
            max = 10;
            chances = 3;
            break;
        case '2':
            max = 100;
            chances = 10;
            break;
        case '3':
            max = 1000;
            chances = 13;
            break;
        case '4':
            max = 10000;
            chances = 20;
            break;
        default:
            cout << "wrong input\n\n";

    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, max);
    int secretNumber = distribution(gen), guessed;
    while (chances > 0) {
        cout << "you have " << chances << " chances\n";
        chances--;
        cout << "Guess the number?\n";
        cout << "Answer:";
        cin >> guessed;
        if (guessed < secretNumber) {
            if ((guessed * 2) < secretNumber)
                cout << "Wrong\nHint:Guess is too low";
            else cout << "Wrong\nHint:Guess is low";
            cout << "\n\n";
        } else if (guessed > secretNumber) {
            if ((guessed / 2) > secretNumber)
                cout << "Wrong\nHint:Guess is too high";
            else cout << "Wrong\nHint:Guess is high";
            cout << "\n\n";
        } else {
            cout << "Hoorrray,you guess it right\n\n";
            break;
        }
    }
    if (chances == 0)
        cout << "sorry, no remaining chances\n";
    cout << "play again? Y or N\n";
    cin >> choice;
    if (tolower(choice) == 'y') {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
        goto replay;

    } else cout << "Goodbye";
    return 0;
}
