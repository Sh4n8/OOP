#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Room {
protected:
    string roomNo;
    string roomType;
    double price;
    bool isAvailable;
    string features;
    int maxOccupancy;

public:
    Room(string no, string type, double p, string f, int maxOcc) 
        : roomNo(no), roomType(type), price(p), isAvailable(true), features(f), maxOccupancy(maxOcc) {}

    string getRoomNo() const { return roomNo; }
    string getRoomType() const { return roomType; }
    double getRoomPrice() const { return price; }
    bool getRoomAvailability() const { return isAvailable; }
    string getRoomFeatures() const { return features; }
    int getMaxOccupancy() const { return maxOccupancy; }

    void setRoomAvailability(bool available) { isAvailable = available; }

    virtual void displayRoomInfo() const {
        cout << "[ID: " << roomNo << "] " << roomType << endl
             << "   - Features: " << features << endl
             << "   - Price: Php " << price << "/night" << endl
             << "   - Max Occupancy: " << maxOccupancy << " Guests" << endl;
    }

    virtual ~Room() {}
};

// Derived classes for different room types
class DeluxeRoom : public Room {
public:
    DeluxeRoom(string no) : Room(no, "Deluxe Room", 6000, "2 Queen Beds, Free Wi-Fi, Ensuite Bathroom, Ocean View", 4) {}
};

class StandardRoom : public Room {
public:
    StandardRoom(string no) : Room(no, "Standard Room", 2000, "1 Double Bed, Free Wi-Fi, Shared Bathroom, City View", 2) {}
};

class SuiteRoom : public Room {
public:
    SuiteRoom(string no) : Room(no, "Suite", 10000, "1 King Bed, Living Area, Free Wi-Fi, Jacuzzi, Private Balcony", 3) {}
};

class FamilyRoom : public Room {
public:
    FamilyRoom(string no) : Room(no, "Family Room", 8000, "2 Queen Beds, 1 Sofa Bed, Free Wi-Fi, Kitchenette, Garden View", 6) {}
};

// Booking class with payment method
class Booking {
private:
    string bookingID;
    string roomNo;
    string fromDate;
    string toDate;
    int numberOfGuests;
    string paymentMethod;
    double totalPrice;

public:
    Booking(string id, string room, string from, string to, int guests, string payment, double price) 
        : bookingID(id), roomNo(room), fromDate(from), toDate(to), numberOfGuests(guests), paymentMethod(payment), totalPrice(price) {}

    void displayBookingDetails() const {
        cout << "Booking ID: " << bookingID << endl
             << "Room: " << roomNo << endl
             << "Check-in: " << fromDate << endl
             << "Check-out: " << toDate << endl
             << "Guests: " << numberOfGuests << endl
             << "Total Price: Php " << totalPrice << endl
             << "Payment Method: " << paymentMethod << endl;
    }

    string getBookingID() const { return bookingID; }
    double getTotalPrice() const { return totalPrice; }
    string getPaymentMethod() const { return paymentMethod; }
};

class User {
protected:
    string name, email, password, role;

public:
    User(string n, string e, string p, string r) : name(n), email(e), password(p), role(r) {}

    // Getter for role
    string getRole() const { return role; }

    virtual void createAccount() = 0;
    virtual void deleteAccount() = 0;

    static User* login(vector<User*>& users, string email, string password) {
        for (auto& user : users) {
            if (user->email == email && user->password == password) {
                cout << "Login successful! Welcome, " << user->name << endl;
                return user;
            }
        }
        cout << "Invalid email or password.\n";
        return nullptr;
    }
};

class Admin : public User {
public:
    Admin(string n, string e, string p) : User(n, e, p, "Admin") {}

    void createAccount() override {
        cout << "Admin account created for: " << name << endl;
    }

    void deleteAccount() override {
        cout << "Admin account deleted for: " << name << endl;
    }

    void generateReport() const {
        cout << "----------[Hotel Name] Generate Report----------\n";
        cout << "1. Daily Summary\n";
        cout << "2. Weekly Summary\n";
        cout << "3. Monthly Summary\n";
        cout << "4. Custom Range\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            cout << "Daily Summary Report: 2024-12-01\n";
            cout << "--------------------------------\n";
            cout << "Total Guests Checked In: 10\n";
            cout << "Total Revenue Collected: Php 130,000\n";
            cout << "Rooms Occupied: 80%\n";
            cout << "Refunds Issued: Php 5,000\n";
        }
    }
};

class Customer : public User {
    vector<Booking*> bookings;
public:
    Customer(string n, string e, string p) : User(n, e, p, "Customer") {}

    void createAccount() override {
        cout << "Customer account created for: " << name << endl;
    }

    void deleteAccount() override {
        cout << "Customer account deleted for: " << name << endl;
    }

    void bookRoom(string roomNo, string fromDate, string toDate, int guests, string paymentMethod, double price) {
        string bookingID = "B" + to_string(bookings.size() + 1); // Example of generating a booking ID
        Booking* newBooking = new Booking(bookingID, roomNo, fromDate, toDate, guests, paymentMethod, price);
        bookings.push_back(newBooking);
        cout << "Booking confirmed! Your Booking ID: " << bookingID << endl;
    }

    void cancelBooking(string bookingID) {
        for (auto it = bookings.begin(); it != bookings.end(); ++it) {
            if ((*it)->getBookingID() == bookingID) {
                cout << "Cancelling booking: " << bookingID << endl;
                delete *it;
                bookings.erase(it);
                cout << "Booking cancelled successfully.\n";
                return;
            }
        }
        cout << "Booking ID not found.\n";
    }

