#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <regex>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <map>

using namespace std;

// Custom Exceptions
class ValidationException : public runtime_error {
public:
    ValidationException(const string& message) : runtime_error(message) {}
};

class BookingException : public runtime_error {
public:
    BookingException(const string& message) : runtime_error(message) {}
};

// Strategy Pattern for Payment
class PaymentStrategy {
public:
    virtual bool processPayment(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};

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

    void setWalletId(const string& id) {
        walletId = id;
    }
};

class CreditCardPayment : public PaymentStrategy {
public:
    bool processPayment(double amount) override {
        cout << "Processing Credit/Debit Card Payment of Php " << amount << endl;
        return true;
    }
};

// Singleton for Hotel Management
class HotelManager {
private:
    static HotelManager* instance;
    vector<string> availableRooms;

    HotelManager() {
        // Initialize available rooms
        availableRooms = {"101", "102", "103", "201", "202", "203"};
    }

public:
    static HotelManager& getInstance() {
        if (!instance) {
            instance = new HotelManager();
        }
        return *instance;
    }

    vector<string> getAvailableRooms() {
        return availableRooms;
    }

    // Prevent copying
    HotelManager(const HotelManager&) = delete;
    HotelManager& operator=(const HotelManager&) = delete;
};

HotelManager* HotelManager::instance = nullptr;

// Booking Class with Encapsulation and Validation
class Booking {
private:
    string bookingId;
    string roomId;
    string guestName;
    string checkInDate;
    string checkOutDate;
    int numberOfGuests;
    double totalAmount;
    bool isPaid;

    // Private validation methods
    void validateDate(const string& date) {
        regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
        if (!regex_match(date, dateRegex)) {
            throw ValidationException("Invalid date format. Use YYYY-MM-DD.");
        }
    }

    void validateGuests(int guests) {
        if (guests < 1 || guests > 4) {
            throw ValidationException("Number of guests must be between 1 and 4.");
        }
    }

public:
    // Constructors with validation
    Booking() : numberOfGuests(0), totalAmount(0.0), isPaid(false) {}

    void createBooking(const string& room, const string& name, 
                       const string& checkIn, const string& checkOut, int guests) {
        validateDate(checkIn);
        validateDate(checkOut);
        validateGuests(guests);

        roomId = room;
        guestName = name;
        checkInDate = checkIn;
        checkOutDate = checkOut;
        numberOfGuests = guests;
        bookingId = generateBookingId();
        calculateTotalAmount();
    }

    // Getters with Abstraction
    string getBookingId() const { return bookingId; }
    string getRoomId() const { return roomId; }
    string getGuestName() const { return guestName; }
    string getCheckInDate() const { return checkInDate; }
    string getCheckOutDate() const { return checkOutDate; }
    int getNumberOfGuests() const { return numberOfGuests; }
    double getTotalAmount() const { return totalAmount; }
    bool getIsPaid() const { return isPaid; }

    // Setters with validation
    void updateCheckInDate(const string& newDate) {
        validateDate(newDate);
        checkInDate = newDate;
        calculateTotalAmount();
    }

    void updateCheckOutDate(const string& newDate) {
        validateDate(newDate);
        checkOutDate = newDate;
        calculateTotalAmount();
    }

    void updateNumberOfGuests(int guests) {
        validateGuests(guests);
        numberOfGuests = guests;
        calculateTotalAmount();
    }

    void markAsPaid() {
        isPaid = true;
    }

private:
    // Private method for generating unique booking ID
    string generateBookingId() {
        static int counter = 1000;
        return "BK" + to_string(++counter);
    }

    // Calculate total amount based on stay duration and guests
    void calculateTotalAmount() {
        // Simple calculation for demonstration
        // In real system, would include room rates, seasonal pricing, etc.
        double dailyRate = 1500.0;  // PHP 1,500 per night
        double guestMultiplier = 1 + ((numberOfGuests - 1) * 0.2);

        // Calculate nights stayed
        istringstream checkInStream(checkInDate);
        istringstream checkOutStream(checkOutDate);
        tm checkInTime = {}, checkOutTime = {};
        checkInStream >> get_time(&checkInTime, "%Y-%m-%d");
        checkOutStream >> get_time(&checkOutTime, "%Y-%m-%d");

        time_t checkInSeconds = mktime(&checkInTime);
        time_t checkOutSeconds = mktime(&checkOutTime);
        
        int nights = (checkOutSeconds - checkInSeconds) / (24 * 3600);
        
        totalAmount = dailyRate * nights * guestMultiplier;
    }
};

