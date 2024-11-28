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
      cout << "View Booking History: " << 
    }
    
};


//class Employee
class Employee{
  private:
  vector<User> users;

  public:
  Employee() {}

  void manageUserAccount(){
    int choice;

    do {
      cout << "\n--- User Account Management ---\n";
      cout << "1. Register New User\n";
      cout << "2. View User Account Information\n";
      cout << "3. Update User Details\n";
      cout << "4. Delete User Account\n";
      cout << "5. Exit\n";
      cout << "Enter your choice: ";
      cin >> choice;
      
      switch(choice){
        case 1:
          registerUser();
          break;
        case 2:
          viewUser();
          break;
        case 3:
          updateUser();
          break;
        case 4: 
          deleteUser();
          break;
        case 5:
          cout << "Exiting User Account Management...\n";
          break;
        default:
          cout << "Invalid choice. Please try again.\n";
      }
    } while (choice != 5);
  }

  private:

  void registerUser(){
    User newUser;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, newUser.name);
    cout << "Enter Email: ";
    cin >> newUser.email;
    cout << "Enter Password: ";
    cin >> newUser.password;
    users.push_back(newUser);
    cout << "User registered successfully!\n";
  }

  void viewUser(){
    string email;
    cout<< "Enter email of the user to view: ";
    cin >> email;
  }

  bool found = false;
  for (const auto& user : users){
    if (user.email == email){
      cout << "\n--- User Details ---\n";
      cout << "Name: " << user.name << "\n";
      cout << "Email: " << user.email << "\n";
      found = truebreak;
    }
  }

  if(!found){
    cout << "User not found.\n";
  }
}

void updateUser(){
  string email;
  cout << "Enter email of the user to update: ";
  cin >> email;

  bool found = false;
  for (auto&user : users){
    if (user.email == email){
      cout << "Enter new name: ";
      cin.ignore;
      getline(cin, user.name);
      cout << "Enter new password: ";
      cin >> user.password;
      cout << "User details updated successfully!\n";
      found = true;
      break;
    }
  }

  if(!found){
    cout << "User not found.\n";
  }
}

  void addRoom() {

  }

  void issueRefund(){

  }

  void viewAnalytics(){

  }

  void checkIn(){

  }

  void checkOut(){

  }

  void viewCheckInOut(){

  }

  void manageRoomInc(){

  }

  void editRoom(){

  }

  void addRoom(){

  }

  };

  class Booking{
    private:
      vector<Room>;
      double totalPrice;
      string fromDate;
      string toDate;

      //Constructor
      //missing vector room
      Booking(double totalPrice, string fromDate, string toDate) : totalPrice(totalPrice), fromDate(fromDate), toDate(toDate){}

      //Getters

      //missing getRooms
      double getTotalPrice() const{
        return totalPrice;
      } 

      string getFromDate() const{
        return fromDate;
      }

      string getToDate() const{
        return toDate;
      }
  };

