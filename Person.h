#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

class Book;

class Person {
protected:
    std::string name;
    std::string address;
    std::string email;

public:
    std::string getName() const {
        return name;
    }

    void setName(const std::string& n) {
        name = n;
    }

    std::string getAddress() const {
        return address;
    }

    void setAddress(const std::string& a) {
        address = a;
    }

    std::string getEmail() const {
        return email;
    }

    void setEmail(const std::string& e) {
        email = e;
    }
};

#endif // PERSON_H