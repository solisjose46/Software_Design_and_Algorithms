//=====================================================================================
// Name        : Index.cpp
// Author      : Jose Solis Salazar
// Copyright   : Copyright (C). CS Department Foothill College 2015. All rights reserved.
// Program purpose: Program allows for searching and viewing of properties from a list of multiple properties
//=====================================================================================

#include <iostream>
//#include <conio.h>
#include <string>

using namespace std;
//Class Property
class Property {
private:
	Property * next_;
protected:
	string address_;
	int zip_code_;
	double offered_price_;
	int year_built_;
public:
	Property();
	Property(string, int, double, int);
	virtual ~Property();
	void virtual ShowPropertyInfo()const;
	bool operator<=(double)const;
	//Accessors and mutators
	void SetNext(Property*);
	void SetAddress(string);
	void SetZipCode(int);
	void SetPrice(double);
	void SetYear(int);
	Property * GetNext()const;
	int GetZip()const;
	double GetPrice()const;
	int GetYear()const;
	string GetAddress()const;
	
};
Property::Property() :next_(NULL), address_("123 Fake Street"), zip_code_(12345), offered_price_(0.00), year_built_(1994) {}
Property::Property(string street_adress, int zip, double price, int year_made) {
	next_ = NULL;
	address_ = street_adress;
	zip_code_ = zip;
	offered_price_ = price;
	year_built_ = year_made;
}
Property::~Property() {
	//no op
}
void Property::ShowPropertyInfo()const {}
bool Property::operator<=(double num) const{
	if (this->GetPrice() <= num) {
		return true;
	}
	else {
		return false;
	}
}
void Property::SetNext(Property * p_home) {
	next_ = p_home;
}
void Property::SetAddress(string street_address) {
	address_ = street_address;
}
void Property::SetZipCode(int zip) {
	zip_code_ = zip;
}
void Property::SetPrice(double price) {
	offered_price_ = price;
}
void Property::SetYear(int year_made) {
	year_built_ = year_made;
}
Property * Property::GetNext() const{
	return next_;
}
int Property::GetZip()const {
	return zip_code_;
}
double Property::GetPrice()const {
	return offered_price_;
}
int Property::GetYear() const{
	return year_built_;
}
string Property::GetAddress()const {
	return address_;
}
//Class Townhouse
class Townhouse : public Property {
private:
	double HOA_monthly_fee_;
public:
	Townhouse();
	Townhouse(string, int, double, int, double);
	virtual ~Townhouse();
	void virtual ShowPropertyInfo()const;
	double GetFee()const;
	void SetFee(double);

};
Townhouse::Townhouse() :HOA_monthly_fee_(100.0) {
	Property();
}
Townhouse::Townhouse(string address, int zip, double price, int year_made, double fee) {
	address_ = address;
	zip_code_ = zip;
	offered_price_ = price;
	year_built_ = year_made;
	HOA_monthly_fee_ = fee;
}
Townhouse::~Townhouse() {
	//no op
}
void Townhouse::ShowPropertyInfo()const {
	cout << "------------------------------------------------Townhouse---------------------------------------------------------" << endl;
	cout << "Address: " << address_ << ", Zip Code: " << zip_code_ << ", Price: $" << offered_price_ << ", Year Built: " << year_built_ <<
		", HOA Monthly Fee: $" << HOA_monthly_fee_ << endl;
}
double Townhouse::GetFee()const {
	return HOA_monthly_fee_;
}
void Townhouse::SetFee(double fee) {
	HOA_monthly_fee_ = fee;
}
//Class Single Family House
class SingleFamilyHouse : public Property {
private:
	double backyard_area_;
public:
	SingleFamilyHouse();
	SingleFamilyHouse(string, int, double, int, double);
	virtual ~SingleFamilyHouse();
	void virtual ShowPropertyInfo()const;
	void SetArea(double);
	double GetArea();
};
SingleFamilyHouse::SingleFamilyHouse() :backyard_area_(0.00) {
	Property();
}
SingleFamilyHouse::SingleFamilyHouse(string address, int zip, double price, int year_made, double area) {
	address_ = address;
	zip_code_ = zip;
	offered_price_ = price;
	year_built_ = year_made;
	backyard_area_ = area;
}
SingleFamilyHouse::~SingleFamilyHouse() {
	//no op
}
void SingleFamilyHouse::ShowPropertyInfo()const {
	cout << "----------------------------------------------Single Family House-----------------------------------------------------------" << endl;
	cout << "Address: " << address_ << ", Zip Code: " << zip_code_ << ", Price: $" << offered_price_ << ", Year Built: " << year_built_ <<
		", Backyard Area: " << backyard_area_ << " square feet" << endl;
}
void SingleFamilyHouse::SetArea(double area) {
	backyard_area_ = area;
}
double SingleFamilyHouse::GetArea() {
	return backyard_area_;
}
//class PropertyList
class PropertyList {
private:
	Property * head_;
public:
	PropertyList();
	~PropertyList();
	void Insert(Property*);
	void InIt();
	void ViewAllProperties();
	void SearchTownHouseByZipCode(int);
	void SearchByMaxPrice(double);
};
PropertyList::PropertyList() :head_(NULL) {}
PropertyList::~PropertyList() {
	Property * p_home;
	p_home = head_;
	while (p_home != NULL) {
		delete p_home;
		p_home = p_home->GetNext();
	}
}
void PropertyList::Insert(Property*home) {
	home->SetNext(head_);
	head_ = home;
}
void PropertyList::InIt() {
	//Single Family House
	Insert(new SingleFamilyHouse("123 First Street, San Jose, CA ", 95112, 450000, 1956, 5000.0));
	Insert(new SingleFamilyHouse("787 Adam Street, San Jose, CA ", 95123, 750000, 1980, 7000.0));
	Insert(new SingleFamilyHouse("2580 Albert Ave., Sunnyvale, CA ", 94086, 1250000, 2010, 3000.0));
	Insert(new SingleFamilyHouse("3810 Mosher Dr., San Jose, CA ", 95184, 950000, 2000, 4000.0));
	Insert(new SingleFamilyHouse("1022 Banyan Ct, San Jose, CA ", 95131, 1250000, 2007, 3569.0));
	Insert(new SingleFamilyHouse("147 Florence St, Sunnyvale, CA ", 94086, 1198000, 1942, 5989.0));
	Insert(new SingleFamilyHouse("8477 Westwood Dr, Gilroy, CA ", 95020, 659000, 1974, 6600.0));
	Insert(new SingleFamilyHouse("8534 Otoole Ct, Gilroy, CA ", 95020, 829500, 1985, 6203.0));
	Insert(new SingleFamilyHouse("894 Shirley Ave, Sunnyvale, CA ", 94086, 1188000, 1950, 6200.0));
	Insert(new SingleFamilyHouse("200 Autumn St, La Honda, CA ", 94020, 692000, 1930, 7400.0));
	Insert(new SingleFamilyHouse("2150 Monterey Rd #68, San Jose, CA ", 95112, 169900, 1963, 1000.0));
	Insert(new SingleFamilyHouse("6283 Mahan Dr, San Jose, CA ", 95123, 958800, 1969, 1143.0));
	Insert(new SingleFamilyHouse("412 Avenida Palmas, San Jose, CA ", 95123, 999900, 1968, 7286.0));
	Insert(new SingleFamilyHouse("869 Channing Ave, Palo Alto, CA ", 94301, 2598000, 1910, 5917.0));
	Insert(new SingleFamilyHouse("1018 Harlan Ct, San Jose, CA ", 95129, 2000000, 1967, 9100.0));
	Insert(new SingleFamilyHouse("6711 Michele Way, San Jose, CA ", 95129, 3498000, 2018, 7864.0));
	//Townhouse
	Insert(new Townhouse("234 Hillview Ave. #245, Milpitas, CA ", 95023, 670000, 2010, 250.0));
	Insert(new Townhouse("126 Edwards St. #1278, Sunnyvale, CA ", 94087, 560000, 2008, 170.0));
	Insert(new Townhouse("2654 Ferguson Circle #305, Milpitas, CA ", 95035, 732000, 2010, 250.0));
	Insert(new Townhouse("1776 Camino Leonor, San Jose, CA ", 95131, 799000, 2008, 170.0));
	Insert(new Townhouse("1011 Giacomo Ln #6, San Jose, CA ", 95131, 1004710, 2018, 250.0));
	Insert(new Townhouse("410 Auburn Way #14, San Jose, CA ", 95129, 649000, 1970, 230.0));
	Insert(new Townhouse("1256 Copper Peak Ln, San Jose, CA ", 95120, 1150000, 1986, 270.0));
	Insert(new Townhouse("4685 Albany Cir #135, San Jose, CA ", 95129, 839000, 1982, 350.0));
	Insert(new Townhouse("234 Hillview Ave. #376, Milpitas, CA ", 95023, 820000, 2010, 250.0));
}
void PropertyList::ViewAllProperties() {
	Property * p_home;
	p_home = head_;
	while (p_home != NULL) {
		p_home->ShowPropertyInfo();
		p_home = p_home->GetNext();
	}
}
void PropertyList::SearchTownHouseByZipCode(int zip) {
	Townhouse * p_townhouse;
	Property * p_home;
	p_home = head_;
	int count_of_homes = 0;
	while (p_home != NULL) {
		p_townhouse = dynamic_cast<Townhouse*>(p_home);
		if (p_townhouse) {
			if (p_townhouse->GetZip() == zip) {
				p_townhouse->ShowPropertyInfo();
				count_of_homes++;
			}
		}
		p_home = p_home->GetNext();
	}
	if (count_of_homes == 0) {
		cout << "Sorry no Townhouse listing found for zip code " << zip << "!  Please check it back at a later time" << endl;
	}
}
void PropertyList::SearchByMaxPrice(double price) {
	Property * p_home;
	p_home = head_;
	while (p_home != NULL) {
		if (*p_home <= price) {
			p_home->ShowPropertyInfo();
		}
		p_home = p_home->GetNext();
	}
}
//Class MLSListings
class MLSListings {
private:
	PropertyList list_;
public:
	MLSListings();
	~MLSListings();
	void InIt();
	void Run();
	void ViewAllProperties();
	void SearchTownhouseByZipCode();
	void SearchByMaxPrice();
	void Quit();
};
MLSListings::MLSListings() {}
MLSListings::~MLSListings() {
	//no op
}
void MLSListings::InIt() {
	list_.InIt();
}
void MLSListings::Run() {
	int user_option = 1;
	while (user_option != 4) {
		cout << "1. View all properties" << endl;
		cout << "2. Search townhouse by zip code" << endl;
		cout << "3. Search properties by max price" << endl;
		cout << "4. Quit" << endl;
		cout << "Select an option (1-4): "; cin >> user_option;
		switch (user_option) {
		case 1:
			ViewAllProperties();
			break;
		case 2:
			SearchTownhouseByZipCode();
			break;
		case 3:
			SearchByMaxPrice();
			break;
		case 4:
			Quit();
			break;
		default:
			cout << "Please enter a valid option" << endl;
			break;
		}
	}
}
void MLSListings::ViewAllProperties() {
	list_.ViewAllProperties();
}
void MLSListings::SearchTownhouseByZipCode() {
	int search;
	cout << "-----Search Townhouse by Zip Code-----" << endl;
	cout << "Enter Zip Code: "; cin >> search;
	list_.SearchTownHouseByZipCode(search);
}
void MLSListings::SearchByMaxPrice() {
	double search;
	cout << "-----Search by Max Price-----" << endl;
	cout << "Enter Max Price: $"; cin >> search;
	list_.SearchByMaxPrice(search);
}
void MLSListings::Quit() {
	cout << "-----Quit-----" << endl;
	cout << "Thanks for browsing our listings. See you again!" << endl;
}
int main() {
	MLSListings * p_list = new MLSListings();
	p_list->InIt();
	p_list->Run();
	delete p_list;
	//_getch();
	return 0;
}