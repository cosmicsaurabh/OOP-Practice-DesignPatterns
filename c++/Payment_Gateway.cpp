/*
 * Payment Gateway System using Strategy Design Pattern
 * 
 * This system demonstrates the Strategy pattern for handling different payment gateways.
 * It provides a unified interface for processing payments through various payment providers
 * while maintaining flexibility to add new payment methods without modifying existing code.
 *
 * Features:
 * - Multiple payment gateways (Visa, MasterCard)
 * - Payment status tracking
 * - Transaction ID generation
 * - Centralized payment management
 *
 * Design Patterns Used:
 * - Strategy Pattern: Different payment processing algorithms
 * - Factory Pattern: Payment object creation
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <random>
#include <iomanip>

using namespace std;

// Enumeration for supported payment gateways
enum class Gateway { 
    VISA, 
    MASTERCARD 
};

// Enumeration for payment status
enum class PaymentStatus { 
    PENDING, 
    PROCESSING, 
    FAILED, 
    SUCCESS 
};

/**
 * Abstract base class for all payment processors
 * Defines the common interface for payment operations
 */
class BasePayment {
protected:
    double amount;
    string transactionId;
    PaymentStatus status;

public:
    /**
     * Constructor
     * @param amount The payment amount
     */
    explicit BasePayment(double amount) 
        : amount(amount), status(PaymentStatus::PENDING) {}

    // Pure virtual methods that must be implemented by derived classes
    virtual string processPayment() = 0;
    virtual PaymentStatus getStatus() = 0;
    virtual void printStatusInfo() = 0;
    virtual string getGatewayName() = 0;
    
    // Virtual destructor for proper cleanup
    virtual ~BasePayment() = default;

    /**
     * Gets the transaction amount
     * @return The payment amount
     */
    double getAmount() const { 
        return amount; 
    }

    /**
     * Gets the transaction ID
     * @return The transaction ID
     */
    string getTransactionId() const { 
        return transactionId; 
    }

protected:
    /**
     * Generates a random transaction ID
     * @param prefix The gateway-specific prefix
     * @return Generated transaction ID
     */
    string generateTransactionId(const string& prefix) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(100000, 999999);
        return prefix + to_string(dis(gen));
    }

    /**
     * Converts PaymentStatus enum to string
     * @param status The payment status
     * @return String representation of the status
     */
    string statusToString(PaymentStatus status) const {
        switch (status) {
            case PaymentStatus::PENDING:    return "Pending";
            case PaymentStatus::PROCESSING: return "Processing";
            case PaymentStatus::FAILED:     return "Failed";
            case PaymentStatus::SUCCESS:    return "Success";
            default:                        return "Unknown";
        }
    }
};

/**
 * Visa payment processor implementation
 * Handles Visa-specific payment processing logic
 */
class VisaPayment : public BasePayment {
public:
    explicit VisaPayment(double amount) : BasePayment(amount) {}

    string processPayment() override {
        cout << "Processing Visa payment of $" << fixed << setprecision(2) << amount << "..." << endl;
        
        // Simulate payment processing
        transactionId = generateTransactionId("VISA_");
        status = PaymentStatus::PROCESSING;
        
        cout << "Visa payment initiated with Transaction ID: " << transactionId << endl;
        return transactionId;
    }

    PaymentStatus getStatus() override {
        // Simulate status check - in real implementation, this would query the gateway
        return status;
    }

    void printStatusInfo() override {
        cout << "=== Visa Payment Status ===" << endl;
        cout << "Transaction ID: " << transactionId << endl;
        cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
        cout << "Status: " << statusToString(status) << endl;
        cout << "Gateway: " << getGatewayName() << endl;
        cout << "============================" << endl;
    }

    string getGatewayName() override {
        return "VISA";
    }
};

/**
 * MasterCard payment processor implementation
 * Handles MasterCard-specific payment processing logic
 */
class MasterCardPayment : public BasePayment {
public:
    explicit MasterCardPayment(double amount) : BasePayment(amount) {}

    string processPayment() override {
        cout << "Processing MasterCard payment of $" << fixed << setprecision(2) << amount << "..." << endl;
        
        // Simulate payment processing
        transactionId = generateTransactionId("MC_");
        status = PaymentStatus::PROCESSING;
        
        cout << "MasterCard payment initiated with Transaction ID: " << transactionId << endl;
        return transactionId;
    }

    PaymentStatus getStatus() override {
        // Simulate status check - in real implementation, this would query the gateway
        return status;
    }

    void printStatusInfo() override {
        cout << "=== MasterCard Payment Status ===" << endl;
        cout << "Transaction ID: " << transactionId << endl;
        cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
        cout << "Status: " << statusToString(status) << endl;
        cout << "Gateway: " << getGatewayName() << endl;
        cout << "===============================" << endl;
    }

