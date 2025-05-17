#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "Food.h"
#include "Utils.h"

using namespace std;
namespace seneca {
	Food::Food() : Billable() {
		m_ordered = false;
		m_child = false;
		m_customize = nullptr;
	}

	Food::Food(const Food& src) : Billable(src) {
		m_ordered = src.m_ordered;
		m_child = src.m_child;
		if (src.m_customize) {
			m_customize = new char[strlen(src.m_customize) + 1];
			strcpy(m_customize, src.m_customize);
		}
		else {
			m_customize = nullptr;
		}
	}

	Food& Food::operator=(const Food& src) {
		if (this != &src) {
			Billable::operator=(src);

			m_ordered = src.m_ordered;
			m_child = src.m_child;

			delete[] m_customize;

			if (src.m_customize) {
				m_customize = new char[strlen(src.m_customize) + 1];
				strcpy(m_customize, src.m_customize);
			}
			else {
				m_customize = nullptr;
			}
		}
		return *this;
	}

	Food::~Food() {
		delete[] m_customize;
		m_customize = nullptr;
	}

	ostream& Food::print(ostream& ostr) const {
		ostr << left << setw(28) << setfill('.') << Billable::operator const char* ();
		if (ordered()) {
			if (m_child) {
				ostr << "Child" << setw(7) << fixed << right << setfill(' ') << setprecision(2) << price();
			}
			else {
				ostr << "Adult" << setw(7) << fixed << right << setfill(' ') << setprecision(2) << price();
			}
		}
		else {
			ostr << "....." << setw(7) << fixed << right << setfill(' ') << setprecision(2) << price();;
		}

		if (&ostr == &cout && m_customize) {
			ostr << " >> " << string(m_customize).substr(0, 30) << "\n";
		}
		else {
			ostr  << '\n';
		}

		return ostr;
	}



	bool Food::order() {
		int choice;

		std::cout << "         Food Size Selection\n"
			<< "          1- Adult\n"
			<< "          2- Child\n"
			<< "          0- Back\n"
			<< "         > ";
		cin >> choice;


		cin.ignore(100, '\n');

		// Handle the food size selection
		if (choice == 1) {
			cout << "Special instructions\n> ";
			string customize;
			getline(cin, customize);

			if (customize.empty()) {
				if (m_customize) {
					delete[] m_customize;
					m_customize = nullptr;
				}
			}
			else {
				delete[] m_customize;
				m_customize = new char[customize.length() + 1];
				strcpy(m_customize, customize.c_str());
			}
			m_child = false;
			m_ordered = true;
		}
		else if (choice == 2) {
			cout << "Special instructions\n> ";
			string customize;
			getline(cin, customize);

			if (customize.empty()) {
				if (m_customize) {
					delete[] m_customize;
					m_customize = nullptr;
				}
			}
			else {
				delete[] m_customize;
				m_customize = new char[customize.length() + 1];
				strcpy(m_customize, customize.c_str());
			}
			m_child = true;
			m_ordered = true;
		}
		else if (choice == 0) {
			m_ordered = false;
			if (m_customize) {
				delete[] m_customize;
				m_customize = nullptr;
			}
			return false;
		}

		return true;
	}


	bool Food::ordered() const {
		return m_ordered;
	}

	ifstream& Food::read(ifstream& file) {
		if (file.is_open()) {
			string line;

			if (getline(file, line)) {
				stringstream stringS(line);
				string name;
				double price;

				if (getline(stringS, name, ',') && (stringS >> price)) {
					Billable::price(price);
					Billable::name(name.c_str());
					m_ordered = false;
					m_child = false;
					delete[] m_customize;
					m_customize = nullptr;
				}
			}
		}
		return file;
	}

	double Food::price() const {
		if (m_ordered && m_child) {
			return Billable::price() / 2;
		}
		return Billable::price();
	}
}