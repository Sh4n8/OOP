#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Room {
protected:
    string roomNo;
    string roomType;
    double price;
    bool isAvailable;

public:
    Room() : roomNo(""), roomType(""), price(0.0), isAvailable(true) {}

    // Getters
    string getRoomNo() const { return roomNo; }
    string getRoomType() const { return roomType; }
    double getRoomPrice() const { return price; }
    bool getRoomAvailability() const { return isAvailable; }

    // Setters
    void setRoomNo(const string &no) { roomNo = no; }
    void setRoomType(const string &type) { roomType = type; }
    void setRoomPrice(double p) { price = p; }
    void setRoomAvailability(bool available) { isAvailable = available; }

    // Display room details
    virtual void displayRoomInfo() const {
        cout << "[ID: " << roomNo << "] " << roomType << "\n"
             << "- Price: Php " << price << "/night\n"
             << "- Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
    }

    virtual ~Room() {}
};

// Standard Room Class
class StandardRoom : public Room {
    string bedSize;

public:
    StandardRoom() : bedSize("Double") {}

    // Getters and Setters
    string getBedSize() const { return bedSize; }
    void setBedSize(const string &size) { bedSize = size; }

    // Display details
    void displayRoomInfo() const override {
        Room::displayRoomInfo();
        cout << "- Bed Size: " << bedSize << "\n" << endl;
    }
};

// Deluxe Room Class
class DeluxeRoom : public Room {
    string bedSize;
    bool extraBedAvailable;

public:
    DeluxeRoom() : bedSize("Queen"), extraBedAvailable(false) {}

    // Getters and Setters
    string getBedSize() const { return bedSize; }
    void setBedSize(const string &size) { bedSize = size; }

    bool getExtraBedAvailable() const { return extraBedAvailable; }
    void setExtraBedAvailable(bool available) { extraBedAvailable = available; }

    // Display details
    void displayRoomInfo() const override {
        Room::displayRoomInfo();
        cout << "- Bed Size: " << bedSize << "\n"
             << "- Extra Bed Available: " << (extraBedAvailable ? "Yes" : "No") << "\n" << endl;
    }
};

// Suite Room Class
class SuiteRoom : public Room {
    bool hasLivingRoom;
    bool hasKitchen;
    int noOfBedrooms;

public:
    SuiteRoom() : hasLivingRoom(true), hasKitchen(true), noOfBedrooms(2) {}

    // Getters and Setters
    bool getLivingRoom() const { return hasLivingRoom; }
    void setLivingRoom(bool livingRoom) { hasLivingRoom = livingRoom; }

    bool getKitchen() const { return hasKitchen; }
    void setKitchen(bool kitchen) { hasKitchen = kitchen; }

    int getNoOfBedrooms() const { return noOfBedrooms; }
    void setNoOfBedrooms(int bedrooms) { noOfBedrooms = bedrooms; }

    // Display details
    void displayRoomInfo() const override {
        Room::displayRoomInfo();
        cout << "- Living Room: " << (hasLivingRoom ? "Yes" : "No") << "\n"
             << "- Kitchen: " << (hasKitchen ? "Yes" : "No") << "\n"
             << "- No. of Bedrooms: " << noOfBedrooms << "\n" << endl;
    }
};

class Booking {
private:
    vector<int> rooms;  
    double totalPrice;
    string fromDate;
    string toDate;
    int numberOfGuests;
    string paymentMethod;

public:
    Booking(vector<int> rooms, double totalPrice, string fromDate, string toDate, int guests, string payment) 
        : rooms(rooms), totalPrice(totalPrice), fromDate(fromDate), toDate(toDate), 
          numberOfGuests(guests), paymentMethod(payment) {}

    vector<int> getRooms() const {
        return rooms;
    }

    double getTotalPrice() const {
        return totalPrice;
    }

    string getFromDate() const {
        return fromDate;
    }

    string getToDate() const {
        return toDate;
    }

    int getNumberOfGuests() const {
        return numberOfGuests;
    }

    string getPaymentMethod() const {
        return paymentMethod;
    }

    void updateDates(string newFromDate, string newToDate) {
        fromDate = newFromDate;
        toDate = newToDate;
    }

    void updateRoom(vector<int> newRooms) {
        rooms = newRooms;
    }

    void updateGuests(int newNumberOfGuests) {
        numberOfGuests = newNumberOfGuests;
    }
};

// Base class: User
class User {
protected:
    string name, email, password, role;

public:
    User(string n, string e, string p, string r) : name(n), email(e), password(p), role(r) {}
    string getName() { return name; }
    string getEmail() { return email; }
    string getPassword() { return password; }
    string getRole() { return role; }
    