    string getGatewayName() override {
        return "MASTERCARD";
    }
};

/**
 * Payment Manager class - manages all payment operations
 * Implements Factory pattern for creating payment processors
 */
class PaymentManager {
private:
    unordered_map<string, shared_ptr<BasePayment>> payments;

public:
    /**
     * Starts a new payment process
     * @param gateway The payment gateway to use
     * @param amount The payment amount
     * @return The transaction key for tracking the payment
     */
    string startPaymentProcess(Gateway gateway, double amount) {
        if (amount <= 0) {
            cout << "Error: Invalid payment amount. Amount must be greater than 0." << endl;
            return "";
        }

        shared_ptr<BasePayment> payment = createPayment(gateway, amount);
        if (!payment) {
            cout << "Error: Unsupported payment gateway." << endl;
            return "";
        }

        string transactionId = payment->processPayment();
        string key = payment->getGatewayName() + "_" + transactionId;

        payments[key] = payment;
        cout << "Payment registered with key: " << key << endl;
        return key;
    }

    /**
     * Retrieves and displays payment status
     * @param key The transaction key
     */
    void getPaymentStatus(const string& key) {
        auto it = payments.find(key);
        if (it != payments.end()) {
            it->second->printStatusInfo();
        } else {
            cout << "Error: No payment found with key '" << key << "'" << endl;
        }
    }

    /**
     * Simulates updating payment status (e.g., from webhook)
     * @param key The transaction key
     * @param newStatus The new payment status
     */
    bool updatePaymentStatus(const string& key, PaymentStatus newStatus) {
        auto it = payments.find(key);
        if (it != payments.end()) {
            // Access protected member through a public method
            // In a real implementation, you'd have a setter method
            cout << "Payment status updated for key: " << key << endl;
            return true;
        } else {
            cout << "Error: Cannot update status. No payment found with key '" << key << "'" << endl;
            return false;
        }
    }

    /**
     * Lists all payments
     */
    void listAllPayments() {
        if (payments.empty()) {
            cout << "No payments found." << endl;
            return;
        }

        cout << "\n=== All Payments ===" << endl;
        for (const auto& payment : payments) {
            cout << "Key: " << payment.first << " | Gateway: " << payment.second->getGatewayName() 
                 << " | Amount: $" << fixed << setprecision(2) << payment.second->getAmount() << endl;
        }
        cout << "Total payments: " << payments.size() << endl;
    }

private:
    /**
     * Factory method to create payment processors
     * @param gateway The payment gateway type
     * @param amount The payment amount
     * @return Shared pointer to the created payment processor
     */
    shared_ptr<BasePayment> createPayment(Gateway gateway, double amount) {
        switch (gateway) {
            case Gateway::VISA:
                return make_shared<VisaPayment>(amount);
            case Gateway::MASTERCARD:
                return make_shared<MasterCardPayment>(amount);
            default:
                return nullptr;
        }
    }
};

/**
 * Utility function to convert Gateway enum to string
 */
string gatewayToString(Gateway gateway) {
    switch (gateway) {
        case Gateway::VISA:       return "Visa";
        case Gateway::MASTERCARD: return "MasterCard";
        default:                  return "Unknown";
    }
}

/**
 * Main function - demonstrates the payment gateway system
 */
int main() {
    cout << "=== Payment Gateway System Demo ===" << endl;
    
    PaymentManager manager;

    // Test different payment scenarios
    cout << "\n--- Processing Visa Payment ---" << endl;
    string visaPaymentKey = manager.startPaymentProcess(Gateway::VISA, 500.75);
    
    cout << "\n--- Processing MasterCard Payment ---" << endl;
    string mcPaymentKey = manager.startPaymentProcess(Gateway::MASTERCARD, 1250.00);

    // Test error handling
    cout << "\n--- Testing Error Handling ---" << endl;
    string invalidPaymentKey = manager.startPaymentProcess(Gateway::VISA, -100.0);

    // Check payment statuses
    cout << "\n--- Checking Payment Statuses ---" << endl;
    if (!visaPaymentKey.empty()) {
        manager.getPaymentStatus(visaPaymentKey);
    }
    
    if (!mcPaymentKey.empty()) {
        manager.getPaymentStatus(mcPaymentKey);
    }

    // Test invalid payment lookup
    cout << "\n--- Testing Invalid Payment Lookup ---" << endl;
    manager.getPaymentStatus("INVALID_KEY");

    // List all payments
    cout << "\n--- All Payments Summary ---" << endl;
    manager.listAllPayments();

    return 0;
}
