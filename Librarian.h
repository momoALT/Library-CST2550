#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "Person.h" 
#include "Book.h"
#include "Member.h"

using namespace std;


class Member;
class Book;

class Librarian : public Person {
private:
    int staffID;
    int salary;
    vector<Member> members;
    vector<Book> books;

public:
    Librarian(int id, const string& n, const string& a, const string& e, int s)
        : staffID(id), salary(s) {
        setName(n);
        setAddress(a);
        setEmail(e);
    }

    int getStaffID() const {
        return staffID;
    }

    void setStaffID(int id) {
        staffID = id;
    }

    int getSalary() const {
        return salary;
    }

    void setSalary(int s) {
        salary = s;
    }

    void addMember() {
        int memberID;
        string memberName;
        string memberAddress;
        string memberEmail;

        // Get member details from the librarian
        cout << "Enter Member ID: ";
        cin >> memberID;
        cout << "Enter Member Name: ";
        cin.ignore(); 
        getline(cin, memberName);
        cout << "Enter Member Address: ";
        getline(cin, memberAddress);
        cout << "Enter Member Email: ";
        getline(cin, memberEmail);

        // Create a Member object and add it to the members vector
        members.push_back(Member(memberID, memberName, memberAddress, memberEmail));

        cout << "Member added successfully!" << endl;
    }

   void displayBorrowedBooks() const {

    // Display borrowed books for all members
    cout << "Borrowed Books:" << endl;
    for (const auto& book : books) {
        if (book.isBorrowed()) {
            cout << "\n" << "Book ID: " << book.getBookID() << endl;
            cout << "Name: " << book.getBookName() << ", Author: " << book.getAuthorFirstName() << " " << book.getAuthorLastName() << endl;
            //cout << "Borrower: " << book.getBorrower()->getName() << endl;  // Display borrower name
            cout << "Borrower ID: " << book.getBorrower()->getMemberID() << endl; // Display borrower ID
            cout << "Due Date: " << book.getDueDateAsString();// Display due date
            cout << "---------------------------" << endl;//Closes with line so it looks organized and easy to read
        }
    }
  
}


   void issueBook(int memberID, int bookID) {
    // Find the member with the given ID
    auto memberIt = std::find_if(members.begin(), members.end(), [memberID](const Member& member) {
        return member.getMemberID() == memberID;
    });

    if (memberIt != members.end()) {
        // Find the book with the given ID
        auto bookIt = std::find_if(books.begin(), books.end(), [bookID](const Book& book) {
            return book.getBookID() == bookID && !book.isBorrowed();
        });

        if (bookIt != books.end()) {
            // Issue the book to the member
            memberIt->setBooksBorrowed(&(*bookIt));

            std::cout << "Book \"" << bookIt->getBookName() << "\" issued to Member ID " << memberID << " successfully!" << std::endl;
        } else {
            std::cout << "Book with ID " << bookID << " not available for issue or already borrowed." << std::endl;
        }
    } else {
        std::cout << "Member with ID " << memberID << " not found." << std::endl;
    }
}

void returnBook(int memberID, int bookID) {
   
    auto memberIt = std::find_if(members.begin(), members.end(), [memberID](const Member& member) {
        return member.getMemberID() == memberID;
    });

    if (memberIt != members.end()) {
        
        auto bookIt = std::find_if(books.begin(), books.end(), [bookID, memberID](const Book& book) {
            return book.getBookID() == bookID && book.isBorrowed() && book.getBorrower()->getMemberID() == memberID;
        });

        if (bookIt != books.end()) {
            // Return book
            bookIt->returnBook();

            // Remove the book from the member
            auto borrowedBooks = memberIt->getBooksBorrowed();
            borrowedBooks.erase(std::remove_if(borrowedBooks.begin(), borrowedBooks.end(), [bookID](const Book* book) {
                return book->getBookID() == bookID;
            }), borrowedBooks.end());

            std::cout << "Book \"" << bookIt->getBookName() << "\" returned by Member ID " << memberID << " successfully!" << std::endl;
        } else {
            std::cout << "Book with ID " << bookID << " not borrowed by Member ID " << memberID << "." << std::endl;
        }
    } else {
        std::cout << "Member with ID " << memberID << " not found." << std::endl;
    }
}


void addBookToLibrary(const Book& book) {
        books.push_back(book);
    }
};
// references: https://www.w3schools.com/cpp/cpp_oop.asp classes
#endif // LIBRARIAN_H