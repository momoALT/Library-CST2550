#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Book {
    std::string bookID;
    std::string bookName;
    int pageCount;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
};

// Function to search for a book by its ID
Book findBookByID(std::ifstream& inputFile, const std::string& bookID) {
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        Book book;

        // Read book ID
        std::getline(iss, book.bookID, ',');

        // Read book name (handle quotes)
        std::getline(iss, book.bookName, ',');
        if (book.bookName.front() == '"' && book.bookName.back() != '"') {
            // The book name is spread across multiple columns, continue reading until the closing quote
            std::string additionalPart;
            std::getline(iss, additionalPart, '"');
            book.bookName += "," + additionalPart;
        }

        // Read remaining fields
        iss >> book.pageCount;
        std::getline(iss >> std::ws, book.authorFirstName, ',');
        std::getline(iss, book.authorLastName, ',');
        std::getline(iss, book.bookType, ',');

        if (book.bookID == bookID) {
            return book;
        }
    }

    // Return a book with empty values if not found
    return {"", "", 0, "", "", ""};
}

int main() {
    std::ifstream inputFile("library_books.csv");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::string searchID;
    std::cout << "Enter the Book ID: ";
    std::cin >> searchID;

    Book foundBook = findBookByID(inputFile, searchID);
    inputFile.close();

    if (foundBook.bookID.empty()) {
        std::cout << "Book not found." << std::endl;
    } else {
        std::cout << "Book Name: " << foundBook.bookName << std::endl;
        std::cout << "Author: " << foundBook.authorFirstName << " " << foundBook.authorLastName << std::endl;
    }

    return 0;
}

