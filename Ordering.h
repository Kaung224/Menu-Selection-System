#pragma once
#include <iostream>
#include <cstring>
#include "Food.h"
#include "Drink.h"
#include "constants.h"
#include "Billable.h"
#include "Menu.h"
#include "Utils.h"


using namespace std;
namespace seneca {
	class Ordering {
		int foodCounter{};
		int drinkCounter{};
		int billableCounter{};
		int billNumber{};
		Food* foodArray{};
		Drink* drinkArray{};
		Billable** billItems{};
	public:
		ostream& billTitlePrint(ostream& os = cout) const;
		ostream& printTotals(double total, ostream& os = cout) const;
		size_t countRecords(const char* file) const;
		Ordering(const char* drinkFile, const char* foodFile);
		~Ordering();
		operator bool() const;
		int noOfBillItems() const;
		bool hasUnsavedBill() const;
		ostream& listFoods(ostream& os = cout) const;
		ostream& ListDrinks(ostream& os = cout) const;
		void orderFood();
		void orderDrink();
		ostream& printBill(ostream& os = cout) const;
		void resetBill();
        void orderMenu(seneca::Ordering& orderingSystem); 

	};
}
