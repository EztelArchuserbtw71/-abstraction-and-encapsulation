#include<iostream>
#include<string>
#include<limits>
using namespace std;

class bankAccount {
protected:
    string accountHolderName;//name of account owner
    string accountNumber;
    string accountPassword;
    double balance;

public:
    bankAccount(string name, string accNum, string password) : accountHolderName(name), accountNumber(accNum), accountPassword(password), balance(0) {}

    virtual void deposit(double amount) = 0;
    virtual bool withdraw(double amount) = 0;
    virtual void checkBalance() const {
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << balance << endl;
    }

    string getaccountNumber() const {
        return accountNumber;
    }

    string getPassword() const {
        return accountPassword;
    }

    string getaccountHolderName() const {
        return accountHolderName;
    }
};

class savingsAccount : public bankAccount {
private:
    const double interestRate = 0.04;//the interest rate of  savings account(based on google)
    const double minimumBalance = 1000;//mininum balance of savings account

public:
    savingsAccount(string name, string accNum, string password) : bankAccount(name, accNum, password) {
        balance = 1000;//the balnce already have in savings
    }

    void deposit(double amount) override {
        balance += amount;
        cout << "$" << amount << " deposited to Savings Account." << endl;
    }

    bool withdraw(double amount) override {//withraw overide in the savings account
        if (balance - amount < minimumBalance) {
            cout << "Insufficient funds! Savings Account must maintain a minimum balance of $1000." << endl;
            return false;
        } else {
            balance -= amount;
            cout << "$" << amount << " withdrawn from Savings Account." << endl;
            return true;
        }
    }

    void checkBalance() const override {
        cout << "Savings Account Balance: $" << balance << endl;//display of availble money
    }
};

class currentAccount : public bankAccount {
public:
    currentAccount(string name, string accNum, string password) : bankAccount(name, accNum, password) {}

    void deposit(double amount) override {
        balance += amount;
        cout << "$" << amount << " deposited to Current Account." << endl;
    }

    bool withdraw(double amount) override {
        if (balance < amount) {
            cout << "Insufficient funds! Cannot withdraw more than available balance." << endl;
            return false;
        } else {
            balance -= amount;
            cout << "$" << amount << " withdrawn from Current Account." << endl;
            return true;
        }
    }

    void checkBalance() const override {
        cout << "Current Account Balance: $" << balance << endl;
    }
};

class bankSystem {// bank sytem were can input name, accnum and etc
private:
    savingsAccount* savingsAcc = nullptr;
    currentAccount* currentAcc = nullptr;

public:
    void registerAccount() {
        string name, accNum, password;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your account number: ";
        cin >> accNum;
        cout << "Enter your account password: ";
        cin >> password;

        savingsAcc = new savingsAccount(name, accNum, password);
        currentAcc = new currentAccount(name, accNum, password);
        cout << "Account created successfully!" << endl;
    }

    bool login() {
        string accNum, password;
        cout << "Enter your account number: ";
        cin >> accNum;
        cout << "Enter your account password: ";
        cin >> password;

        if (savingsAcc && currentAcc && savingsAcc->getaccountNumber() == accNum && savingsAcc->getPassword() == password) {
            cout << "Login successful! Welcome " << savingsAcc->getaccountHolderName() << endl;
            return true;
        } else {
            cout << "Invalid account number or password!" << endl;
            return false;
        }
    }

    void showMainMenu() {
        int option;
        do {
            cout << "Main Menu:" << endl;
            cout << "1. Savings Account" << endl;
            cout << "2. Current Account" << endl;
            cout << "3. Exit" << endl;
            cout << "Choose an option: ";
            if (!(cin >> option)) {
                cout << "Invalid input, please enter a valid number. Try again!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');//use of #include<limits> it is ok??
            } else {
                switch (option) {
                    case 1:
                        showAccountMenu(savingsAcc);
                        break;
                    case 2:
                        showAccountMenu(currentAcc);
                        break;
                    case 3:
                        cout << "Exiting..." << endl;
                        break;
                    default:
                        cout << "Invalid option, please try again!" << endl;
                }
            }
        } while (option != 3);
    }

    void showAccountMenu(bankAccount* account) {
        int option;
        do {
            cout << "Sub Menu:" << endl;
            cout << "1. Deposit" << endl;
            cout << "2. Withdraw" << endl;
            cout << "3. Check Balance" << endl;
            cout << "4. Back" << endl;
            cout << "Choose an option: ";
            if (!(cin >> option)) {
                cout << "Invalid input, please enter a valid number. Try again!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');// limits
            } else {
                switch (option) {
                    case 1: {
                        double amount;
                        cout << "Enter amount to deposit: ";
                        if (!(cin >> amount)) {
                            cout << "Invalid input, please enter a valid amount. Try again!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            account->deposit(amount);
                        }
                        break;
                    }
                    case 2: {
                        double amount;
                        cout << "Enter amount to withdraw: ";
                        if (!(cin >> amount)) {
                            cout << "Invalid input, please enter a valid amount. Try again!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');// again limits
                        } else {
                            account->withdraw(amount);
                        }
                        break;
                    }
                    case 3:
                        account->checkBalance();
                        break;
                    case 4:
                        break;
                    default:
                        cout << "Invalid option, please try again!" << endl;
                }
            }
        } while (option != 4);
    }
};

int main() {
    bankSystem bank;
    int option;

    do {
        cout << "Welcome to the Bank!" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose an option: ";
        if (!(cin >> option)) {
            cout << "Invalid input, please enter a valid number. Try again!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            switch (option) {
                case 1:
                    if (bank.login()) {
                        bank.showMainMenu();
                    }
                    break;
                case 2:
                    bank.registerAccount();
                    break;
                case 3:
                    cout << "Thank you for using the bank system!" << endl;//exit message but dousnt quit or exit the terminal
                    break;
                default:
                    cout << "Invalid option, please try again!" << endl;// if the input is wrong
            }
        }
    } while(option != 3);// ser i forgot something is this allowed??

    return 0;
}
