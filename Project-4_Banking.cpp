#include <iostream>
#include <vector>
using namespace std;


// -=== BASE CLASS ===-

class BankAccount
{
    
protected:

    int accountNumber;
    string accountHolderName;

private:

    double balance;

public:

    BankAccount(int accNo, string name, double bal)
    {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    // Deposit
    
    virtual void deposit(double amount)
    {
        balance += amount;
        cout << "Amount Deposited Successfully!\n";
    }

    // Withdraw
    
    virtual void withdraw(double amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
            cout << "Withdrawal Successful!\n";
        }
        
        else
        {
            cout << "Insufficient Balance!\n";
        }
    }

    // Getter
    
    double getBalance()
    {
        return balance;
    }

    // Setter
    
    void setBalance(double bal)
    {
        balance = bal;
    }

    // Display
    
    virtual void displayAccountInfo()
    {
        cout << "\nAccount Number : " << accountNumber << endl;
        cout << "Account Holder   : " << accountHolderName << endl;
        cout << "Balance          : " << balance << endl;
    }

    // Virtual Function
    
    virtual void calculateInterest()
    {
        cout << "No Interest Calculation Available\n";
    }

    virtual ~BankAccount() 
    {
        
    }
};


// -=== SAVINGS ACCOUNT ====-

class SavingsAccount : public BankAccount
{
    double interestRate;


public:

    SavingsAccount(int accNo, string name, double bal, double rate) : BankAccount(accNo, name, bal)
    {
        interestRate = rate;
    }

    void calculateInterest() override
    {
        double interest = getBalance() * interestRate / 100;

        cout << "Savings Interest: " << interest << endl;
    }

    void displayAccountInfo() override
    {
        cout << "\n===== Savings Account =====\n";
        
        BankAccount::displayAccountInfo();
        
        cout << "Interest Rate: " << interestRate << "%\n";
    }
};


// -=== CHECKING ACCOUNT ===-

class CheckingAccount : public BankAccount
{
    double overdraftLimit;

public:

    CheckingAccount(int accNo, string name, double bal, double limit) : BankAccount(accNo, name, bal)
    {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override
    {
        if (amount <= getBalance() + overdraftLimit)
        {
            setBalance(getBalance() - amount);

            cout << "Withdrawal Successful!\n";
        }
        
        else
        {
            cout << "Overdraft Limit Exceeded!\n";
        }
    }

    void checkOverdraft()
    {
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }

    void displayAccountInfo() override
    {
        cout << "\n===== Checking Account =====\n";
        
        BankAccount::displayAccountInfo();
        
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};


// -=== FIXED DEPOSIT ACCOUNT ===-


class FixedDepositAccount : public BankAccount
{
    int term;

public:
    FixedDepositAccount(int accNo, string name, double bal, int t) : BankAccount(accNo, name, bal)
    {
        term = t;
    }

    void calculateInterest() override
    {
        double interest = (getBalance() * 7 * term) / 100;

        cout << "Fixed Deposit Interest: " << interest << endl;
    }

    void displayAccountInfo() override
    {
        cout << "\n===== Fixed Deposit Account =====\n";
        
        BankAccount::displayAccountInfo();
        
        cout << "Term: " << term << " months\n";
    }
};


//-===Main Function===-

int main()
{
    
    vector<BankAccount*> accounts;

    int choice;

    do
    {
        cout << "\n===== BANKING SYSTEM =====\n";
        
        cout << "1. Create Savings Account\n";
        cout << "2. Create Checking Account\n";
        cout << "3. Create Fixed Deposit Account\n";
        cout << "4. Display All Accounts\n";
        cout << "5. Deposit Money\n";
        cout << "6. Withdraw Money\n";
        cout << "7. Calculate Interest\n";
        cout << "8. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int accNo;
            string name;
            double bal, rate;

            cin.ignore();

            cout << "Enter Account Number: ";
            cin >> accNo;

            cin.ignore();

            cout << "Enter Account Holder Name: ";
            getline(cin, name);

            cout << "Enter Balance: ";
            cin >> bal;

            cout << "Enter Interest Rate: ";
            cin >> rate;


            accounts.push_back(new SavingsAccount(accNo, name, bal, rate));


            cout << "Savings Account Created!\n";

            break;
        }

        case 2:
        {
            int accNo;
            string name;
            double bal, limit;

            cin.ignore();

            cout << "Enter Account Number: ";
            cin >> accNo;
            cin.ignore();

            cout << "Enter Account Holder Name: ";
            getline(cin, name);

            cout << "Enter Balance: ";
            cin >> bal;

            cout << "Enter Overdraft Limit: ";
            cin >> limit;

            accounts.push_back(new CheckingAccount(accNo, name, bal, limit));

            cout << "Checking Account Created!\n";

            break;
        }

        case 3:
        {
            int accNo, term;
            string name;
            double bal;
            cin.ignore();

            cout << "Enter Account Number: ";
            cin >> accNo;
            cin.ignore();

            cout << "Enter Account Holder Name: ";
            getline(cin, name);

            cout << "Enter Balance: ";
            cin >> bal;

            cout << "Enter Term (months): ";
            cin >> term;


            accounts.push_back(new FixedDepositAccount(accNo, name, bal, term));


            cout << "Fixed Deposit Account Created!\n";

            break;
        }

        case 4:
        {
            if (accounts.empty())
            {
                cout << "No Accounts Found!\n";
            }
            
            else
            {
                for (int i = 0; i < accounts.size(); i++)
                {
                    accounts[i]->displayAccountInfo();
                }
            }

            break;
        }

        case 5:
        {
            int index;
            double amount;

            cout << "Enter Account Index: ";
            cin >> index;

            cout << "Enter Deposit Amount: ";
            cin >> amount;

            if (index >= 0 && index < accounts.size())
            {
                accounts[index]->deposit(amount);
            }
            
            else
            {
                cout << "Invalid Account Index!\n";
            }

            break;
        }

        case 6:
        {
            int index;
            double amount;

            cout << "Enter Account Index: ";
            cin >> index;

            cout << "Enter Withdraw Amount: ";
            cin >> amount;

            if (index >= 0 && index < accounts.size())
            {
                accounts[index]->withdraw(amount);
            }
            
            else
            {
                cout << "Invalid Account Index!\n";
            }

            break;
        }

        case 7:
        {
            int index;

            cout << "Enter Account Index: ";
            cin >> index;

            if (index >= 0 && index < accounts.size())
            {
                accounts[index]->calculateInterest();
            }
            
            else
            {
                cout << "Invalid Account Index!\n";
            }

            break;
        }

        case 8:
        {
            cout << "Thank You Visit Again!\n";
            break;
        }

        default:
        {
            cout << "Invalid Choice!\n";
        }
        }

    } 
    while (choice != 8);

    // Memory Release
    
    for (int i = 0; i < accounts.size(); i++)
    {
        delete accounts[i];
    }

    return 0;
}
