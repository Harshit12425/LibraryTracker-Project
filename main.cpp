#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Book class
class Book {
private:
    string name;
    string author;
    bool borrowed;

public:
    Book(string name, string author) {
        this->name = name;
        this->author = author;
        borrowed = false;
    }

    string getBookName() {
        return this->name;
    }

    string getAuthorName() {
        return this->author;
    }

    bool isBorrowed() {
        return this->borrowed;
    }

    void setBookStatus(bool f) {
        this->borrowed = f;
    }
};

// Library class
class Library {
private:
    vector<Book> list;

    // Helper to find book index by name (case insensitive)
    int findBookIndexByName(const string& bookName) {
        for (int i = 0; i < list.size(); i++) {
            string bn = list[i].getBookName();
            string bnLower = bn, targetLower = bookName;
            transform(bnLower.begin(), bnLower.end(), bnLower.begin(), ::tolower);
            transform(targetLower.begin(), targetLower.end(), targetLower.begin(), ::tolower);

            if (bnLower == targetLower)
                return i;
        }
        return -1;
    }

public:
    void addBook(Book b) {
        list.push_back(b);
    }

    void displayBooks() {
        if (list.empty()) {
            cout << "No books in library.\n";
            return;
        }
        cout << "Books in Library:\n";
        for (int i = 0; i < list.size(); i++) {
            cout << i + 1 << ". " << list[i].getBookName()
                 << " by " << list[i].getAuthorName()
                 << " [" << (list[i].isBorrowed() ? "Borrowed" : "Available") << "]\n";
        }
    }

    void displayBorrowedBooks() {
        bool found = false;
        for (int i = 0; i < list.size(); i++) {
            if (list[i].isBorrowed()) {
                cout << i + 1 << ". " << list[i].getBookName()
                     << " by " << list[i].getAuthorName() << "\n";
                found = true;
            }
        }
        if (!found) cout << "No books are currently borrowed.\n";
    }

    void borrowBook(const string& bookName) {
        int idx = findBookIndexByName(bookName);
        if (idx == -1) {
            cout << "Book not found.\n";
            return;
        }
        if (list[idx].isBorrowed()) {
            cout << "Sorry, the book is already borrowed.\n";
            return;
        }
        list[idx].setBookStatus(true);
        cout << "You have successfully borrowed \"" << list[idx].getBookName() << "\".\n";
    }

    void returnBook(const string& bookName) {
        int idx = findBookIndexByName(bookName);
        if (idx == -1) {
            cout << "Book not found.\n";
            return;
        }
        if (!list[idx].isBorrowed()) {
            cout << "This book was not borrowed.\n";
            return;
        }
        list[idx].setBookStatus(false);
        cout << "You have successfully returned \"" << list[idx].getBookName() << "\".\n";
    }
};

int main() {
    Library lib;

    while (true) {
        cout << "\n*** Library Tracker Menu ***\n";
        cout << "1. Add Book\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. Show Borrowed Books\n";
        cout << "5. Show All Books\n";
        cout << "6. Exit\n";

        int choice;
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();  // clear newline from input buffer

        if (choice == 6) {
            cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
        case 1: {
            string name, author;
            cout << "Enter book name: ";
            getline(cin, name);
            cout << "Enter author name: ";
            getline(cin, author);
            lib.addBook(Book(name, author));
            cout << "Book added successfully!\n";
            break;
        }
        case 2: {
            string name;
            cout << "Enter book name to borrow: ";
            getline(cin, name);
            lib.borrowBook(name);
            break;
        }
        case 3: {
            string name;
            cout << "Enter book name to return: ";
            getline(cin, name);
            lib.returnBook(name);
            break;
        }
        case 4:
            lib.displayBorrowedBooks();
            break;
        case 5:
            lib.displayBooks();
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    }

    return 0;
}
