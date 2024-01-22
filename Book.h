#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

// #include "Person.h" 
// #include "Member.h"
// #include "Librarian.h"

class Member;
class Librarian;

class Book {
private:
    int bookID;
    string bookName;
    int pageCount;
    string authorFirstName;
    string authorLastName;
    string bookType;
    std::time_t dueDate;
    Member* borrower;

public:

Member* getBorrower() const {
        return borrower;
    }

    std::string getDueDateAsString() const {
        return std::ctime(&dueDate);
    }

bool isBorrowed() const {
        return borrower != nullptr;
    }
    Book(int id, const string& name, int count, const string& firstName, const string& lastName, const string& type)
        : bookID(id), bookName(name), pageCount(count), authorFirstName(firstName), authorLastName(lastName), bookType(type), borrower(nullptr) {}

    int getBookID() const {
        return bookID;
    }

    string getBookName() const {
        return bookName;
    }

    string getAuthorFirstName() const {
        return authorFirstName;
    }

    string getAuthorLastName() const {
        return authorLastName;
    }

//     std::string Book::getBorrowerName() const {
//     if (borrower) {
//         return borrower->getName();
//     } else {
//         return "N/A";
//     }
// }

//     std::string Book::getDueDateAsString() const {
//     if (borrower) {
//         return std::ctime(&dueDate);
//     } else {
//         return "N/A";
//     }
// }

    void returnBook() {
        borrower = nullptr;
    }

    void borrowBook(Member* borrower, std::time_t dueDate) {
        this->borrower = borrower;
        this->dueDate = dueDate;
    }

   static Book parseCSV(const string& line) {
    cout << "Parsing CSV line: " << line << endl;

    stringstream ss(line);
    string token;

    // information from tokens
    getline(ss, token, ',');
    int bookID = stoi(token);
    
    getline(ss, token, ','); // Book Name
    if (token.front() == '"' && token.back() != '"') { //Checks if the begginning has a " and the end does not have a ". if only goes through if both conditions are met using the and.
        // The book name is split across multiple tokens
        string additionalToken;
        do {
            getline(ss, additionalToken, ',');
            token += "," + additionalToken;
        } while (additionalToken.empty() || additionalToken.back() != '"');
    }
    string bookName = token;

    getline(ss, token, ','); 
    int pageCount = stoi(token);

    getline(ss, token, ',');
    string authorFirstName = token;

    getline(ss, token, ',');
    string authorLastName = token;

    getline(ss, token, ',');
    string bookType = token;

    cout << "Book: ID=" << bookID << ", Name=" << bookName << ", PageCount=" << pageCount
         << ", AuthorFirstName=" << authorFirstName << ", AuthorLastName=" << authorLastName << ", BookType=" << bookType << endl;

    // Return a Book object with the extracted information
    return Book(bookID, bookName, pageCount, authorFirstName, authorLastName, bookType);
}




};

//references: https://www.softwaretestinghelp.com/stringstream-class-in-cpp/ for sstream
//https://www.w3schools.com/cpp/cpp_oop.asp classes
#endif // BOOK_H