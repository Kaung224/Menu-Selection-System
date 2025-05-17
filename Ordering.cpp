#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include "Ordering.h"

using namespace std;
namespace seneca {
	ostream& Ordering::billTitlePrint(ostream& os) const{
		os << "Bill # " << setw(3) << setfill('0') << billNumber << " =============================\n";
		return os;
	}

	ostream& Ordering::printTotals(double total, ostream& os) const {
		const double tax = Tax;
		double taxAmount = tax * total;
		double grandTotal = total + taxAmount;
		os << "                     Total: " << fixed << setprecision(2) << setw(12) << setfill(' ') << total << endl;
		os << "                     Tax: " << fixed << setprecision(2) << setw(14) << setfill(' ') << taxAmount << endl;
		os << "                     Total+Tax: " << fixed << setprecision(2) << setw(8) << setfill(' ') << grandTotal << endl;
		os << "========================================\n";
		return os;
	}


	size_t Ordering::countRecords(const char* filename) const {
		std::ifstream file(filename);  
		if (!file.is_open()) {
			return 0;  
		}

		size_t count = 0;
		string line;

		while (getline(file, line)) {
			count++;  
		}

		file.close();  
		return count;
	}


	Ordering::Ordering(const char* drinkFile, const char* foodFile) {
		int foodRecords = countRecords(foodFile);
		int drinkRecords = countRecords(drinkFile);
		
		if (foodRecords == 0 || drinkRecords == 0) {
			foodArray = nullptr;
			drinkArray = nullptr;
			foodCounter = 0;
			drinkCounter = 0;
			return;
		}

		ifstream foodStream(foodFile);
		ifstream drinkStream(drinkFile);
		
		if (!foodStream.is_open() || !drinkStream.is_open()) {
			foodArray = nullptr;
			drinkArray = nullptr;
			foodCounter = 0;
			drinkCounter = 0;
			return;
		}

		foodArray = new Food[foodRecords];
		drinkArray = new Drink[drinkRecords];

		int foodCount = 0;
		int drinkCount = 0;

		while (foodStream && foodCount < foodRecords) {
			foodArray[foodCount].read(foodStream);
			foodCount++;
		}

		while (drinkStream && drinkCount < drinkRecords) {
			drinkArray[drinkCount].read(drinkStream);
			drinkCount++;
		}

		billItems = new Billable*[MaximumNumberOfBillItems];
		for (size_t i = 0; i < MaximumNumberOfBillItems; ++i) {
			billItems[i] = nullptr;  
		}

		if (foodCount == foodRecords && drinkCount == drinkRecords) {
			foodCounter = foodCount;
			drinkCounter = drinkCount;
			billableCounter = 0;
			billNumber = 1;
		}
		else {
			delete[] foodArray;
			delete[] drinkArray;
			foodArray = nullptr;
			drinkArray = nullptr;
			delete[] billItems;
		}
	}


	Ordering::~Ordering() {
		delete[] foodArray;
		delete[] drinkArray;

		for (int i = 0; i < billableCounter; i++) {
			delete billItems[i];
			billItems[i] = nullptr;
		}
		delete[] billItems;
	}

	Ordering::operator bool() const {
		return foodArray != nullptr && drinkArray != nullptr;
	}

	int Ordering::noOfBillItems() const {
		return billableCounter;
	}

	bool Ordering::hasUnsavedBill() const {
		return billableCounter > 0; 
	}
	
	ostream& Ordering::listFoods(ostream& os) const {
		os << "List Of Avaiable Meals" << endl;
		os << "========================================\n";
		for (int i = 0; i < foodCounter; i++) {
			foodArray[i].print();
		}
		os << "========================================\n";
		return os;
	}

	ostream& Ordering::ListDrinks(ostream& os) const {
		os << "List Of Avaiable Drinks" << endl;
		os << "========================================\n";
		for (int i = 0; i < drinkCounter; i++) {
			drinkArray[i].print();
			os << endl;
		}
		os << "========================================\n";
		return os;
	}

	void Ordering::orderFood() {
		int selection;
		Menu foodMenu("Food Menu", "Back to Order", 2);
		for (int i = 0; i < foodCounter; i++) {
			foodMenu << foodArray[i];
		}

		selection = foodMenu.select();

		if (selection != 0) {
			Food* newFoodItem = new Food(foodArray[selection - 1]);
			bool orderSucessfully = newFoodItem->order();
			if (orderSucessfully) {
				size_t nextAvailableIndex = billableCounter;
				if (nextAvailableIndex < MaximumNumberOfBillItems) {
					billItems[nextAvailableIndex] = newFoodItem;
					billableCounter++;
				}
			}
			else {
				delete newFoodItem;
			}
		}
	}


	void Ordering::orderDrink() {
		int selection;
		
		Menu drinkMenu("Drink Menu", "Back to Order", 2);
		for (int i = 0; i < drinkCounter; i++) {
			drinkMenu << drinkArray[i];
		}

		selection = drinkMenu.select(); 

		if (selection != 0) {
			Drink* newDrinkItem = new Drink(drinkArray[selection - 1]); 
			bool orderSuccessfully = newDrinkItem->order(); 

			if (orderSuccessfully) {
				size_t nextAvailableIndex = billableCounter;
				if (nextAvailableIndex < MaximumNumberOfBillItems) {
					billItems[nextAvailableIndex] = newDrinkItem;
					billableCounter++;
				}
			}
			else {
				delete newDrinkItem;  
			}
		}
	
	}

	ostream& Ordering::printBill(ostream& os) const {
		double total = 0.0;

		billTitlePrint(os);
		for (int i = 0; i < billableCounter; i++) {
			billItems[i]->print(os);
			total += billItems[i]->price();
		}
		printTotals(total , os);
		return os;
	}

	void Ordering::resetBill() {
		Utils ut;
		char filename[41];
		ut.makeBillFileName(filename, billNumber);

		ofstream billFile(filename);

		if (billFile.is_open()) {
			printBill(billFile);

			cout << "Saved bill number " << billNumber << endl;
			billNumber++;

			cout << "Starting bill number " << billNumber << endl;
		}

		for (int i = 0; i < billableCounter; i++) {
			delete billItems[i];
		}

		
		billableCounter = 0;

	}
	
	void Ordering::orderMenu(seneca::Ordering& orderingSystem) {
		int choice;
		do {
			cout << "   Order Menu\n"
				<< "    1- Food\n"
				<< "    2- Drink\n"
				<< "    0- Back to main menu\n"
				<< "   > ";
			cin >> choice;

			switch (choice) {
			case 1:
				orderingSystem.orderFood();
				break;
			case 2:
				orderingSystem.orderDrink();
				break;
			case 0:
				break;
			default:
				cout << "Invalid choice. Please try again.\n";
				break;
			}
		} while (choice != 0);
	}

}

