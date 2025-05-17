#pragma once
#include <iostream>
#include <cstring>
#include "Utils.h"
#include "Billable.h"

using namespace std;
namespace seneca {
	class Food : public Billable {
		bool m_ordered;
		bool m_child;
		char* m_customize;
	public:
		Food();
		Food(const Food& src);
		Food& operator=(const Food& src);
		~Food();

		ostream& print(ostream& ostr = cout) const;
		bool order();
		bool ordered() const;
		ifstream& read(ifstream& file);
		double price() const;

	};
};