#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "Drink.h"

using namespace std;
namespace seneca {
	Drink::Drink() : Billable() {
		m_size = ' ';
	}

	ostream& Drink::print(ostream& ostr) const {
		ostr << left << setw(28) << setfill('.') << Billable::operator const char* ();
		switch (m_size)
		{
		case 'S':
			ostr << "SML.." << setw(7) << fixed << right << setfill(' ') << setprecision(2) << price() << endl;
			break;
		case 'M':
			ostr << "MID.." << setw(7) << fixed << right << setfill(' ') << setprecision(2) << price() << endl;
			break;
		case 'L':
			ostr << "LRG.." << setw(7) << fixed << right << setfill(' ') << setprecision(2) << price() << endl;
			break;
		case 'X':
			ostr << "XLR.." << setw(7) << fixed << right << setfill(' ') << setprecision(2) << price() << endl;
			break;
		default:
			ostr << "....." << setw(7) << fixed << right << setfill(' ') << setprecision(2) << price() << endl;
			break;
		}
		return ostr;
	}

	bool Drink::order() {
		int choice;

		cout << "         Drink Size Selection\n"
			<< "          1- Small\n"
			<< "          2- Medium\n"
			<< "          3- Larg\n"
			<< "          4- Extra Large\n"
			<< "          0- Back\n"
			<< "         > ";
		cin >> choice;
		switch (choice) {
		case 1: m_size = 'S'; break;
		case 2: m_size = 'M'; break;
		case 3: m_size = 'L'; break;
		case 4: m_size = 'X'; break;
		default: m_size = ' '; return false;
		}
		return true;
	}

	bool Drink::ordered() const {
		return m_size != ' ';
	}

	ifstream& Drink::read(ifstream& file) {
		if (file.is_open()) {
			string line;

			if (getline(file, line)) {
				stringstream stringS(line);
				string name;
				double price;

				if (getline(stringS, name, ',') && (stringS >> price)) {
					Billable::price(price);
					Billable::name(name.c_str());
					m_size = ' ';
				}
			}
		}
		return file;
	}

	double Drink::price() const {
		if (m_size == 'S') {
			return Billable::price() / 2.0;
		}
		else if (m_size == 'M') {
			return Billable::price() * 0.75;
		}
		else if (m_size == 'X') {
			return Billable::price() * 1.5;
		}
		return Billable::price();
	}
}