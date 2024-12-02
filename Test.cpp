#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <regex>
#include <chrono>
#include <iomanip>

using namespace std;

// Exception Classes
class ValidationException : public runtime_error {
public:
    ValidationException(const string& message) : runtime_error(message) {}
};

class BookingException : public runtime_error {
public:
    BookingException(const string& message) : runtime_error(message) {}
};

// Abstraction: Payment Strategy Interface
class PaymentStrategy {
public:
    virtual bool processPayment(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};

// Concrete Payment Strategies
class CashPayment : public PaymentStrategy {
public:
    bool processPayment(double amount) override {
        cout << "Processing Cash Payment of Php " << amount << endl;
        return true;
    }
};

class DigitalWalletPayment : public PaymentStrategy {
private:
    string walletId;

public:
    bool processPayment(double amount) override {
        cout << "Processing Digital Wallet Payment of Php " << amount << endl;
        return true;
    }
};

class CreditCardPayment : public PaymentStrategy {
public:
    bool processPayment(double amount) override {
        cout << "Processing Credit/Debit Card Payment of Php " << amount << endl;
        return true;
    }
};

// Base Room Class (Abstraction)
class Room {
protected:
    string roomId;
    string roomType;
    double pricePerNight;
    int maxOccupancy;
    string features;
    string status;

public:
    Room(const string& id, const string& type, double price, int occupancy, const string& roomFeatures)
        : roomId(id), roomType(type), pricePerNight(price), maxOccupancy(occupancy), features(roomFeatures), status("Available") {}

    // Encapsulation: Getters and Setters
    virtual string getRoomDetails() const {
        return "Room ID: " + roomId + "\nType: " + roomType + 
               "\nPrice: Php " + to_string(pricePerNight) + 
               "\nMax Occupancy: " + to_string(maxOccupancy) + 
               "\nFeatures: " + features + 
               "\nStatus: " + status;
    }

    // Polymorphic method
    virtual double calculateTotalPrice(int nights) const {
        return pricePerNight * nights;
    }

    // Getters
    string getRoomId() const { return roomId; }
    string getRoomType() const { return roomType; }
    double getPricePerNight() const { return pricePerNight; }
    string getStatus() const { return status; }

    // Setters with validation
    void setStatus(const string& newStatus) {
        if (newStatus != "Available" && newStatus != "Occupied" && newStatus != "Under Maintenance") {
            throw ValidationException("Invalid room status");
        }
        status = newStatus;
    }

    void setPrice(double newPrice) {
        if (newPrice <= 0) {
            throw ValidationException("Price must be positive");
        }
        pricePerNight = newPrice;
    }
};

// Derived Room Classes (Inheritance)
class DeluxeRoom : public Room {
public:
    DeluxeRoom(const string& id) 
        : Room(id, "Deluxe Room", 6000, 4, "2 Queen Beds, Free Wi-Fi, Ensuite Bathroom, Ocean View") {}
};

class StandardRoom : public Room {
public:
    StandardRoom(const string& id) 
        : Room(id, "Standard Room", 2000, 2, "1 Double Bed, Free Wi-Fi, Shared Bathroom, City View") {}
};

class SuiteRoom : public Room {
public:
    SuiteRoom(const string& id) 
        : Room(id, "Suite", 10000, 3, "1 King Bed, Living Area, Free Wi-Fi, Jacuzzi, Private Balcony") {}
};

class FamilyRoom : public Room {
public:
    FamilyRoom(const string& id) 
        : Room(id, "Family Room", 8000, 6, "2 Queen Beds, 1 Sofa Bed, Free Wi-Fi, Kitchenette, Garden View") {}
};

// User Class
class User {
protected:
    string name;
    string email;
    string password;

