#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

class ElectricityBill {
public:
    string CustomerName;
    string PhoneNumber;
    int MeterNumber;
    int Units;
    float TotalBill;
    float SubsidyAmount;
    string BillDate;

public:
    ElectricityBill() {
        totalBill = 0;
        units = 0;
        subsidyAmount = 0;
        billDate = getCurrentDate();
    }

    string getCurrentDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[15];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y", ltm);
        return string(buffer);
    }

    void inputDetails() {
        cout << "\nEnter Customer Name: ";
        cin.ignore();
        getline(cin, customerName);

        cout << "Enter Phone Number  : ";
        getline(cin, phoneNumber);

        cout << "Enter Meter Number  : ";
        cin >> meterNumber;

        cout << "Enter Units Consumed: ";
        cin >> units;
    }

    void calculateBill() {
        float baseBill = 0;

        // Slab-based bill calculation
        if (units <= 100) {
            baseBill = units * 1.50;
        } else if (units <= 200) {
            baseBill = 100 * 1.50 + (units - 100) * 2.00;
        } else if (units <= 300) {
            baseBill = 100 * 1.50 + 100 * 2.00 + (units - 200) * 3.00;
        } else {
            baseBill = 100 * 1.50 + 100 * 2.00 + 100 * 3.00 + (units - 300) * 5.00;
        }

        baseBill += 50; // fixed meter charge

        // Subsidy
        if (units <= 100) {
            subsidyAmount = baseBill * 0.20;
        } else if (units <= 200) {
            subsidyAmount = baseBill * 0.10;
        } else {
            subsidyAmount = 0;
        }

        totalBill = baseBill - subsidyAmount;
    }

    void displayBill() {
        cout << "\n Electricity Bill --" << endl;
        cout << "Date  : " << billDate << endl;

        cout << "Customer Name    : " << customerName << endl;
        cout << "Phone Number     : " << phoneNumber << endl;
        cout << "Meter Number     : " << meterNumber << endl;
        cout << "Units Consumed   : " << units << " units" << endl;
        cout << "Subsidy Applied  : Rs. " << fixed << setprecision(2) << subsidyAmount << endl;
        cout << "Total Bill       : Rs. " << fixed << setprecision(2) << totalBill << endl;
        cout << "\n";
    }



    void saveToFile() {
        ofstream file("bills.txt", ios::app);
        if (file.is_open()) {
            file << "\n========== Electricity Bill ==========\n";
            file << "Date : " << billDate << "\n";
            file << "Customer Name    : " << customerName << "\n";
            file << "Phone Number     : " << phoneNumber << "\n";
            file << "Meter Number     : " << meterNumber << "\n";
            file << "Units Consumed   : " << units << " units\n";
            file << "Subsidy Applied  : Rs. " << fixed << setprecision(2) << subsidyAmount << "\n";
            file << "Total Bill       : Rs. " << fixed << setprecision(2) << totalBill << "\n";
            file << "\n";
            file.close();
            cout << "\nBill saved to 'bills.txt'\n";
        } else {
            cout << "Error saving bill to file.\n";
        }
    }
};

void showMenu() {
    cout << "\nElectricity Billing System \n";
    cout << "1. Generate New Bill\n";
    cout << "2. View Saved Bills\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void viewSavedBills() {
    ifstream file("bills.txt");
    if (file.is_open()) {
        string line;
        cout << "\nSaved Bills\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "\nNo saved bills found.\n";
    }
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                ElectricityBill bill;
                bill.inputDetails();
                bill.calculateBill();
                bill.displayBill();
                bill.saveToFile();
                break;
            }
            case 2:
                viewSavedBills();
                break;

            case 3:
                cout << "Exiting program. Thank you!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}

