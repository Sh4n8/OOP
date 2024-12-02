#include <iostream>
#include <vector>
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

// Function to display all available rooms
void displayAvailableRooms(const vector<Room *> &rooms) {
    cout << "----------Park Inn Lodge Available Rooms----------\n" << endl;
    for (const auto &room : rooms) {
        room->displayRoomInfo();
    }
}

int main() {
    vector<Room *> rooms;

    // Adding rooms to the list
    StandardRoom *standard = new StandardRoom();
    standard->setRoomNo("RM102");
    standard->setRoomType("Standard Room");
    standard->setRoomPrice(2000);
    rooms.push_back(standard);

    DeluxeRoom *deluxe = new DeluxeRoom();
    deluxe->setRoomNo("RM101");
    deluxe->setRoomType("Deluxe Room");
    deluxe->setRoomPrice(6000);
    deluxe->setExtraBedAvailable(true);
    rooms.push_back(deluxe);

    SuiteRoom *suite = new SuiteRoom();
    suite->setRoomNo("RM201");
    suite->setRoomType("Suite Room");
    suite->setRoomPrice(10000);
    suite->setNoOfBedrooms(3);
    rooms.push_back(suite);

    // Display rooms
    displayAvailableRooms(rooms);

    // Clean up memory
    for (auto room : rooms) {
        delete room;
    }

    return 0;
}