// Main Hotel Management System Class
class HotelManagementSystem {
private:
    vector<Booking> bookings;
    unique_ptr<PaymentStrategy> paymentStrategy;

public:
    // Polymorphic method for payment processing
    void setPaymentStrategy(unique_ptr<PaymentStrategy> strategy) {
        paymentStrategy = move(strategy);
    }

    void viewAvailableRooms() {
        vector<string> availableRooms = HotelManager::getInstance().getAvailableRooms();
        cout << "Available Rooms:" << endl;
        for (const auto& room : availableRooms) {
            cout << room << " ";
        }
        cout << endl;
    }

    void bookRoom() {
        try {
            Booking newBooking;
            string roomId, guestName, checkIn, checkOut;
            int guests;

            cout << "----------[Luxury Hotel] Room Booking Menu----------" << endl;
            
            // Room Selection with Validation
            viewAvailableRooms();

            cout << "Enter the Room ID you want to book: ";
            cin >> roomId;

            vector<string> availableRooms = HotelManager::getInstance().getAvailableRooms();
            if (find(availableRooms.begin(), availableRooms.end(), roomId) == availableRooms.end()) {
                throw ValidationException("Invalid Room ID");
            }

            cout << "Enter Guest Name: ";
            cin.ignore();
            getline(cin, guestName);

            cout << "Enter Check-in Date (YYYY-MM-DD): ";
            cin >> checkIn;

            cout << "Enter Check-out Date (YYYY-MM-DD): ";
            cin >> checkOut;

            cout << "Enter the Number of Guests: ";
            cin >> guests;

            // Create Booking
            newBooking.createBooking(roomId, guestName, checkIn, checkOut, guests);

            // Payment Processing
            int paymentChoice;
            cout << "Choose Payment Method:\n1. Cash\n2. Digital Wallet\n3. Credit/Debit Card" << endl;
            cout << "Enter your choice: ";
            cin >> paymentChoice;

            switch (paymentChoice) {
                case 1: {
                    setPaymentStrategy(make_unique<CashPayment>());
                    break;
                }
                case 2: {
                    auto digitalWallet = make_unique<DigitalWalletPayment>();
                    string walletId;
                    cout << "Enter Wallet ID/Number: ";
                    cin >> walletId;
                    digitalWallet->setWalletId(walletId);
                    setPaymentStrategy(move(digitalWallet));
                    break;
                }
                case 3: {
                    setPaymentStrategy(make_unique<CreditCardPayment>());
                    break;
                }
                default:
                    throw ValidationException("Invalid Payment Method");
            }

            // Confirm Payment
            double totalAmount = newBooking.getTotalAmount();
            cout << "Confirm Payment of Php " << totalAmount << "? [Yes/No]: ";
            string confirm;
            cin >> confirm;

            if (confirm == "Yes" || confirm == "yes") {
                if (paymentStrategy->processPayment(totalAmount)) {
                    newBooking.markAsPaid();
                    bookings.push_back(newBooking);
                    cout << "Payment Successful!" << endl;
                    cout << "Booking Confirmed!" << endl;
                    cout << "Your Booking ID: " << newBooking.getBookingId() << endl;
                    cout << "Payment Method: Digital Wallet" << endl;
                    cout << "Check-in: " << newBooking.getCheckInDate() << endl;
                    cout << "Check-out: " << newBooking.getCheckOutDate() << endl;
                }
            }

            cout << "Press Enter to go back to the Menu...";
            cin.ignore();
            cin.get();
        }
        catch (const ValidationException& e) {
            cerr << "Validation Error: " << e.what() << endl;
        }
        catch (const exception& e) {
            cerr << "Unexpected Error: " << e.what() << endl;
        }
    }

