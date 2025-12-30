#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Base Account class
class Account {
protected:
    string accNum;
    string holderName;
    double balance;
    string accType;
    
public:
    Account() {
        accNum = "";
        holderName = "";
        balance = 0.0;
        accType = "";
    }
    
    Account(string num, string name, double bal, string type) {
        accNum = num;
        holderName = name;
        balance = bal;
        accType = type;
    }
    
    virtual ~Account() {}
    
    // Virtual functions for polymorphism
    virtual void deposit(double amt) {
        if (amt > 0) {
            balance = balance + amt;
            cout << "Deposited: $" << amt << endl;
            cout << "New Balance: $" << balance << endl;
        } else {
            cout << "Invalid amount!" << endl;
        }
    }
    
    virtual bool withdraw(double amt) {
        if (amt > 0 && amt <= balance) {
            balance = balance - amt;
            cout << "Withdrawn: $" << amt << endl;
            cout << "New Balance: $" << balance << endl;
            return true;
        } else {
            cout << "Insufficient balance or invalid amount!" << endl;
            return false;
        }
    }
    
    virtual void display() {
        cout << "\n--- Account Details ---" << endl;
        cout << "Account Number: " << accNum << endl;
        cout << "Holder Name: " << holderName << endl;
        cout << "Account Type: " << accType << endl;
        cout << "Balance: $" << balance << endl;
    }
    
    string getAccNum() { 
        return accNum; 
    }
    
    double getBalance() { 
        return balance; 
    }
    
    string getHolderName() { 
        return holderName; 
    }
};

// Savings Account with interest
class SavingsAccount : public Account {
private:
    double interestRate;
    
public:
    SavingsAccount() {
        interestRate = 0.04;
    }
    
    SavingsAccount(string num, string name, double bal, double rate) {
        accNum = num;
        holderName = name;
        balance = bal;
        accType = "Savings";
        interestRate = rate;
    }
    
    void addInterest() {
        double interest = balance * interestRate;
        balance = balance + interest;
        cout << "Interest added: $" << interest << endl;
        cout << "New Balance: $" << balance << endl;
    }
    
    void display() {
        Account::display();
        cout << "Interest Rate: " << (interestRate * 100) << "%" << endl;
    }
};

// Current Account with overdraft
class CurrentAccount : public Account {
private:
    double overdraftLimit;
    
public:
    CurrentAccount() {
        overdraftLimit = 1000.0;
    }
    
    CurrentAccount(string num, string name, double bal, double limit) {
        accNum = num;
        holderName = name;
        balance = bal;
        accType = "Current";
        overdraftLimit = limit;
    }
    
    bool withdraw(double amt) {
        if (amt > 0 && (balance + overdraftLimit) >= amt) {
            balance = balance - amt;
            cout << "Withdrawn: $" << amt << endl;
            cout << "New Balance: $" << balance << endl;
            return true;
        } else {
            cout << "Overdraft limit exceeded or invalid amount!" << endl;
            return false;
        }
    }
    
    void display() {
        Account::display();
        cout << "Overdraft Limit: $" << overdraftLimit << endl;
    }
};

// Bank class to manage accounts
class Bank {
private:
    vector<Account*> accounts;
    
public:
    Bank() {}
    
    ~Bank() {
        for (size_t i = 0; i < accounts.size(); i++) {
            delete accounts[i];
        }
        accounts.clear();
    }
    
    void createSavingsAccount() {
        string num, name;
        double bal, rate;
        
        cout << "\n--- Create Savings Account ---" << endl;
        cout << "Enter Account Number: ";
        cin >> num;
        cin.ignore();
        cout << "Enter Holder Name: ";
        getline(cin, name);
        cout << "Enter Initial Balance: $";
        cin >> bal;
        cout << "Enter Interest Rate (e.g., 0.04 for 4%): ";
        cin >> rate;
        
        SavingsAccount* newAcc = new SavingsAccount(num, name, bal, rate);
        accounts.push_back(newAcc);
        cout << "Savings Account created successfully!" << endl;
    }
    
    void createCurrentAccount() {
        string num, name;
        double bal, limit;
        
        cout << "\n--- Create Current Account ---" << endl;
        cout << "Enter Account Number: ";
        cin >> num;
        cin.ignore();
        cout << "Enter Holder Name: ";
        getline(cin, name);
        cout << "Enter Initial Balance: $";
        cin >> bal;
        cout << "Enter Overdraft Limit: $";
        cin >> limit;
        
        CurrentAccount* newAcc = new CurrentAccount(num, name, bal, limit);
        accounts.push_back(newAcc);
        cout << "Current Account created successfully!" << endl;
    }
    
    Account* findAccount(string accNum) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i]->getAccNum() == accNum) {
                return accounts[i];
            }
        }
        return NULL;
    }
    
    void depositMoney() {
        string num;
        double amt;
        
        cout << "\nEnter Account Number: ";
        cin >> num;
        Account* acc = findAccount(num);
        
        if (acc != NULL) {
            cout << "Enter Amount to Deposit: $";
            cin >> amt;
            acc->deposit(amt);
        } else {
            cout << "Account not found!" << endl;
        }
    }
    
    void withdrawMoney() {
        string num;
        double amt;
        
        cout << "\nEnter Account Number: ";
        cin >> num;
        Account* acc = findAccount(num);
        
        if (acc != NULL) {
            cout << "Enter Amount to Withdraw: $";
            cin >> amt;
            acc->withdraw(amt);
        } else {
            cout << "Account not found!" << endl;
        }
    }
    
    void checkBalance() {
        string num;
        cout << "\nEnter Account Number: ";
        cin >> num;
        Account* acc = findAccount(num);
        
        if (acc != NULL) {
            cout << "Current Balance: $" << acc->getBalance() << endl;
        } else {
            cout << "Account not found!" << endl;
        }
    }
    
    void displayAccount() {
        string num;
        cout << "\nEnter Account Number: ";
        cin >> num;
        Account* acc = findAccount(num);
        
        if (acc != NULL) {
            acc->display();
        } else {
            cout << "Account not found!" << endl;
        }
    }
    
    void displayAllAccounts() {
        if (accounts.size() == 0) {
            cout << "\nNo accounts found!" << endl;
            return;
        }
        
        cout << "\n=== All Accounts ===" << endl;
        for (size_t i = 0; i < accounts.size(); i++) {
            accounts[i]->display();
            cout << "----------------------" << endl;
        }
    }
};

// Main function
int main() {
    Bank bank;
    int choice;
    
    cout << "=====================================" << endl;
    cout << "  Banking Management System v1.0" << endl;
    cout << "=====================================" << endl;
    
    while (true) {
        cout << "\n====== Banking Management System ======" << endl;
        cout << "1. Create Savings Account" << endl;
        cout << "2. Create Current Account" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Check Balance" << endl;
        cout << "6. Display Account Details" << endl;
        cout << "7. Display All Accounts" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                bank.createSavingsAccount();
                break;
            case 2:
                bank.createCurrentAccount();
                break;
            case 3:
                bank.depositMoney();
                break;
            case 4:
                bank.withdrawMoney();
                break;
            case 5:
                bank.checkBalance();
                break;
            case 6:
                bank.displayAccount();
                break;
            case 7:
                bank.displayAllAccounts();
                break;
            case 8:
                cout << "\nThank you for using Banking Management System!" << endl;
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}
