#pragma once
#include <iostream>
#include <cstring>

using namespace std;
namespace seneca {
	class Billable {
		char* m_name{};
		double m_price;
	protected:
		void price(double value);
		void name(const char* name);
	public:
		Billable();
		Billable(const Billable& src);
		Billable& operator=(const Billable& src);
		operator const char* ()const;
		virtual ~Billable();

		// Virtual Methods

		virtual double price() const;
		virtual ostream& print(ostream& ostr = cout) const = 0;
		virtual bool order() = 0;
		virtual bool ordered() const = 0;
		virtual ifstream& read(ifstream& file) = 0;
		friend double operator+(double money, const Billable& B);
		friend double& operator+=(double& money, const Billable& B);
	};
}