#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class PaymentMethod {
protected:
string method;

public:
  PaymentMethod (string method = "") : method(method){}

  string getMethod() const{
    return method;
  }

  virtual void displayDetails() const{
    cout << "Payment Method: " << method << endl;
  }

  virtual ~PaymentMethod() {}
};

class Card : public PaymentMethod {
private:
  string number;
  string expiration;
  string pin;
  bool isCredit;

public:
  Card(string method, string number, string pin, string expiration, bool isCredit) :
  PaymentMethod(method), number(number), expiration(expiration), pin(pin), isCredit(isCredit) {}

  bool getIsCredit() const {
    return isCredit;
  }

  void deleteCard(){
    number.clear();
    expiration.clear();
    pin.clear();
    cout << "Card details have been deleted.\n";
  }

  void displayDetails() const override {
    PaymentMethod :: displayDetails();
    cout << "Card Number: " << number << "\n";
    cout << "Expiration: " << expiration << "\n";
    cout << "Is Credit: " << (isCredit ? "Yes" : "No") << endl;
  }

};

class Gcash : public PaymentMethod {
  private:
  string number;

  public:
    Gcash(string method, string number) : PaymentMethod(method), number(number) {}

    string getNumber() const {
      return number;
    }

    void setNumber (string newNumber) {
    number = newNumber;
    }

    void displayDetails() const override {
      PaymentMethod :: displayDetails();
      cout << "Gcash Number: " << number << endl;
    }
};