    virtual void createAccount() {
        cout << "User account created for: " << name << endl;
    }
    virtual void deleteAccount() {
        cout << "User account deleted for: " << name << endl;
    }
    
    static User* login(vector<User*>& users, string email, string password) {
        for (auto& user : users) {
            if (user->getEmail() == email && user->getPassword() == password) {
                cout << "Login successful! Welcome, " << user->getName() << endl;
                return user;
            }
        }
        cout << "Invalid email or password.\n";
        return nullptr;
    }
};
// Derived class: Customer
class Customer : public User {
    vector<string> bookingHistory;
    vector<int> currentBookings;

public:
    Customer(string n, string e, string p)
        : User(n, e, p, "Customer") {}

    void createAccount() override {
        cout << "Customer account created for: " << name << endl;
    }

    void bookRoom(int roomNo) {
        currentBookings.push_back(roomNo);
        bookingHistory.push_back("Booked room " + to_string(roomNo));
        cout << "Room " << roomNo << " booked successfully!\n";
    }

    void cancelBooking(int roomNo) {
        for (auto it = currentBookings.begin(); it != currentBookings.end(); ++it) {
            if (*it == roomNo) {
                currentBookings.erase(it);
                bookingHistory.push_back("Canceled room " + to_string(roomNo));
                cout << "Room " << roomNo << " canceled successfully!\n";
                return;
            }
        }
        cout << "Booking not found for room " << roomNo << ".\n";
    }

    void viewBookingHistory() {
        cout << "Booking History for " << name << ":\n";
        for (const string &history : bookingHistory) {
            cout << "- " << history << endl;
        }
    }
};

// Derived class: Employee
class Employee : public User {
public:
    Employee(string n, string e, string p)
        : User(n, e, p, "Employee") {}

    void addRoom(vector<Room *> &rooms, Room *room) {
        rooms.push_back(room);
        cout << "Room " << room->getRoomNo() << " added successfully!\n";
    }

    void deleteRoom(vector<Room *> &rooms, const string &roomNo) {
        for (auto it = rooms.begin(); it != rooms.end(); ++it) {
            if ((*it)->getRoomNo() == roomNo) {
                delete *it; // Free memory
                rooms.erase(it);
                cout << "Room " << roomNo << " deleted successfully!\n";
                return;
            }
        }
        cout << "Room " << roomNo << " not found.\n";
    }

    void viewCheckInOut() {
        cout << "Viewing all check-ins and check-outs (placeholder).\n";
    }

    void viewAnalytics() {
        cout << "Viewing analytics (placeholder).\n";
    }
};

// ParkInnLodge class
class ParkInnLodge {
    vector<User *> users;
    vector<Room *> rooms;

public:
    void createAccount(User *user) {
        users.push_back(user);
        user->createAccount();
    }

    void addRoom(Room *room) {
        rooms.push_back(room);
        cout << "Room added: " << room->getRoomNo() << endl;
    }

    void viewAvailableRooms() {
        cout << "\nAvailable Rooms:\n";
        for (auto &room : rooms) {
            if (room->getRoomAvailability()) {
                cout << "- Room " << room->getRoomNo() << " (" << room->getRoomType()
                     << ") - P" << room->getRoomPrice() << endl;
            }
        }
    }

    vector<Room *> &getRooms() { return rooms; }

    vector<User *> &getUsers() { return users; }
};

