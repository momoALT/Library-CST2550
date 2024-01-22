#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;
class Person;
class Book;
class Member;
class Librarian;

class Person {
protected:
    string name;
    string address;
    string email;

public:
    string getName() const {
        return name;
    }

    void setName(const string& n) {
        name = n;
    }

    string getAddress() const {
        return address;
    }

    void setAddress(const string& a) {
        address = a;
    }

    string getEmail() const {
        return email;
    }

    void setEmail(const string& e) {
        email = e;
    }
};

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
        // Additional logic for handling book return
    }

    void borrowBook(Member* borrower, std::time_t dueDate) {
        this->borrower = borrower;
        this->dueDate = dueDate;
        // Additional logic for handling book borrow
    }

   static Book parseCSV(const string& line) {
    cout << "Parsing CSV line: " << line << endl;

    stringstream ss(line);
    string token;

    // information from tokens
    getline(ss, token, ',');
    int bookID = stoi(token);
    
    getline(ss, token, ','); // Book Name
    if (token.front() == '"' && token.back() != '"') { //Checks if the begginning has a " and the end has a ". if only goes through if both conditions are met using the and.
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
        cin.ignore();  // Ignore any newline character left in the input buffer
        getline(cin, memberName);
        cout << "Enter Member Address: ";
        getline(cin, memberAddress);
        cout << "Enter Member Email: ";
        getline(cin, memberEmail);

        // Create a Member object and add it to the members vector
        members.push_back(Member(memberID, memberName, memberAddress, memberEmail));

        cout << "Member added successfully!" << endl;
    }

    void displayAllMembers() const {
        cout << "All Members:" << endl;
        for (const auto& member : members) {
            member.displayInformation();
        }
        cout << "---------------------------" << endl;
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
        // Find the member with ID
        auto memberIt = std::find_if(members.begin(), members.end(), [memberID](const Member& member) {
            return member.getMemberID() == memberID;
        });

        if (memberIt != members.end()) {
            // Find the book with ID
            auto bookIt = std::find_if(books.begin(), books.end(), [bookID, memberID](const Book& book) {
            return book.getBookID() == bookID && book.isBorrowed() && book.getBorrower()->getMemberID() == memberID;
});


            if (bookIt != books.end()) {
                // Return the book
                bookIt->returnBook();

                std::cout << "Book \"" << bookIt->getBookName() << "\" returned by Member ID " << memberID << " successfully!" << std::endl;
            } else {
                std::cout << "Book with ID " << bookID << " not borrowed by Member ID " << memberID << "." << std::endl;
            }
        } else {
            std::cout << "Member with ID " << memberID << " not found." << std::endl;
        }
    }

void displayBorrowedBooks() const {
    cout << "Borrowed Books:" << endl;
    for (const auto& book : books) {
        if (book.isBorrowed()) {
            cout << "Book ID: " << book.getBookID() << endl;
            cout << "Name: " << book.getBookName() << ", Author: " << book.getAuthorFirstName() << " " << book.getAuthorLastName() << endl;
            
            // Display borrower's name
            //cout << "Borrower: " << book.getBorrowerName() << endl;
            
            // Display due date
            //cout << "Due Date: " << book.getDueDateAsString();

            cout << "---------------------------" << endl;
        }
    }
}









void addBookToLibrary(const Book& book) {
        books.push_back(book);
    }
};

int main() {

    
     Librarian admin(1, "Admin", "Library", "main@library.com", 27000);

     ifstream file("library_books.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    // Read the first line of the CSV file
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
    

    cout << "Welcome to the library!" << endl;
    
    do {
        cout << "Select command: Exit (0), Add member (1), Display all members (2), Issue a book (3), Return a Book (4): ";
        cin >> input;

        switch (input) {
            case 1:
                admin.displayBorrowedBooks();
                admin.addMember();
                
                break;

            case 2:
                admin.displayAllMembers();
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