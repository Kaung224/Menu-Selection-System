#pragma once
#include <iostream>
#include <cstring>
#include "Billable.h"

using namespace std;
namespace seneca {
	class Drink : public Billable {
		char m_size;
	public:
		Drink();
		ostream& print(ostream& ostr = cout) const;
		bool order();
		bool ordered() const;
		ifstream& read(ifstream& file);
		double price() const;
	};
}