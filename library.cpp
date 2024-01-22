#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "Librarian.h"
#include "Member.h"
#include "Book.h"
#include "Person.h"
using namespace std;


int main() {

    
     Librarian admin(1, "Admin", "Library", "main@library.com", 27000);

     ifstream file("library_books.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    
    string line;

    getline(file, line); //Skips line 1 because books start at line 2.
    while (getline(file, line)) {
    // Parse the line as a Book object
    Book book = Book::parseCSV(line);
    admin.addBookToLibrary(book);
    // Print details of the parsed book for debugging
    cout << "Book ID: " << book.getBookID() << ", Book Name: " << book.getBookName() << endl;
}

    file.close();

    int input;
    

    cout << "\n" << "\n" << "Welcome to the library!" << endl;
    
    do {
        cout << "Select command: Exit (0), Add member (1), View borrowed books (2), Issue a book (3), Return a Book (4), Calculate Fine (5): ";
        cin >> input;

        switch (input) {
            case 1:
                admin.addMember();
                
                break;

            case 2:
                admin.displayBorrowedBooks();
                break;

            case 3:
                int memberID, bookID;
                cout << "Enter Member ID: ";
                cin >> memberID;
                cout << "Enter Book ID: ";
                cin >> bookID;
                admin.issueBook(memberID, bookID);
                break;

            case 4:
               int returnMemberID, returnBookID;
                cout << "Enter Member ID for returning a book: ";
                cin >> returnMemberID;
                cout << "Enter Book ID for returning: ";
                cin >> returnBookID;
                admin.returnBook(returnMemberID, returnBookID);
                break;
                

            case 0:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid command. Please try again." << endl;
        }
    } while (input != 0);

    return 0;
}

//references https://stackoverflow.com/questions/49721121/reading-csv-with-fstream-and-only-fstream for csv file reading using fstream