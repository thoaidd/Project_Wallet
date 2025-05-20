#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <string>
using namespace std;

struct User {
    string username;
    string hashed_password;
    string role; // "user" hoặc "admin"
};

struct Wallet {
    string username;
    int balance;
};

struct Transaction {
    string from;
    string to;
    int amount;
    string timestamp;
};

vector<User> users;
vector<Wallet> wallets;

// ============================
// Utilities
// ============================

string hashPassword(string input) {
    int hash = 0;
    for (char c : input) {
        hash = (hash * 31 + c) % 1000000007;
    }
    return to_string(hash);
}

string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void setupConsole() {
    system("cls");
}

// ============================
// File Operations
// ============================

void loadUsers() {
    users.clear();
    ifstream fin("users.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        User u;
        getline(ss, u.username, ',');
        getline(ss, u.hashed_password, ',');
        getline(ss, u.role);
        users.push_back(u);
    }
}

void saveUser(const User& u) {
    ofstream fout("users.txt", ios::app);
    fout << u.username << "," << u.hashed_password << "," << u.role << endl;
}

void loadWallets() {
    wallets.clear();
    ifstream fin("wallets.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        Wallet w;
        getline(ss, w.username, ',');
        ss >> w.balance;
        wallets.push_back(w);
    }
}

void saveWallets() {
    ofstream fout("wallets.txt");
    for (auto& w : wallets) {
        fout << w.username << "," << w.balance << endl;
    }
}

void saveTransaction(const Transaction& t) {
    ofstream fout("transactions.txt", ios::app);
    fout << t.from << "," << t.to << "," << t.amount << "," << t.timestamp << endl;
}

// ============================
// Account and Wallet Handling
// ============================

User* findUser(const string& username) {
    for (auto& u : users) {
        if (u.username == username)
            return &u;
    }
    return nullptr;
}

Wallet* findWallet(const string& username) {
    for (auto& w : wallets) {
        if (w.username == username)
            return &w;
    }
    return nullptr;
}

void ensureAdminAccount() {
    if (!findUser("admin")) {
        User admin = {"admin", hashPassword("admin"), "admin"};
        saveUser(admin);
        users.push_back(admin);
        wallets.push_back({"admin", 100000});
        saveWallets();
    }
}

// ============================
// Đăng nhập / Đăng ký
// ============================

User* login() {
    string user, pass;
    cout << "Dang nhap\n";
    cout << "Ten dang nhap: "; cin >> user;
    cout << "Mat khau: "; cin >> pass;

    string hashed = hashPassword(pass);
    for (auto& u : users) {
        if (u.username == user && u.hashed_password == hashed) {
            cout << "Dang nhap thanh cong!\n";
            return &u;
        }
    }
    cout << "Sai ten dang nhap hoac mat khau.\n";
    return nullptr;
}

void registerUser() {
    string user, pass;
    cout << "Dang ky tai khoan moi\n";
    cout << "Ten dang nhap: "; cin >> user;
    if (findUser(user)) {
        cout << "Ten dang nhap da ton tai.\n";
        return;
    }
    cout << "Mat khau: "; cin >> pass;
    User newUser = {user, hashPassword(pass), "user"};
    Wallet newWallet = {user, 0};
    users.push_back(newUser);
    wallets.push_back(newWallet);
    saveUser(newUser);
    saveWallets();
    cout << "Dang ky thanh cong!\n";
}

// ============================
// Giao dịch & Lịch sử
// ============================

void transferPoints(User* sender) {
    string receiver;
    int amount;
    cout << "Nguoi nhan: "; cin >> receiver;
    cout << "So diem can chuyen: "; cin >> amount;

    Wallet* fromWallet = findWallet(sender->username);
    Wallet* toWallet = findWallet(receiver);

    if (!toWallet) {
        cout << "Nguoi nhan khong ton tai.\n";
        return;
    }
    if (fromWallet->balance < amount) {
        cout << "Khong du so du.\n";
        return;
    }

    fromWallet->balance -= amount;
    toWallet->balance += amount;
    saveWallets();

    saveTransaction({sender->username, receiver, amount, getCurrentTime()});
    cout << "Chuyen tien thanh cong!\n";
}

void showTransactionHistory() {
    ifstream fin("transactions.txt");
    string line;
    cout << "\nLich su giao dich:\n";
    while (getline(fin, line)) {
        stringstream ss(line);
        Transaction t;
        getline(ss, t.from, ',');
        getline(ss, t.to, ',');
        ss >> t.amount;
        ss.ignore();
        getline(ss, t.timestamp);
        cout << "Tu: " << t.from << " -> " << t.to << ", So diem: " << t.amount << ", Thoi gian: " << t.timestamp << endl;
    }
}

// ============================
// Admin Menu
// ============================

void listUsers() {
    cout << "\nDanh sach tai khoan:\n";
    for (auto& u : users) {
        cout << "- " << u.username << " (" << u.role << ")" << endl;
    }
}

void resetPassword(string username) {
    string newpass;
    cout << "Nhap mat khau moi cho " << username << ": ";
    cin >> newpass;
    for (auto& u : users) {
        if (u.username == username) {
            u.hashed_password = hashPassword(newpass);
        }
    }
    ofstream fout("users.txt");
    for (auto& u : users) {
        fout << u.username << "," << u.hashed_password << "," << u.role << endl;
    }
    cout << "Mat khau da duoc cap nhat.\n";
}

void adminMenu(User* admin) {
    int choice;
    do {
        cout << "\n===== MENU ADMIN =====" << endl;
        cout << "1. Xem danh sach tai khoan" << endl;
        cout << "2. Tao tai khoan moi" << endl;
        cout << "3. Doi mat khau nguoi dung" << endl;
        cout << "4. Xem lich su giao dich" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon: "; cin >> choice;

        switch (choice) {
            case 1: listUsers(); break;
            case 2: registerUser(); break;
            case 3: {
                string user;
                cout << "Ten nguoi dung can doi mat khau: ";
                cin >> user;
                resetPassword(user);
                break;
            }
            case 4: showTransactionHistory(); break;
        }
    } while (choice != 0);
}

// ============================
// User Menu
// ============================

void userMenu(User* u) {
    int chon;
    do {
        cout << "\n===== MENU NGUOI DUNG =====" << endl;
        cout << "1. Xem so du" << endl;
        cout << "2. Chuyen diem" << endl;
        cout << "3. Xem lich su giao dich" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon: "; cin >> chon;

        switch (chon) {
            case 1: {
                Wallet* w = findWallet(u->username);
                cout << "So du hien tai: " << w->balance << endl;
                break;
            }
            case 2: transferPoints(u); break;
            case 3: showTransactionHistory(); break;
        }
    } while (chon != 0);
}

// ============================
// MAIN
// ============================

int main() {
    setupConsole();
    loadUsers();
    loadWallets();
    ensureAdminAccount();

    int chon;
    while (true) {
        cout << "\n==============================\n";
        cout << "HE THONG QUAN LY VI DIEM THUONG\n";
        cout << "1. Dang nhap\n";
        cout << "2. Dang ky\n";
        cout << "3. Thoat\n";
        cout << "==============================\n";
        cout << "Chon: "; cin >> chon;

        if (chon == 1) {
            User* u = login();
            if (u) {
                if (u->role == "admin") adminMenu(u);
                else userMenu(u);
            }
        } else if (chon == 2) {
            registerUser();
        } else if (chon == 3) {
            cout << ">> Tam biet!\n";
            break;
        } else {
            cout << ">> Lua chon khong hop le.\n";
        }
    }

    return 0;
}
