#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PaymentMethod {
public:
    virtual void processPayment(double amount) = 0;
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

    void processPayment(double amount) override {
       
        cout << "Processing " << (isCredit ? "credit" : "debit") << " card payment of Php" << amount << endl;
    }

    string getType() const override {
        return "Card";
    }
};

class GCash : public PaymentMethod {
private:
    string number;

public:
    GCash(const string& number) : number(number) {}

    void processPayment(double amount) override {
        
        cout << "Processing GCash payment of Php" << amount << endl;
    }

    string getType() const override {
        return "GCash";
    }
};

int main() {
    vector<PaymentMethod*> paymentMethods = {
        new Card("1234567890", "12/24", "1234", true),
        new GCash("09123456789")
    };

    double amount = 100.00;
    int choice;

    cout << "Available Payment Methods:\n";
    for (size_t i = 0; i < paymentMethods.size(); i++) {
        cout << i + 1 << ". " << paymentMethods[i]->getType() << endl;
    }

    cout << "Enter your choice (1-" << paymentMethods.size() << "): ";
    cin >> choice;

    if (choice >= 1 && choice <= static_cast<int>(paymentMethods.size())) {
        paymentMethods[choice - 1]->processPayment(amount);
    } else {
        cout << "Invalid choice." << endl;
    }

    for (auto paymentMethod : paymentMethods) {
        delete paymentMethod;
    }

    return 0;
}