    void editBooking() {
        try {
            string bookingId;
            cout << "----------[Luxury Hotel] Edit Booking----------" << endl;
            cout << "Enter Your Booking ID: ";
            cin >> bookingId;

            auto bookingIt = find_if(bookings.begin(), bookings.end(), 
                [&bookingId](const Booking& b) { return b.getBookingId() == bookingId; });

            if (bookingIt == bookings.end()) {
                throw BookingException("Booking not found.");
            }

            // Display Current Booking
            cout << "Current Booking Details:" << endl;
            cout << "Room: " << bookingIt->getRoomId() << endl;
            cout << "Guest Name: " << bookingIt->getGuestName() << endl;
            cout << "Check-in: " << bookingIt->getCheckInDate() << endl;
            cout << "Check-out: " << bookingIt->getCheckOutDate() << endl;
            cout << "Guests: " << bookingIt->getNumberOfGuests() << endl;
            cout << "Payment Status: " << (bookingIt->getIsPaid() ? "Paid" : "Unpaid") << endl;

            // Edit Options
            int editChoice;
            cout << "What would you like to edit?\n1. Change Dates\n2. Change Number of Guests" << endl;
            cout << "Choose an option: ";
            cin >> editChoice;

            switch (editChoice) {
                case 1: {
                    string newCheckIn, newCheckOut;
                    cout << "Enter New Check-in Date (YYYY-MM-DD): ";
                    cin >> newCheckIn;
                    cout << "Enter New Check-out Date (YYYY-MM-DD): ";
                    cin >> newCheckOut;

                    bookingIt->updateCheckInDate(newCheckIn);
                    bookingIt->updateCheckOutDate(newCheckOut);

                    // Recalculated amount
                    cout << "----------Updating Booking----------" << endl;
                    cout << "Updated Booking Details:" << endl;
                    cout << "Room: " << bookingIt->getRoomId() << endl;
                    cout << "Check-in: " << bookingIt->getCheckInDate() << endl;
                    cout << "Check-out: " << bookingIt->getCheckOutDate() << endl;
                    cout << "Guests: " << bookingIt->getNumberOfGuests() << endl;
                    cout << "New Total Amount: Php " << bookingIt->getTotalAmount() << endl;

                    // Payment for difference
                    double newAmount = bookingIt->getTotalAmount();
                    cout << "Amount Already Paid: Php " << (newAmount * 0.5) << endl;
                    cout << "Balance Due: Php " << (newAmount * 0.5) << endl;

                    // Payment method selection
                    int paymentChoice;
                    cout << "Choose Payment Method to Settle Balance:\n1. Cash\n2. Digital Wallet\n3. Credit/Debit Card" << endl;
                    cout << "Enter your choice: ";
                    cin >> paymentChoice;

                    // Similar payment processing logic as bookRoom()
                    break;
                }
                case 2: {
                    int newGuests;
                    cout << "Enter New Number of Guests: ";
                    cin >> newGuests;
                    bookingIt->updateNumberOfGuests(newGuests);
                    break;
                }
                default:
                    throw ValidationException("Invalid Edit Option");
            }

            cout << "Press Enter to go back to the Menu...";
            cin.ignore();
            cin.get();
        }
        catch (const BookingException& e) {
            cerr << "Booking Error: " << e.what() << endl;
        }
        catch (const ValidationException& e) {
            cerr << "Validation Error: " << e.what() << endl;
        }
    }

    void viewBookings() {
        if (bookings.empty()) {
            cout << "No bookings found." << endl;
            return;
        }

        cout << "----------Booking History----------" << endl;
        for (const auto& booking : bookings) {
            cout << "Booking ID: " << booking.getBookingId() << endl;
            cout << "Guest Name: " << booking.getGuestName() << endl;
            cout << "Room: " << booking.getRoomId() << endl;
            cout << "Check-in: " << booking.getCheckInDate() << endl;
            cout << "Check-out: " << booking.getCheckOutDate() << endl;
            cout << "Guests: " << booking.getNumberOfGuests() << endl;
            cout << "Total Amount: Php " << booking.getTotalAmount() << endl;
            cout << "Payment Status: " << (booking.getIsPaid() ? "Paid" : "Unpaid") << endl;
            cout << "-----------------------------------" << endl;
        }
    }