    // Email validation
    bool isValidEmail(const string& email) {
        const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
        return regex_match(email, pattern);
    }

public:
    User(const string& userName, const string& userEmail, const string& userPassword)
        : name(userName), email(userEmail), password(userPassword) {
        
        if (!isValidEmail(email)) {
            throw ValidationException("Invalid email format");
        }

        if (password.length() < 8) {
            throw ValidationException("Password must be at least 8 characters long");
        }
    }

    // Getters and setters with validation
    void setEmail(const string& newEmail) {
        if (!isValidEmail(newEmail)) {
            throw ValidationException("Invalid email format");
        }
        email = newEmail;
    }

    void setPassword(const string& newPassword) {
        if (newPassword.length() < 8) {
            throw ValidationException("Password must be at least 8 characters long");
        }
        password = newPassword;
    }

    string getName() const { return name; }
    string getEmail() const { return email; }
};

// Singleton Hotel Management System
class HotelManagementSystem {
private:
    static HotelManagementSystem* instance;
    vector<Room*> rooms;
    vector<User*> users;

    // Private constructor for Singleton
    HotelManagementSystem() {
        // Initialize with default rooms
        rooms.push_back(new DeluxeRoom("RM101"));
        rooms.push_back(new StandardRoom("RM102"));
        rooms.push_back(new SuiteRoom("RM201"));
        rooms.push_back(new FamilyRoom("RM202"));
    }

public:
    // Singleton method
    static HotelManagementSystem* getInstance() {
        if (!instance) {
            instance = new HotelManagementSystem();
        }
        return instance;
    }

    // Methods for room and user management
    void displayAvailableRooms() {
        for (const auto& room : rooms) {
            cout << room->getRoomDetails() << "\n\n";
        }
    }

    Room* findRoomById(const string& roomId) {
        auto it = find_if(rooms.begin(), rooms.end(), 
            [&roomId](const Room* room) { return room->getRoomId() == roomId; });
        
        if (it != rooms.end()) {
            return *it;
        }
        throw BookingException("Room not found");
    }

    // Destructor to clean up dynamically allocated memory
    ~HotelManagementSystem() {
        for (auto room : rooms) delete room;
        for (auto user : users) delete user;
    }
};

// Initialize the static instance
HotelManagementSystem* HotelManagementSystem::instance = nullptr;



// Main Application
int main() {
    try {
        HotelManagementSystem* hotelSystem = HotelManagementSystem::getInstance();
        
        int choice;
        do {
            cout << "Hotel Management System\n";
            cout << "1. Guest Login\n";
            cout << "2. Admin Login\n";
            cout << "3. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    // Guest Login Flow
                    string name, email, password;
                    cout << "Hotel Management System - Guest Login\n";
                    cout << "1. Create Account\n2. Login Account\n3. Back\n";
                    cout << "Choose an option: ";
                    cin >> choice;

                    switch (choice) {
                        case 1: {
                            cout << "Enter Name: ";
                            cin.ignore();
                            getline(cin, name);
                            
                            cout << "Enter Email: ";
                            getline(cin, email);
                            
                            cout << "Enter Password: ";
                            getline(cin, password);

                            try {
                                User* newUser = new User(name, email, password);
                                cout << "You have successfully created your account!\n";
                            } catch (const ValidationException& e) {
                                cerr << "Account Creation Failed: " << e.what() << endl;
                            }
                            break;
                        }
                        // Additional login and booking logic would be implemented here
                    }
                    break;
                }
                case 2: {
                    // Admin Login Flow
                    string adminName, adminEmail, adminPassword;
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, adminName);
                    
                    cout << "Enter Email: ";
                    getline(cin, adminEmail);
                    
                    cout << "Enter Password: ";
                    getline(cin, adminPassword);

                    cout << "Available Rooms:\n";
                    hotelSystem->displayAvailableRooms();
                    break;
                }
                case 3:
                    cout << "Thank you for using the Hotel Management System.\n";
                    break;
                default:
                    cout << "Invalid option. Please try again.\n";
            }
        } while (choice != 3);

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}