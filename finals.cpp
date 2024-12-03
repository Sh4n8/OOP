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
        // Implement credit/debit card payment processing logic here
        cout << "Processing " << (isCredit ? "credit" : "debit") << " card payment of $" << amount << endl;
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
        // Implement GCash payment processing logic here
        cout << "Processing GCash payment of $" << amount << endl;
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

    for (const auto& paymentMethod : paymentMethods) {
        paymentMethod->processPayment(100.00);
        cout << "Payment Method Type: " << paymentMethod->getType() << endl;
    }

    for (auto paymentMethod : paymentMethods) {
        delete paymentMethod;
    }

    return 0;
}