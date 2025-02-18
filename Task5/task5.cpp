#include <iostream>
#include <vector>
#include <iomanip>
#include <termios.h>
#include <unistd.h>
using namespace std;

class Book {
private:
    string title, author, ISBN;
    bool isAvailable;

public:
    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isAvailable(true) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    bool getAvailability() const { return isAvailable; }

    void checkoutBook() {
        if (isAvailable) {
            isAvailable = false;
            cout << "📖 Book checked out successfully!\n";
        } else {
            cout << "⚠️ Book is currently unavailable.\n";
        }
    }

    void returnBook() {
        isAvailable = true;
        cout << "📚 Book returned successfully!\n";
    }

    void displayBook() const {
        cout << left << setw(20) << title << setw(20) << author << setw(15) << ISBN
             << (isAvailable ? "✅ Available" : "⛔ Checked Out") << endl;
    }
};

class Library {
private:
    vector<Book> books;
    const double finePerDay;

public:
    Library() : finePerDay(2.0) {}

    void addBook(const string& title, const string& author, const string& ISBN) {
        books.push_back(Book(title, author, ISBN));
        cout << "📚 Book added successfully!\n";
    }

    void removeBook(const string& ISBN) {
        for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == ISBN) {
                books.erase(it);
                cout << "❌ Book removed successfully!\n";
                return;
            }
        }
        cout << "⚠️ Book not found!\n";
    }

    void searchBook(const string& keyword) const {
        bool found = false;
        cout << "\n🔍 Search Results:\n";
        cout << left << setw(20) << "Title" << setw(20) << "Author" << setw(15) << "ISBN" << "Status\n";
        cout << string(65, '-') << endl;

        for (vector<Book>::const_iterator it = books.begin(); it != books.end(); ++it) {
            if (it->getTitle() == keyword || it->getAuthor() == keyword || it->getISBN() == keyword) {
                it->displayBook();
                found = true;
            }
        }
        if (!found) cout << "⚠️ No books found with that information.\n";
    }

    void checkoutBook(const string& ISBN) {
        for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == ISBN) {
                it->checkoutBook();
                return;
            }
        }
        cout << "⚠️ Book not found!\n";
    }

    void returnBook(const string& ISBN, int overdueDays) {
        for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == ISBN) {
                it->returnBook();
                if (overdueDays > 0) {
                    double fine = overdueDays * finePerDay;
                    cout << "💰 Overdue fine: ₹" << fine << "\n";
                }
                return;
            }
        }
        cout << "⚠️ Book not found!\n";
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "📭 No books available.\n";
            return;
        }
        cout << "\n📚 Library Books:\n";
        cout << left << setw(20) << "Title" << setw(20) << "Author" << setw(15) << "ISBN" << "Status\n";
        cout << string(65, '-') << endl;

        for (vector<Book>::const_iterator it = books.begin(); it != books.end(); ++it) {
            it->displayBook();
        }
    }
};

bool adminLogin() {
    string username, password;
    cout << "\n🔑 ADMIN LOGIN 🔑\n";
    cout << "👤 Username: ";
    cin >> username;
    cin.ignore();

    cout << "🔒 Password: ";

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch;
    while (true) {
        ch = getchar();
        if (ch == 10) break;
        else if (ch == 127) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else if (ch >= 32 && ch <= 126) {
            password.push_back(ch);
            cout << "*";
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cout << endl;

    if (username == "admin" && password == "lib123") {
        cout << "✅ Login successful!\n";
        return true;
    } else {
        cout << "❌ Invalid credentials!\n";
        return false;
    }
}

int main() {
    Library library;
    int role;

    do {
        cout << "🏛 Welcome to the Library Management System 🏛\n";
        cout << "1️⃣ Admin Login\n2️⃣ User Login\n3️⃣ Exit\nEnter your role: ";
        cin >> role;
        cin.ignore();

        if (role == 1) {  
            if (!adminLogin()) {
                cout << "🔒 Access denied.\n";
                continue;
            }

            int choice;
            bool logout = false;
            do {
                cout << "\n🔑 ADMIN MENU 🔑\n";
                cout << "1️⃣ Add Book\n2️⃣ Remove Book\n3️⃣ View All Books\n4️⃣ Logout\n5️⃣ Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();

                switch (choice) {
                    case 1: {
                        string title, author, ISBN;
                        cout << "📖 Enter Book Title: ";
                        getline(cin, title);
                        cout << "✍️ Enter Author Name: ";
                        getline(cin, author);
                        cout << "🔢 Enter ISBN: ";
                        getline(cin, ISBN);
                        library.addBook(title, author, ISBN);
                        break;
                    }
                    case 2: {
                        string ISBN;
                        cout << "❌ Enter ISBN of book to remove: ";
                        getline(cin, ISBN);
                        library.removeBook(ISBN);
                        break;
                    }
                    case 3:
                        library.displayAllBooks();
                        break;
                    case 4:
                        cout << "🔒 Admin logged out.\n\n";
                        logout = true;
                        break;
                    case 5:
                        cout << "❌ Exiting system.\n";
                        return 0;
                    default:
                        cout << "⚠️ Invalid choice!\n";
                }
            } while (!logout);
        } 
        else if (role == 2) {  
            int choice;
            bool logout = false;
            do {
                cout << "\n👤 USER MENU 👤\n";
                cout << "1️⃣ Search Book\n2️⃣ Checkout Book\n3️⃣ Return Book\n4️⃣ View Available Books\n5️⃣ Logout\n6️⃣ Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();

                switch (choice) {
                    case 1: {
                        string keyword;
                        cout << "🔍 Enter Title, Author, or ISBN to search: ";
                        getline(cin, keyword);
                        library.searchBook(keyword);
                        break;
                    }
                    case 2: {
                        string ISBN;
                        cout << "📖 Enter ISBN of the book to checkout: ";
                        getline(cin, ISBN);
                        library.checkoutBook(ISBN);
                        break;
                    }
                    case 3: {
                        string ISBN;
                        int days;
                        cout << "📖 Enter ISBN of the book to return: ";
                        getline(cin, ISBN);
                        cout << "📅 Enter number of overdue days (0 if none): ";
                        cin >> days;
                        library.returnBook(ISBN, days);
                        break;
                    }
                    case 4:
                        library.displayAllBooks();
                        break;
                    case 5:
                        cout << "🔓 User logged out.\n\n";
                        logout = true;
                        break;
                    case 6:
                        cout << "❌ Exiting system.\n";
                        return 0;
                    default:
                        cout << "⚠️ Invalid choice!\n";
                }
            } while (!logout);
        } 
        else if (role == 3) {
            cout << "❌ Exiting system.\n";
            return 0;
        }
        else {
            cout << "⚠️ Invalid role selected!\n";
        }
    } while (role != 3);

    return 0;
}
