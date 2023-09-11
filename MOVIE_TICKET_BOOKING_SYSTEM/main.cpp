#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <windows.h>
#include <filesystem>

using namespace std;

class Ticket {
public:
    string id;

    Ticket(const string &id) {
        this->id = id;
    }

    Ticket() {}
};

class Movie {
    static int countMovies;

    char seats1[2][17] = {
            '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
            '_',
            '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
    };
    char seats2[3][25] = {
            '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
            '_',
            '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
            '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
            '_',
            '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
            '_', '_', '_', '_', '_', '_', '_'
    };
    char seats3[3][17] = {
            '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
            '_',
            '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
            '_',
            '_', '_', '_', '_', '_', '_', '_',
    };
    char seats4[4] = {'_', '_', '_', '_'};
public:
    string name;
    string genre;
    string rating;
    string duration;
    string ageRestriction;
    int price;
    string hall;
    string time;
    string date;
    int ticketSold = 0;
    Ticket tickets[169];

    Movie(const string &name, const string &genre, const string &ratting, const string &duration,
          const string &ageRestriction,
          const int &price, const string &hall, const string &time,
          const string &date) {
        this->name = name;
        this->genre = genre;
        this->rating = ratting;
        this->duration = duration;
        this->ageRestriction = ageRestriction;
        this->price = price;
        this->hall = hall;
        this->time = time;
        this->date = date;
        countMovies++;
    }

    void MovieDetails() const {
        cout << "Name: " << name << endl;
        cout << "Genre: " << genre;
        cout << "\t\tRating: " << rating << endl;
        cout << "Running Time: " << duration << " min";
        cout << "\tAge restriction: " << ageRestriction << endl;
        cout << "Price: " << price << "EGP";
        cout << "\t\tHall: " << hall << endl;
        cout << "Time: " << time;
        cout << "\t\tDate: " << date << endl;
        cout << "Tickets available: " << 169 - ticketSold << endl;
        cout << "______________________________\n";
    }

    void printMovie() {
        cout << "Name: " << name << endl;
        cout << "Price: " << price << "EGP\n";
        cout << "Time: " << time;
        cout << "\tDate: " << date << endl;
        cout << "______________________________\n";
    }

    bool selectSeat(string input) {
        int row, column;

        input[0] = toupper(input[0]);
        if (input == "e" || input == "E")
            return false;
        row = 9 - (toupper(input[0]) - 65) - 1;
        bool isDigit = true;

        if (input.length() > 1) {
            for (char in: input.substr(1, input.length() - 1))
                if (!isdigit(in))
                    isDigit = false;
        } else isDigit = false;

        if (isDigit)
            column = stoi(input.substr(1, input.length() - 1)) - 1;
        else {
            cout << "wrong input\n\n";
            return true;
        }
        if (row < 2 && 3 < column && column < 21)
            if (seats1[row][column - 4] == 'X') {
                cout << "Seat is already booked";
            } else seats1[row][column - 4] = 'X';
        else if (2 <= row && row < 5)
            if (seats2[row - 2][column] == 'X') {
                cout << "Seat is already booked";
            } else
                seats2[row - 2][column] = 'X';
        else if (5 <= row && row < 8 && 6 < column && column < 23)
            if (seats3[row - 5][column - 7] == 'X') {
                cout << "Seat is already booked";
            } else
                seats3[row - 5][column - 7] = 'X';
        else if (row == 8 && 11 < column && column < 16)
            if (seats4[column - 12] == 'X') {
                cout << "Seat is already booked";
            } else
                seats4[column - 12] = 'X';
        else {
            cout << "Wrong input";
            return true;
        }
        tickets[ticketSold] = Ticket(input);
        ticketSold++;
        return true;
    }

    void bookMovie() {
        while (true) {
            int space = 12;
            cout << "\n\n";
            for (int r = 92; r > 81; r -= 2, space++) {
                for (int c = 0; c < space; c++)
                    cout << " ";
                cout << "\\";
                for (int c = 0; c < r; c++) {
                    if (r == 88 && c == 40) {
                        cout << "S C R E E N";
                        c += 10;
                    } else cout << " ";
                }
                cout << "/\n";
            }
            //ending screen
            cout << "\t\t  \\";
            for (int c = 0; c < 80; c++)
                cout << "_";

            cout << "/\n\n\n";

            char letter = 73;
            cout << "\t ";
            for (int c = 1; c < 26; c++) {
                if (c < 9)
                    cout << c << "   ";
                else cout << c << "  ";
            }
            cout << endl;
            for (int r = 0; r < 9; r++, letter--) {
                cout << letter << "\t";
                if (r < 2) {
                    cout << "\t\t";
                    for (int c = 0; c < 17; c++)
                        cout << '|' << seats1[r][c] << "| ";
                }
                if (2 <= r && r < 5) {
                    for (int c = 0; c < 25; c++)
                        cout << '|' << seats2[r - 2][c] << "| ";
                }
                if (5 <= r && r < 8) {
                    cout << "\t\t\t    ";
                    for (int c = 0; c < 16; c++)
                        cout << '|' << seats3[r - 5][c] << "| ";
                }
                if (8 <= r) {
                    cout << "\t\t\t\t\t\t";
                    for (int c = 0; c < 4; c++)
                        cout << '|' << seats4[c] << "| ";
                }
                cout << endl;

            }
            string input;
            cout << "\n\n\n\n\n\n";
            cout << "\nSelect a seat:\n ";
            cout << "to go back press e\n";
            cin >> input;
            if (selectSeat(input))
                continue;
            else
                break;
        }
    }

