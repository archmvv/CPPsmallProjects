#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct User {
    string username;
    string password;
};

class Database {
public:
    vector<User> users;

    Database(const string& filename) {
        loadDatabase(filename);
    }

    void loadDatabase(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening database file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            User user;
            iss >> user.username >> user.password;
            users.push_back(user);
        }

        file.close();
    }

    void saveDatabase(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cerr << "Error opening database file for writing." << endl;
            return;
        }

        for (const auto& user : users) {
            file << user.username << " " << user.password << endl;
        }

        file.close();
    }
};

class LoginSystem{
public:
    Database& database;

    LoginSystem(Database& db) : database(db) {}

    bool login(const string& username, const string& password){
        for (const auto& user : database.users){
            if (user.username == username && user.password == password){
                cout << "Login successful. Welcome, " << username << "!" << endl;
                return true;
            }
        }

        cout << "Login failed. Invalid username or password." << endl;
        return false;
    }

    void registerUser(const string& username, const string& password){
        for (const auto& user : database.users){
            if (user.username == username) {
                cout << "Registration failed. Username already exists." << endl;
                return;
            }
        }

        User newUser;
        newUser.username = username;
        newUser.password = password;
        database.users.push_back(newUser);
        database.saveDatabase("database.txt");
        cout << "Registration successful. Welcome, " << username << "!" << endl;
    }
};

void showMenu(){
    cout << "***********MENU***********" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Forgot password?" << endl;
    cout << "4. Exit" << endl;
    cout << "**************************" << endl;
}


int main(){
    Database database("database.txt");
    LoginSystem loginSystem(database);

    
        showMenu();
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
    while (choice != 4) {
        if (choice == 1) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            loginSystem.login(username, password);
        } else if (choice == 2) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            loginSystem.registerUser(username, password);
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}