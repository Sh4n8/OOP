#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

//Class User
class User {
  protected: 
    string name, email, password;

  //Constructor
  public:
    User(string name, string email, string password) : name(name), email(email), password(password) {}

    //Getters
    string getName() const{
      return name;
    }

    string getEmail() const{
      return email;
    }
    
    //Setters
    void setName(string name) {
      this -> name = name;
    }

    void setEmail(string email) {
      this -> email = email;
    }
};

class Customer : public User {
  private:
    vector<Booking> bookingHistory;
    
}

//Class Room
class Room {
  private:
    int roomNo;
    string roomType;
    double price;
    bool isAvailable;

  public:
    // constructor
    Room(int roomNo, string roomType, double price) : roomNo(roomNo), roomType(roomType), price(price), isAvailable(true) {}

    //getter
    int getRoomNo() {
      return roomNo;
    }

    string getRoomType() {
      return roomType;
    }

    double getRoomPrice() {
      return price;
    }

    bool roomIsAvailable() {
      return isAvailable;
    }

    //setter
    void setRoomNo(int roomNo) {
      this -> roomNo = roomNo;
    }

    void setRoomType(string roomType) {
      this -> roomType = roomType;
    }

    void setRoomPrice(double roomPrice) {
      this -> price = roomPrice;
    }

    void setIsAvailable(bool isAvailable) {
      this -> isAvailable = isAvailable;
    }
};

class ParkInnLodge {
  private:
    vector(User) users;
    vector(Room) rooms;

  public:
    // construct objects
    void createAccount(string name, string email, string password) : User(name, email, password) {}
    void addRoom(int roomNo, string roomType, double price) : Room(roomNo, roomType, price) {}



    virtual void viewBookingHistory () const {
      cout << "View Booking History: " << endl; 
      cout >> book >> endl;
     
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

class HotelBookingSystem {
private:
    vector<Booking> bookings;
    const double ROOM_PRICE_PER_NIGHT = 1500.0; 

public:
    void displayMainMenu() {
        cout << "----------[Hotel Name] Room Booking Menu----------" << endl;
        cout << "1. New Booking" << endl;
        cout << "2. Edit Booking" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
    }

    void newBooking() {
        int roomId, numberOfGuests;
        string checkInDate, checkOutDate, paymentMethod;

        cout << "Enter the Room ID you want to book: ";
        cin >> roomId;

        cout << "Enter Check-in Date (YYYY-MM-DD): ";
        cin >> checkInDate;

        cout << "Enter Check-out Date (YYYY-MM-DD): ";
        cin >> checkOutDate;

        cout << "Enter the Number of Guests: ";
        cin >> numberOfGuests;

        cout << "Choose Payment Method:" << endl;
        cout << "1. Cash" << endl;
        cout << "2. Digital Wallet" << endl;
        cout << "3. Credit/Debit Card" << endl;
        cout << "Enter your choice: ";
        cin >> paymentMethod;

        string paymentMethodStr;
        switch (stoi(paymentMethod)) {
            case 1: paymentMethodStr = "Cash"; break;
            case 2: paymentMethodStr = "Digital Wallet"; break;
            case 3: paymentMethodStr = "Credit/Debit Card"; break;
            default: paymentMethodStr = "Unknown"; break;
        }

        double totalPrice = calculateTotalPrice(checkInDate, checkOutDate, numberOfGuests);

        Booking newBooking({roomId}, totalPrice, checkInDate, checkOutDate, numberOfGuests, paymentMethodStr);
        bookings.push_back(newBooking);

        cout << "Booking Successful!" << endl;
        displayBookingDetails(newBooking);
    }

    void editBooking() {
        int bookingIndex;
        cout << "Enter Your Booking ID: ";
        cin >> bookingIndex;

        if (bookingIndex < 0 || bookingIndex >= bookings.size()) {
            cout << "Invalid Booking ID." << endl;
            return;
        }

        Booking& currentBooking = bookings[bookingIndex];
        displayBookingDetails(currentBooking);

        cout << "What would you like to edit?" << endl;
        cout << "1. Change Dates" << endl;
        cout << "2. Change Room" << endl;
        cout << "3. Change Number of Guests" << endl;
        cout << "Choose an option: ";

        int editChoice;
        cin >> editChoice;

        switch (editChoice) {
            case 1: editBookingDates(currentBooking); break;
            case 2: editBookingRoom(currentBooking); break;
            case 3: editBookingGuests(currentBooking); break;
            default: cout << "Invalid option." << endl;
        }
    }

private:
    double calculateTotalPrice(string fromDate, string toDate, int guests) {
        int nights = 1;
        return ROOM_PRICE_PER_NIGHT * nights * guests;
    }

    void displayBookingDetails(const Booking& booking) {
        cout << "----------Booking Details----------" << endl;
        cout << "Room: " << booking.getRooms()[0] << endl;
        cout << "Check-in: " << booking.getFromDate() << endl;
        cout << "Check-out: " << booking.getToDate() << endl;
        cout << "Guests: " << booking.getNumberOfGuests() << endl;
        cout << "Payment Method: " << booking.getPaymentMethod() << endl;
        cout << "Total Amount: Php " << fixed << setprecision(2) << booking.getTotalPrice() << endl;
    }

    void editBookingDates(Booking& booking) {
        string newCheckInDate, newCheckOutDate;
        cout << "Enter New Check-in Date (YYYY-MM-DD): ";
        cin >> newCheckInDate;
        cout << "Enter New Check-out Date (YYYY-MM-DD): ";
        cin >> newCheckOutDate;

        booking.updateDates(newCheckInDate, newCheckOutDate);
        double newTotalPrice = calculateTotalPrice(newCheckInDate, newCheckOutDate, booking.getNumberOfGuests());

        cout << "----------Updating Booking----------" << endl;
        displayBookingDetails(booking);
        
        cout << "Balance Due: Php " << fixed << setprecision(2) << newTotalPrice << endl;
        
        cout << "Choose Payment Method to Settle Balance:" << endl;
        cout << "1. Cash" << endl;
        cout << "2. Digital Wallet" << endl;
        cout << "3. Credit/Debit Card" << endl;
        cout << "Enter your choice: ";
    }

    void editBookingRoom(Booking& booking) {
        int newRoomId;
        cout << "Enter New Room ID: ";
        cin >> newRoomId;
        booking.updateRoom({newRoomId});
    }

    void editBookingGuests(Booking& booking) {
        int newNumberOfGuests;
        cout << "Enter New Number of Guests: ";
        cin >> newNumberOfGuests;
        booking.updateGuests(newNumberOfGuests);
    }

public:
    void run() {
        int choice;
        do {
            displayMainMenu();
            cin >> choice;

            switch (choice) {
                case 1: newBooking(); break;
                case 2: editBooking(); break;
                case 3: cout << "Exiting..." << endl; break;
                default: cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != 3);
    }
};

int main() {
    HotelBookingSystem hotelSystem;
    hotelSystem.run();
    return 0;
}