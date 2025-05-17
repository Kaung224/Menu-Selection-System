#include <iostream>
#include <fstream>
#include "Menu.h"
#include "Food.h"
#include "Drink.h"
#include "Ordering.h"
using namespace std;
using namespace seneca;

void saveBill(Ordering& ord) {
    ofstream billtest("billTest.txt");
    ord.printBill(billtest);
}
void showSavedBill(const char* filename) {
    ifstream billtest(filename);
    char ch;
    while (billtest.get(ch) && cout << ch);
}
int main() {
    Ordering orderingSystem("drinks.csv", "foods.csv"); // Replace with actual file paths

    if (!orderingSystem) {
        cout << "Error loading menu items. Please check the files." << endl;
        return 1;
    }

    bool exitProgram = false;
    while (!exitProgram) {
        cout << "Seneca Restaurant \n"
            << " 1- Order\n"
            << " 2- Print Bill\n"
            << " 3- Start a New Bill\n"
            << " 4- List Foods\n"
            << " 5- List Drinks\n"
            << " 0- End Program\n"
            << "> ";

        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            orderingSystem.orderMenu(orderingSystem);
            break;
        case 2:
            orderingSystem.printBill(cout);
            break;
        case 3:
            orderingSystem.resetBill();
            break;
        case 4:
            orderingSystem.listFoods(cout);
            break;
        case 5:
            orderingSystem.ListDrinks(cout);
            break;
        case 0:
            if (orderingSystem.hasUnsavedBill()) {
                cout << "You have bills that are not saved, are you sue you want to exit?\n";
                cout << " 1- Yes\n";
                cout << " 0- No\n";
                cout << "> ";
                cin >> choice;
            }
            else {
                exitProgram = true;
                break;
            }
            if (choice == 1) {
                exitProgram = true;
                break;
            }
            else {
                break;
            }
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
    return 0;
}