// Display menu for customers
void displayCustomerMenu(Customer *customer, ParkInnLodge *lodge) {
    int choice;
    do {
        cout << "\n--- Customer Menu ---\n";
        cout << "1. Book Room\n";
        cout << "2. Cancel Booking\n";
        cout << "3. View Booking History\n";
        cout << "4. View Available Rooms\n";
        cout << "5. Sign-out\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string roomNo;
            cout << "Enter room number to book: ";
            cin >> roomNo;

            // Check if the room exists and if it is available
            bool roomFound = false;
            bool roomAvailable = false;
            for (Room *room : lodge->getRooms()) {
                if (room->getRoomNo() == roomNo) {
                    roomFound = true;
                    if (room->getRoomAvailability()) {
                        roomAvailable = true;
                    }
                    break;
                }
            }

            if (!roomFound) {
                cout << "Room number " << roomNo << " does not exist.\n";
            } else if (!roomAvailable) {
                cout << "Room number " << roomNo << " is already booked.\n";
            } else {
                customer->bookRoom(stoi(roomNo));
            }
            break;
        }

        case 2: {
            int roomNo;
            cout << "Enter room number to cancel: ";
            cin >> roomNo;
            customer->cancelBooking(roomNo);
            break;
        }
        case 3:
            customer->viewBookingHistory();
            break;
        case 4:
            lodge->viewAvailableRooms();
            break;
        case 5:
            cout << "Signing out...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

// Display menu for employees
void displayEmployeeMenu(Employee *employee, ParkInnLodge *lodge) {
    int choice;
    do {
        cout << "\n--- Employee Menu ---\n";
        cout << "1. Add Room\n";
        cout << "2. Delete Room\n";
        cout << "3. View Available Rooms\n";
        cout << "4. View Check-Ins and Check-Outs\n";
        cout << "5. View Analytics\n";
        cout << "6. Sign-out\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string roomNo;
            double price;
            cout << "Enter room number: ";
            cin >> roomNo;
            cout << "Enter room price: ";
            cin >> price;

            Room *room = new StandardRoom();
            room->setRoomNo(roomNo);
            room->setRoomPrice(price);
            room->setRoomType("Standard");
            employee->addRoom(lodge->getRooms(), room);
            break;
        }

        case 2: {
            string roomNo;
            cout << "Enter room number to delete: ";
            cin >> roomNo;
            employee->deleteRoom(lodge->getRooms(), roomNo);
            break;
        }

        case 3:
            lodge->viewAvailableRooms();
            break;

        case 4:
            employee->viewCheckInOut();
            break;

        case 5:
            employee->viewAnalytics();
            break;

        case 6:
            cout << "Signing out...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}



void displayMainMenu(ParkInnLodge &parkInn) {
    bool isRunning = true;

    while (isRunning) {
        cout << "\n--- PARK INN LODGE ---" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: { // Create Account
            cout << "\n--- Create Account ---" << endl;
            cout << "Are you a:\n1. Customer\n2. Employee\nEnter your choice: ";
            int accountType;
            cin >> accountType;

            if (accountType == 1 || accountType == 2) {
                string name, email, password;
                cout << "Enter your name: ";
                cin.ignore(); // To handle the leftover newline character
                getline(cin, name);

                cout << "Enter your email: ";
                cin >> email;

                cout << "Create a password: ";
                cin >> password;

                if (accountType == 1) {
                    Customer *newCustomer = new Customer(name, email, password);
                    parkInn.createAccount(newCustomer);
                } else if (accountType == 2) {
                    Employee *newEmployee = new Employee(name, email, password);
                    parkInn.createAccount(newEmployee);
                }
            } else {
                cout << "Invalid account type selected.\n";
            }
            break;
        }

        case 2: { // Login
            cout << "\n--- Login ---" << endl;
            string email, password;
            cout << "Enter your email: ";
            cin >> email;

            cout << "Enter your password: ";
            cin >> password;

            User *loggedInUser = User::login(parkInn.getUsers(), email, password);

            if (loggedInUser != nullptr) {
                if (loggedInUser->getRole() == "Customer") {
                    displayCustomerMenu(dynamic_cast<Customer *>(loggedInUser), &parkInn);
                } else if (loggedInUser->getRole() == "Employee") {
                    displayEmployeeMenu(dynamic_cast<Employee *>(loggedInUser), &parkInn);
                }
            }
            break;
        }

        case 3: // Exit
            cout << "Thank you for using Park Inn Lodge. Goodbye!" << endl;
            isRunning = false;
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

class PaymentMethod {
public:
    virtual bool processPayment(double amount) = 0;
    virtual string getType() const = 0;
    virtual ~PaymentMethod() {}
};

class Card : public PaymentMethod {
private:
    string number;
    string expiration;
    string pin;
    bool isCredit;

public:
    Card(const string& number, const string& expiration, const string& pin, bool isCredit)
        : number(number), expiration(expiration), pin(pin), isCredit(isCredit) {}

    bool processPayment(double amount) override {
        // Simple validation
        if (number.empty() || expiration.empty() || pin.empty()) {
            cout << "Invalid card details. Payment failed.\n";
            return false;
        }

        // Simulate PIN verification
        string inputPin;
        cout << "Enter " << (isCredit ? "Credit" : "Debit") << " Card PIN: ";
        cin >> inputPin;

        if (inputPin != pin) {
            cout << "Incorrect PIN. Payment declined.\n";
            return false;
        }

        // Simulate payment processing
        cout << "Processing " << (isCredit ? "credit" : "debit") 
             << " card payment of Php " << amount << endl;
        
        // Simulate transaction confirmation
        char confirm;
        cout << "Confirm payment? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            cout << "Payment successful!\n";
            return true;
        } else {
            cout << "Payment cancelled.\n";
            return false;
        }
    }

    string getType() const override {
        return isCredit ? "Credit Card" : "Debit Card";
    }
};

class GCash : public PaymentMethod {
private:
    string number;
    double balance;

public:
    GCash(const string& number, double initialBalance = 10000.0) 
        : number(number), balance(initialBalance) {}

    bool processPayment(double amount) override {
        // Validate phone number
        if (number.empty() || number.length() != 11) {
            cout << "Invalid GCash number. Payment failed.\n";
            return false;
        }

        // Check balance
        if (amount > balance) {
            cout << "Insufficient balance. Payment failed.\n";
            return false;
        }

        // Simulate OTP verification
        string otp;
        cout << "Enter GCash OTP: ";
        cin >> otp;

        // Simple OTP validation (just for demonstration)
        if (otp != "123456") {
            cout << "Incorrect OTP. Payment declined.\n";
            return false;
        }

        // Process payment
        balance -= amount;
        cout << "Processing GCash payment of Php" << amount << endl;
        
        // Confirm transaction
        char confirm;
        cout << "Confirm payment? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            cout << "Payment successful!\n";
            cout << "Remaining balance: Php" << balance << endl;
            return true;
        } else {
            // Refund the amount if cancelled
            balance += amount;
            cout << "Payment cancelled.\n";
            return false;
        }
    }

    string getType() const override {
        return "GCash";
    }

    // Getter for balance (optional, but useful)
    double getBalance() const {
        return balance;
    }
};


int main() {
    unique_ptr<PaymentMethod> paymentMethod;
    double amount;

    while (true) {
        // Start the main menu
        cout << "\n--- Welcome to the Payment Portal ---\n";
        cout << "Enter the amount to be paid: Php ";
        cin >> amount;

        cout << "\nChoose a payment method:\n";
        cout << "1. Credit Card\n";
        cout << "2. Debit Card\n";
        cout << "3. GCash\n";
        cout << "4. Exit\n"; 
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string cardNumber, expirationDate, pin;
                cout << "\nEnter Credit Card details:\n";
                cout << "Card Number: ";
                cin >> cardNumber;
                cout << "Expiration Date (MM/YY): ";
                cin >> expirationDate;
                cout << "PIN: ";
                cin >> pin;

                paymentMethod = make_unique<Card>(cardNumber, expirationDate, pin, true);
                break;
            }

            case 2: {
                string cardNumber, expirationDate, pin;
                cout << "\nEnter Debit Card details:\n";
                cout << "Card Number: ";
                cin >> cardNumber;
                cout << "Expiration Date (MM/YY): ";
                cin >> expirationDate;
                cout << "PIN: ";
                cin >> pin;

                paymentMethod = make_unique<Card>(cardNumber, expirationDate, pin, false, 5000.0); 
                break;
            }

            case 3: {
                string phoneNumber;
                cout << "\nEnter GCash details:\n";
                cout << "Phone Number: ";
                cin >> phoneNumber;

                paymentMethod = make_unique<GCash>(phoneNumber);
                break;
            }

            case 4:
                cout << "Thank you for using the payment portal. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
                continue;
        }

        // Process payment
        if (paymentMethod && paymentMethod->processPayment(amount)) {
            cout << "Payment processed successfully using " << paymentMethod->getType() << ".\n";
        } else {
            cout << "Payment failed. Please try again.\n";
        }

        
        char restart;
        cout << "\nDo you want to process another payment? (Y/N): ";
        cin >> restart;

        if (restart != 'Y' && restart != 'y') {
            cout << "Thank you for using the payment portal. Goodbye!\n";
            break;
        }
    }

    return 0;
}

    


//ParkInnLodge parkInn;

    // Add users
    //Customer *customer1 = new Customer("John Doe", "john@example.com", "password123");
    //Employee *employee1 = new Employee("Alice Smith", "alice@example.com", "password123");
    //parkInn.createAccount(customer1);
   // parkInn.createAccount(employee1);

    //bool isRunning = true;

    //while (isRunning) {
        //cout << "PARKINNLODGE LOGIN PORTAL (Type 1 to exit.)" << endl;
        //string email, password;
        //cout << "Enter email: ";
        //cin >> email;
        //if (email == "1") {
            //cout << "Exiting program..." << endl;
            //break;
       // }
        //cout << "Enter password: ";
        //cin >> password;

        //User *loggedInUser = User::login(parkInn.getUsers(), email, password);

        //if (loggedInUser != nullptr) {
            //if (loggedInUser->getRole() == "Customer") {
                //displayCustomerMenu(dynamic_cast<Customer *>(loggedInUser), &parkInn);
           // } else if (loggedInUser->getRole() == "Employee") {
               // displayEmployeeMenu(dynamic_cast<Employee *>(loggedInUser), &parkInn);
           // }
        //}
    //}

    //return 0;