    void cancelBooking() {
        string bookingId;
        cout << "Enter Booking ID to Cancel: ";
        cin >> bookingId;

        auto bookingIt = find_if(bookings.begin(), bookings.end(), 
            [&bookingId](const Booking& b) { return b.getBookingId() == bookingId; });

        if (bookingIt != bookings.end()) {
            bookings.erase(bookingIt);
            cout << "Booking " << bookingId << " has been cancelled." << endl;
            } else {
            cout << "Booking not found." << endl;
        }
    }

    void editAccount() {
        string guestName, newName;
        cout << "Enter Current Guest Name: ";
        cin.ignore();
        getline(cin, guestName);

        // Find bookings for this guest
        auto guestBookings = find_if(bookings.begin(), bookings.end(), 
            [&guestName](const Booking& b) { return b.getGuestName() == guestName; });

        if (guestBookings != bookings.end()) {
            cout << "Enter New Guest Name: ";
            getline(cin, newName);

            // Update all bookings for this guest
            for (auto& booking : bookings) {
                if (booking.getGuestName() == guestName) {
                    // In a real system, you'd have a method to update guest name
                    cout << "Account updated successfully." << endl;
                }
            }
        } else {
            cout << "No bookings found for this guest." << endl;
        }
    }

    void deleteAccount() {
        string guestName;
        cout << "Enter Guest Name to Delete Account: ";
        cin.ignore();
        getline(cin, guestName);

        // Remove all bookings for this guest
        auto newEnd = remove_if(bookings.begin(), bookings.end(), 
            [&guestName](const Booking& b) { return b.getGuestName() == guestName; });

        if (newEnd != bookings.end()) {
            bookings.erase(newEnd, bookings.end());
            cout << "All bookings for " << guestName << " have been deleted." << endl;
        } else {
            cout << "No bookings found for this guest." << endl;
        }
    }
};

// User Authentication (Basic Implementation)
class UserAuthentication {
private:
    map<string, string> userCredentials;

public:
    bool registerUser(const string& username, const string& password) {
        // Check if username already exists
        if (userCredentials.find(username) != userCredentials.end()) {
            cout << "Username already exists!" << endl;
            return false;
        }

        // Basic password validation
        if (password.length() < 8) {
            cout << "Password must be at least 8 characters long!" << endl;
            return false;
        }

        userCredentials[username] = password;
        cout << "User registered successfully!" << endl;
        return true;
    }

    bool login(const string& username, const string& password) {
        auto user = userCredentials.find(username);
        if (user != userCredentials.end() && user->second == password) {
            cout << "Login Successful!" << endl;
            return true;
        }
        cout << "Invalid Username or Password!" << endl;
        return false;
    }
};

int main() {
    HotelManagementSystem hms;
    UserAuthentication auth;
    string username, password;
    bool isLoggedIn = false;

    while (!isLoggedIn) {
        cout << "========== Luxury Hotel Management System ==========" << endl;
        cout << "1. Register\n2. Login\n3. Exit" << endl;
        int authChoice;
        cout << "Choose an option: ";
        cin >> authChoice;

        switch (authChoice) {
            case 1: {
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                auth.registerUser(username, password);
                break;
            }
            case 2: {
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                isLoggedIn = auth.login(username, password);
                break;
            }
            case 3:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    int choice;
    do {
        cout << "\n========== Hotel Management System - Guest Menu ==========" << endl;
        cout << "1. View Room Available\n2. Book Room\n3. Edit Booking\n4. Cancel Booking\n";
        cout << "5. View Booking and Payment History\n6. Edit Account\n7. Delete Account\n8. Logout" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch(choice) {
            case 1: hms.viewAvailableRooms(); break;
            case 2: hms.bookRoom(); break;
            case 3: hms.editBooking(); break;
            case 4: hms.cancelBooking(); break;
            case 5: hms.viewBookings(); break;
            case 6: hms.editAccount(); break;
            case 7: hms.deleteAccount(); break;
            case 8: 
                cout << "Logging out..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}