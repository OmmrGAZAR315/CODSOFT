#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <windows.h>
#include <filesystem>
using namespace std;

typedef filesystem::path path;

class task {
    int number;
    string name;
    string content;
    string status = "Pending";

//    task *subtasks;
public:
    static bool isThereChange;

    task() {}

    task(const string &name, const string &content) {
        this->name = name;
        this->content = content;
        isThereChange = true;
    }


    const string &getName() const { return name; }

    void setNumber(int num) { number = num; }

    const string &getStatus() const { return status; }

    void markTask(const bool &marked) {
        if (!marked)
            status = "Completed";
        else
            status = "Pending";
        isThereChange = true;
    }

    const string &getContent() const { return content; }

    void viewTask() const {
        cout << "Task Number:" << number;
        cout << "\nTask Name:" << name;
        if (!content.empty())
            cout << "\nTask content:" << content;
        cout << "\nTask Status:" << status << endl;
    }


    void makeEdit(const int &selector, const string &str) {
        if (selector == 0)
            name = str;
        else if (selector == 1)
            content = str;
        else if (selector == 2)
            status = str;
        isThereChange = true;
    }


};

class list {
    vector<task> tasks;
    string listName;
    int static count;
    int number;
public:
    bool static isThereChange;

    list(const string name) {
        listName = name;
        count++;
        number = count;
        isThereChange = true;
    }

    const int getListNumber() const { return number; }

    void changeListName(const string &newName) { listName = newName; }

    const string getListName() const { return listName; }

    void viewTasks(const bool &writing = false, ofstream *myTxt = nullptr) {
        if (!writing) {
            for (int i = 0; i < tasks.size(); i++) {
                cout << endl << i + 1 << "- \n";
                tasks[i].setNumber(i + 1);
                cout << "Task Name: " << tasks[i].getName() << endl;
                if (!tasks[i].getContent().empty())
                    cout << "Task Content: " << tasks[i].getContent() << endl;
                cout << "Task Status: " << tasks[i].getStatus() << endl;
                cout << "---------------------------------" << endl;
            }
        } else {
            for (int i = 0; i < tasks.size(); i++) {
                *myTxt << i + 1 << "- \n";
                *myTxt << "Task Name: " << tasks[i].getName() << endl;
                if (!tasks[i].getContent().empty())
                    *myTxt << "Task Content: " << tasks[i].getContent() << endl;
                *myTxt << "Task Status: " << tasks[i].getStatus() << endl;
                *myTxt << "---------------------------------" << endl;
            }
        }

    }

    task *getTask(int number) {
        if (!tasks.empty())
            return &tasks[number - 1];
        else return nullptr;
    }

    vector<task> &getTask() {
        return tasks;
    }

    void addTask() {
        tasks.emplace_back();
        isThereChange = true;
    }

    void addTask(const string &name, const string &content) {
        tasks.emplace_back(name, content);
        isThereChange = true;
    }


    void deleteTask(const int &number) {
        if (number - 1 < tasks.size()) {
            tasks.erase(tasks.begin() + number - 1);
            cout << "Task " << number << " Deleted\n";
            isThereChange = true;
        } else {
            cout << "Wrong task count";
        }
    }


};

void openExistList(const int &listNumberUserInput);


int list::count = 0;
bool list::isThereChange = false;
bool task::isThereChange = false;
vector<list> lists;
string input, selectedList;
bool isThereChange = false;

