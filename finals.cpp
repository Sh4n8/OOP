#include <iostream>
#include <string>
#include <vector>
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
    Room(int no, string type, double price, bool availability) : roomNo(no), roomType(type), price(price), isAvailable(availability) {}

    //getter
    int getRoomNo() const {
      return roomNo;
    }

    string getRoomType() const {
      return roomType;
    }

    double getRoomPrice() const {
      return price;
    }

    bool getRoomAvailability() const {
      return isAvailable;
    }

    //setter
    void setRoomNo(int no) {
      this -> roomNo = no;
    }

    void setRoomType(string type) {
      this -> roomType = type;
    }

    void setRoomPrice(double newPrice) {
      this -> price = newPrice;
    }

    void setRoomAvailability(bool availability) {
      this -> isAvailable = availability;
    }
};

void displayRooms(const vector<Room>& rooms) {
  cout << "\nAvailable Rooms: \n";
  for (const auto& room : rooms) {
    cout  << "Room No: " << room.getRoomNo() << "\n"
          << "Type: " << room.getRoomType() << "\n"
          << "Price: Php" << room.getRoomPrice() << "\n"
          << "Available: " << (room.getRoomAvailability() ? "Yes" : "No") << "\n\n";
    }
}

class ParkInnLodge {
  private:
    vector(User) users;
    vector(Room) rooms;

  public:
    // construct objects
    void createAccount(string name, string email, string password) : User(name, email, password) {}
    void addRoom(int roomNo, string roomType, double price) : Room(roomNo, roomType, price) {}



    virtual void viewBookingHistory () const {
      cout << "View Booking History: " << 
    }
};