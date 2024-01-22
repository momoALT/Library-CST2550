#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

#include "Person.h"
#include "Book.h"



class Member : public Person {
private:
    int memberID;
    vector<Book*> booksLoaned;

public:
    Member(int id, const string& n, const string& a, const string& e)
        : memberID(id) {
        setName(n);
        setAddress(a);
        setEmail(e);
    }

    int getMemberID() const {
        return memberID;
    }

    const vector<Book*>& getBooksBorrowed() const {
        return booksLoaned;
    }

    void setBooksBorrowed(Book* book) {
    booksLoaned.push_back(book);
    book->borrowBook(this, std::time(nullptr) + 3 * 24 * 60 * 60); // 3 days from now
}

   void displayInformation() const {
    cout << "Member ID: " << getMemberID() << endl;
    cout << "Name: " << getName() << ", Address: " << getAddress() << ", Email: " << getEmail() << endl;
    cout << "Books Borrowed:" << endl;
    if (booksLoaned.empty()) {
        cout << " - No books borrowed." << endl;
    } else {
        for (const auto& book : booksLoaned) {
            cout << " - " << book->getBookName() << endl;
        }
    }
    cout << "---------------------------" << endl;
}
    
};


#endif // MEMBER_H