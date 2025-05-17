#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Billable.h"
#include "Utils.h"

using namespace std;
namespace seneca {
	void Billable::price(double value) {
		m_price = value;
	}

	void Billable::name(const char* name) {
		delete[] m_name;
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}

	Billable::Billable() {
		m_price = 0;
		m_name = nullptr;
	}

	Billable::Billable(const Billable& src) {
		m_price = src.m_price;
		if (src.m_name) {
			m_name = new char[strlen(src.m_name) + 1];
			strcpy(m_name, src.m_name);
		}
		else {
			m_name = nullptr;
		}
	}

	Billable& Billable::operator=(const Billable& src) {
		if (this != &src) {
			delete[] m_name;

			m_price = src.m_price;
			if (src.m_name) {
				m_name = new char[strlen(src.m_name) + 1];
				strcpy(m_name, src.m_name);
			}
			else {
				m_name = nullptr;
			}
		}

		return *this;
	}

	Billable::~Billable() {
		delete[] m_name;
		m_name = nullptr;
	}

	double Billable::price() const {
		return m_price;
	}

	Billable::operator const char* () const {
		return m_name ? m_name : "";
	}

	double operator+(double money, const Billable& B) {
		return money + B.price();
	}

	double& operator+=(double& money, const Billable& B) {
		money += B.price();
		return money;
	}
}