#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct User{
  string email, name, password, roomType;
  int roomNumber;
  bool isAvailable;
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
  

  bool found = false;
  for (const auto& user : users){
    if (user.email == email){
      cout << "\n--- User Details ---\n";
      cout << "Name: " << user.name << "\n";
      cout << "Email: " << user.email << "\n";
      found = true;
      break;
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
      cin.ignore();
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

void deleteUser() {
  string email;
  cout << "Enter email of the user to delete: ";
  cin >> email;

  for (auto it = users.begin(); it != users.end(); ++it){
    if(it->email == email){
      users.erase(it);
      cout << "User account deleted successfully!\n";
      return;
    }
  }
  cout << "User not found.\n";
}


  void addRoom() {
    Room newRoom;

    cout << "Enter Room Number: ";
    cin >> newRoom.roomNumber;

    for(const auto& room : rooms){
      if(room.roomNumber == newRoom.roomNumber){
        cout << "Room with this number already exist.\n";
        return;
      }
    }
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

 

