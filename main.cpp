#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>


// Class Error Handling
class UserDataException : public std::exception {
public:
    const char* what() const noexcept override {
        return "User Error exception occured.";
    }
};

class InvalidNameException : public UserDataException {
public:
    const char* what() const noexcept override {
        return "Name must not be empty and contain digits.";
    }
};

class InvalidAgeException : public UserDataException {
public:
    const char* what() const noexcept override {
        return "Age must be a positive integer.";
    }
};

class InvalidEmailException : public UserDataException {
public: 
    const char* what() const noexcept override {
        return "Email must contain proper domain requirements ('@'.)";
    }
};

// Function User Data
void validateUserData(const std::string& name, int age, const std::string& email) {
    if (name.empty() || name.find_first_of("0123456789") != std::string::npos) {
        throw InvalidNameException();
    }
    if (age <= 0) {
        throw InvalidAgeException();
    }
    if (email.find('@') == std::string::npos) {
        throw InvalidEmailException();
    }
}

int main() {
    std::string filename;
    std::cout << "Enter the filename (with path if necessary): ";
    std::getline(std::cin, filename);

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: File not found!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string name, email;
        int age;

        std::getline(ss, name, ',');
        ss >> age;
        ss.ignore(); 
        std::getline(ss, email);

        try {
            validateUserData(name, age, email);
            std::cout << "Successfully processed: " << name << ", " << age << ", " << email << std::endl;
        } catch (const InvalidNameException& e) {
            std::cout << "Invalid data for user: " << line << ". Error: " << e.what() << std::endl;
        } catch (const InvalidAgeException& e) {
            std::cout << "Invalid data for user: " << line << ". Error: " << e.what() << std::endl;
        } catch (const InvalidEmailException& e) {
            std::cout << "Invalid data for user: " << line << ". Error: " << e.what() << std::endl;
        }
    }

    file.close();
    return 0;
};