    static int getCout() { return countMovies; }

};

int Movie::countMovies = 0;


void readMovies(const string &fileName);

void saveMovies();

void saveTickets(string &basket, int basketCounter, double total);

void readTickets();

vector<Movie> movies;

int main() {
    int input;
    double total;
    string basket = "", basketTemp;
    int basketCounter = 0;
    char choice;
    readMovies("Movies.txt");
    readTickets();
    cout << "Welcome to our cinema\n";
    cout << "Movies available:\n";
    cout << "______________________________\n";
    cout << "See all movies? (y/n): ";
    cin >> choice;
    if (choice == 'y')
        while (true) {
            cout << "\n";

            for (int i = 0; i < movies.size(); i++) {
                cout << i + 1 << "- ";
                movies[i].printMovie();
                cout << endl;
            }

            cout << "Select a movie: ";
            cout << "exit press 0\n";
            cin >> input;
            if (input == 0)
                break;
            if (input > movies.size() || input < 1) {
                cout << "Wrong input\n";
                continue;
            }
            movies[input - 1].MovieDetails();
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout << "\nDo you want to book a ticket? (y/n): ";
            cin >> choice;
            if (choice == 'y')
                movies[input - 1].bookMovie();
            else if (choice == 'n')
                continue;
            else
                cout << endl << endl << endl;
            cout << "Do you want to checkout? (y/n): ";
            cin >> choice;
            if (basket.find(to_string(input - 1)) == string::npos) {
                basket += to_string(input - 1) + '\n';
                basketCounter++;
            }

            if (choice == 'y') {
                cout << "\n\nCheckout...\n";
                basketTemp = basket;
                for (int i = 0; i < basketCounter && basketTemp.find('\n') != string::npos; i++) {
                    total += movies[stoi(basketTemp.substr(0, basketTemp.find('\n')))].ticketSold *
                             movies[stoi(basketTemp.substr(0, basketTemp.find('\n')))].price;
                    basketTemp.replace(0, basketTemp.find('\n') + 1, "");
                }
                cout << "Total: " << total << "EGP\n";
                cout << "Thank you for using our cinema\n";
                saveTickets(basket, basketCounter, total);
                break;
            } else
                cout << endl << endl << endl;

        }
    else if (choice == 'n')
        cout << "Thank you for using our cinema\n";
    saveMovies();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    filesystem::path filePath = filesystem::current_path() / ("Tickets.txt");
    ShellExecute(nullptr, "open", filePath.string().c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    return 0;
}


void saveMovies() {
    ofstream file("Movies.txt");
    for (int i = 0; i < Movie::getCout(); i++) {
        file << i + 1 << "- Name: " << movies[i].name << endl;
        file << "Genre: " << movies[i].genre;
        file << "\t\tRating: " << movies[i].rating << endl;
        file << "Running Time: " << movies[i].duration << " min";
        file << "\tAge restriction: " << movies[i].ageRestriction << endl;
        file << "Price: " << movies[i].price << "EGP";
        file << "\t\tHall: " << movies[i].hall << endl;
        file << "Time: " << movies[i].time;
        file << "\t\t\tDate: " << movies[i].date << endl;
        file << "Tickets available: " << 169 - movies[i].ticketSold << endl;
        file << "______________________________\n";
    }
    file.close();

}

void saveTickets(string &basket, int basketCounter, double total) {
    ofstream file("Tickets.txt");
    int selectMovies;
    if (file.is_open()) {
        while (0 < basketCounter--) {
            selectMovies = stoi(basket.substr(0, basket.find('\n')));
            basket.replace(0, basket.find('\n') + 1, "");
            for (int i = 0; i < movies[selectMovies].ticketSold; i++) {

                file << "Ticket " << i + 1 << ":\n";
                file << "\t\tMovie: " << movies[selectMovies].name << endl;
                file << "Price: " << movies[selectMovies].price << "EGP";
                file << "\tTime: " << movies[selectMovies].time << endl;
                file << "Date: " << movies[selectMovies].date;
                file << "\tSeat: " << movies[selectMovies].tickets[i].id << endl;
                file << "______________________________\n";
            }
            file << "SubTotal: " << movies[selectMovies].price * movies[selectMovies].ticketSold << "EGP\n\n\n";
        }
        file << "SubTotal: " << total << "EGP\n";
        file.close();
    }

}

void readTickets() {
    ifstream file("Tickets.txt");
    if (file.is_open()) {
        string line, ticket, tickets;
        string movie, seat;
        int ticketsCounter = 0, ticketProperties = 2;
        while (!file.eof()) {
            getline(file, line);
            tickets += line;
            if (line.find("______________________________") != string::npos)
                ticketsCounter++;
        }
        while (0 < ticketsCounter--) {
            if (tickets.find("Movie: ") != string::npos && tickets.find("Price: ") != string::npos) {
                movie = tickets.substr(tickets.find("Movie: ") + 7,
                                       tickets.find("Price: ") - tickets.find("Movie: ") - 7);
            }
            if (tickets.find("Seat: ") != string::npos &&
                tickets.find("______________________________") != string::npos) {
                seat = tickets.substr(tickets.find("Seat: ") + 6,
                                      tickets.find("______________________________") - tickets.find("Seat: ") - 6);
                tickets.replace(0, tickets.find("______________________________") + 30, "");
            }
            for (int i = 0; i < Movie::getCout(); i++) {
                if (movie == movies[i].name)
                    movies[i].selectSeat(seat);
            }
        }
        file.close();
    }
}

void readMovies(const string &fileName) {

    ifstream file(fileName);
    int i = 0;
    string movieLists, line;
    string name, genre, rating, duration, ageRestriction, price, hall, time, date, ticketsAvailable;
    if (file.is_open()) {
        int movieCounter = 0;
        while (!file.eof()) {
            getline(file, line);
            movieLists += line;
            if (line.find("______________________________") != string::npos) {
                movieCounter++;
            }
        }
        while (0 < movieCounter--) {

            if (movieLists.find("Name: ") != string::npos && movieLists.find("Genre: ") != string::npos)
                name = movieLists.substr(movieLists.find("Name: ") + 6,
                                         movieLists.find("Genre: ") - movieLists.find("Name:") - 6);
            if (movieLists.find("Genre: ") != string::npos && movieLists.find("Rating: ") != string::npos)
                genre = movieLists.substr(movieLists.find("Genre: ") + 7,
                                          movieLists.find("Rating: ") - movieLists.find("Genre: ") - 9);
            if (movieLists.find("Rating: ") != string::npos &&
                movieLists.find("Running Time: ") != string::npos)
                rating = movieLists.substr(movieLists.find("Rating: ") + 8,
                                           movieLists.find("Running Time: ") - movieLists.find("Rating: ") - 8);
            if (movieLists.find("Running Time: ") != string::npos &&
                movieLists.find(" min") != string::npos) {
                duration = movieLists.substr(movieLists.find("Running Time: ") + 14,
                                             movieLists.find(" min") - movieLists.find("Running Time: ") - 14);
                movieLists.replace(0, movieLists.find("Running Time: ") + 14, "");
            }
            if (movieLists.find("Age restriction: ") != string::npos &&
                movieLists.find("Price: ") != string::npos)
                ageRestriction = movieLists.substr(movieLists.find("Age restriction: ") + 17,
                                                   movieLists.find("Price: ") -
                                                   movieLists.find("Age restriction: ") -
                                                   17);
            if (movieLists.find("Price: ") != string::npos && movieLists.find("EGP") != string::npos)
                price = movieLists.substr(movieLists.find("Price: ") + 7,
                                          movieLists.find("EGP") - movieLists.find("Price: ") - 7);

            if (movieLists.find("Hall: ") != string::npos && movieLists.find("Time: ") != string::npos)
                hall = movieLists.substr(movieLists.find("Hall: ") + 6,
                                         movieLists.find("Time: ") - movieLists.find("Hall: ") - 6);
            if (movieLists.find("Time: ") != string::npos && movieLists.find("Date: ") != string::npos)
                time = movieLists.substr(movieLists.find("Time: ") + 6,
                                         movieLists.find("Date: ") - movieLists.find("Time: ") - 6 - 3);
            if (movieLists.find("Date: ") != string::npos &&
                movieLists.find("Tickets available: ") != string::npos)
                date = movieLists.substr(movieLists.find("Date: ") + 6,
                                         movieLists.find("Tickets available: ") - movieLists.find("Date: ") - 6);
            if (movieLists.find("Tickets available: ") != string::npos &&
                movieLists.find("______________________________") != string::npos) {
                ticketsAvailable = movieLists.substr(movieLists.find("Tickets available: ") + 19,
                                                     movieLists.find("______________________________") -
                                                     movieLists.find("Tickets available: ") - 19);
                movieLists.replace(0, movieLists.find("______________________________") + 30, "");
                movies.emplace_back(name, genre, rating, duration, ageRestriction, stoi(price), hall,
                                    time, date);
                i++;
            }
        }
        file.close();
    }
}