int main() {
    string fileName = "To Do Mylist.txt";
    ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        string line;
        int i;

        while (getline(inputFile, line)) {
            if (line.find("List Name: ") != string::npos) {
                lists.emplace_back(line.substr(14));
                i = 0;
            } else if (line.find("Task Name: ") != string::npos) {
                i++;
                lists.back().addTask();
                lists.back().getTask(i)->makeEdit(0, line.substr(11));
            } else if (line.find("Task Content: ") != string::npos)
                lists.back().getTask(i)->makeEdit(1, line.substr(14));
            else if (line.find("Task Status: ") != string::npos)
                lists.back().getTask(i)->makeEdit(2, line.substr(13));
        }
    }

    inputFile.close();

    bool exit = true;
    while (exit) {
        cout << "Welcome to do My List\n";
        cout << "Choose an option\n";
        cout << "1-Add a list\n";
        cout << "2-View All lists\n";
        cout << "3-Save\n";
        cin >> input;
        switch (input[0]) {
            case '1':
                cout << "What do you want to name this list?, to go back press b\n";
                cout << "Answer: ";
                cin >> input;
                if (tolower(input[0]) == 'b')
                    break;
                lists.emplace_back(input);
                cout << "List added successfully\n\n";
                openExistList(lists.size());
                break;
            case '2':
                if (lists.size() > 0) {
                    for (int i = 0; i < lists.size(); i++)
                        cout << i + 1 << "- " << lists[i].getListName() << endl;
                    cout << "choose a list, to go back press b\n";
                    cout << "Answer:";
                    cin >> selectedList;
                    if (tolower(selectedList[0]) == 'b')
                        break;
                    if (stoi(selectedList) > lists.size()) {
                        cout << "\nWrong list number\n\n";
                        break;
                    }
                    if (tolower(selectedList[0]) == 'b')
                        break;
                    cout << "1- Open\n";
                    cout << "2- Change list name\n";
                    cout << "3- Remove\n";
                    cout << "to go back press b\n";
                    cin >> input;
                    if (tolower(input[0]) == 'b')
                        break;
                    if (input == "1") {
                        openExistList(stoi(selectedList));
                        break;
                    }
                    if (input == "2") {
                        cout << "3- enter new name\n";
                        cin >> input;
                        lists[stoi(selectedList) - 1].changeListName(input);
                        break;
                    }
                    if (input == "3") {
                        cout << "Are you sure want to delete " <<
                             lists[stoi(selectedList) - 1].getListName() << endl;
                        cin >> input;
                        if (tolower(input[0]) == 'y') {
                            lists.erase(lists.begin() + stoi(selectedList) - 1);
                            isThereChange = true;
                        }
                    }
                } else cout << "There is no task here...\n\n";
                break;
            case '3':
                exit = false;
                break;
        }
    }
    if (task::isThereChange || list::isThereChange || isThereChange) {
        ofstream outPutFile(fileName);
        if (outPutFile.is_open()) {
            for (int i = 0; i < lists.size(); i++) {
                if (i != 0)
                    outPutFile << endl << endl;
                outPutFile << i + 1 << "- List Name: " << lists[i].getListName() << endl;
                outPutFile << "---------------------------------------------------\n";
                lists[i].viewTasks(true, &outPutFile);
            }
            outPutFile.close();

            cout << "\nto do list Saved successfully";
        }
    }
    path filePath = filesystem::current_path() / (fileName);
    ShellExecute(nullptr, "open", filePath.string().c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    return 0;
}

void openExistList(const int &listNumberUserInput) {
    bool userError = true;
    bool exit = true;
    int i;
    char settings;
    for (i = 0; i < lists.size(); i++) {
        if (lists[i].getListNumber() == listNumberUserInput) {
            userError = false;
            break;
        }
    }
    if (userError) {
        cout << "Wrong list name\n";
        return;
    }
    while (exit) {
        cout << endl << lists[i].getListName() << "...\n";
        cout << "Choose an option\n";
        cout << "1-Add a Task\n";
        cout << "2-View All Tasks\n";
        cout << "3-go back\n";
        cin >> input;
        switch (input[0]) {
            case '1': {
                string name;
                string content;
                cout << "enter task name:";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);
                cout << "enter task content:";
                if (cin.peek() != '\n')
                    getline(cin, content);
                lists[i].addTask(name, content);
                cout << "Task added successfully\n";
            }
                break;
            case '2': {
                if (lists[i].getTask(stoi(input)) != nullptr) {
                    lists[i].viewTasks();
                    cout << endl;
                    cout << "choose a Task, to go back press b\n";
                    cout << "Answer: ";
                    cin >> input;
                    if (tolower(input[0]) == 'b')
                        break;
                    if (lists[i].getTask().size() < stoi(input)) {
                        cout << "Wrong task number\n";
                        break;
                    }
                    lists[i].getTask(stoi(input))->viewTask();
                    cout << "\n\n";
                    cout << "1 - Edit\n";
                    if (tolower(lists[i].getTask(stoi(input))->getStatus()[0]) == 'p')
                        cout << "2 - Mark\n";
                    else
                        cout << "2 - Unmark\n";
                    cout << "3 - Delete\n";
                    cout << "4 - go back\n";
                    cin >> settings;
                    switch (settings) {
                        case '1': {
                            string edit;
                            lists[i].getTask(stoi(input))->viewTask();
                            cout << "\n1- change name\n";
                            cout << "2- change content\n";
                            cout << "Answer:";
                            cin >> edit;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            switch (edit[0]) {
                                case '1':
                                    cout << "Enter new name\n";
                                    getline(cin, edit);
                                    lists[i].getTask(stoi(input))->
                                            makeEdit(0, edit);
                                    break;
                                case '2':
                                    cout << "Enter new content\n";
                                    if (cin.peek() != '\n')
                                        getline(cin, edit);
                                    lists[i].getTask(stoi(input))->
                                            makeEdit(1, edit);
                                    break;
                            }
                        }
                            break;

                        case '2':
                            if (tolower(lists[i].getTask(stoi(input))->getStatus()[0]) == 'p')
                                lists[i].getTask(stoi(input))->markTask(false);
                            else
                                lists[i].getTask(stoi(input))->markTask(true);
                            break;
                        case '3':
                            cout << "Are you sure want to delete " <<
                                 lists[i].getTask(stoi(input))->getName() << endl;
                            cin >> settings;
                            if ('y' == tolower(settings))
                                lists[i].deleteTask(stoi(input));
                            break;
                        case '4':
                            break;
                    }
                } else cout << "There is no task here...\n\n";
            }
                break;
            case '3':
                exit = false;

        }
    }
}