    void viewBookingHistory() const {
        cout << "Booking History for " << name << ":\n";
        for (auto& booking : bookings) {
            booking->displayBookingDetails();
        }
    }
};

// Main function with hotel flow
int main() {
    vector<User*> users;
    vector<Room*> rooms;
    bool running = true;

    rooms.push_back(new DeluxeRoom("RM101"));
    rooms.push_back(new StandardRoom("RM102"));
    rooms.push_back(new SuiteRoom("RM201"));
    rooms.push_back(new FamilyRoom("RM202"));

    // Create sample users
    users.push_back(new Customer("John Doe", "john@example.com", "password123"));
    users.push_back(new Customer("Jane Smith", "jane@example.com", "password456"));

    while (running) {
        cout << "Hotel Management System\n";
        cout << "1. Guest Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Register as Customer\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: { // Guest Login
                string email, password;
                cout << "Enter Email: ";
                cin >> email;
                cout << "Enter Password: ";
                cin >> password;

                User* loggedInUser = User::login(users, email, password);
                if (loggedInUser && loggedInUser->getRole() == "Customer") {  // Using the getter
                    Customer* customer = static_cast<Customer*>(loggedInUser);
                    bool guestMenu = true;

                    while (guestMenu) {
                        cout << "\n========== Hotel Management System - Guest Menu ==========\n";
                        cout << "1. View Room Available\n";
                        cout << "2. Book Room\n";
                        cout << "3. Edit Booking\n";
                        cout << "4. Cancel Booking\n";
                        cout << "5. View Booking and Payment History\n";
                        cout << "6. Edit Account\n";
                        cout << "7. Delete Account\n";
                        cout << "8. Logout\n";
                        cout << "Choose an option: ";
                        int guestOption;
                        cin >> guestOption;

                        switch (guestOption) {
                            case 1: { // View Available Rooms
                                cout << "----------[Hotel Name] Available Rooms----------\n";
                                for (size_t i = 0; i < rooms.size(); ++i) {
                                    rooms[i]->displayRoomInfo();
                                    cout << endl;
                                }
                                break;
                            }
                            case 2: { // Book Room
                                string roomNo, fromDate, toDate, paymentMethod;
                                int guests;
                                cout << "Enter the Room ID you want to book: ";
                                cin >> roomNo;
                                cout << "Enter Check-in Date (YYYY-MM-DD): ";
                                cin >> fromDate;
                                cout << "Enter Check-out Date (YYYY-MM-DD): ";
                                cin >> toDate;
                                cout << "Enter the Number of Guests: ";
                                cin >> guests;
                                cout << "Choose Payment Method (1: Cash, 2: Digital Wallet, 3: Credit/Debit Card): ";
                                int paymentChoice;
                                cin >> paymentChoice;
                                switch (paymentChoice) {
                                    case 1: paymentMethod = "Cash"; break;
                                    case 2: paymentMethod = "Digital Wallet"; break;
                                    case 3: paymentMethod = "Credit/Debit Card"; break;
                                }
                                double price = 2000; // Example room price, adjust based on room
                                customer->bookRoom(roomNo, fromDate, toDate, guests, paymentMethod, price);
                                break;
                            }
                            case 3: { // Edit Booking
                                string bookingID;
                                cout << "Enter Booking ID to edit: ";
                                cin >> bookingID;
                                // Add logic to edit booking details here.
                                break;
                            }
                            case 4: { // Cancel Booking
                                string bookingID;
                                cout << "Enter Booking ID to cancel: ";
                                cin >> bookingID;
                                customer->cancelBooking(bookingID);
                                break;
                            }
                            case 5: { // View Booking and Payment History
                                customer->viewBookingHistory();
                                break;
                            }
                            case 6: { // Edit Account
                                // Logic to edit account details (email, password)
                                break;
                            }
                            case 7: { // Delete Account
                                customer->deleteAccount();
                                guestMenu = false;
                                break;
                            }
                            case 8: { // Logout
                                guestMenu = false;
                                break;
                            }
                            default:
                                cout << "Invalid option. Try again.\n";
                        }
                    }
                }
                break;
            }
            case 2: { // Admin Login
                string email, password;
                cout << "Enter Email: ";
                cin >> email;
                cout << "Enter Password: ";
                cin >> password;

                User* loggedInAdmin = User::login(users, email, password);
                if (loggedInAdmin && loggedInAdmin->getRole() == "Admin") {
                    Admin* admin = dynamic_cast<Admin*>(loggedInAdmin);
                    bool adminMenuActive = true;
                    while (adminMenuActive) {
                        cout << "1. Generate Report\n";
                        cout << "2. Logout\n";
                        cout << "Enter your choice: ";
                        int adminChoice;
                        cin >> adminChoice;
                        switch (adminChoice) {
                            case 1: {
                                admin->generateReport();
                                break;
                            }
                            case 2:
                                adminMenuActive = false;
                                break;
                            default:
                                cout << "Invalid option.\n";
                        }
                    }
                }
                break;
            }
            case 3: { // Register as Customer
                string name, email, password;
                cout << "Enter your Name: ";
                cin >> name;
                cout << "Enter your Email: ";
                cin >> email;
                cout << "Enter your Password: ";
                cin >> password;

                User* newCustomer = new Customer(name, email, password);
                newCustomer->createAccount();
                users.push_back(newCustomer);
                break;
            }
            case 4:
                running = false;
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }

    // Cleanup memory (deleting rooms, users, etc.)
    for (auto user : users) delete user;
    for (auto room : rooms) delete room;

    return 0;
}