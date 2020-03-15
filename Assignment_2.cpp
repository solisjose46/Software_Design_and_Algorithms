//=====================================================================================
// Name        : Index.cpp
// Author      : Jose Solis Salazar
// Version     : 1
// Copyright   : Copyright (C). CS Department Foothill College 2015. All rights reserved.
// Program purpose: Read in txt file data, parse and store data in objects. Array of pointers will conatin addresses for each object created.
//=====================================================================================
#include <iostream>
#include <fstream>
//#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
//global
typedef enum { pcNew, pcUsed, pcRefurbished, pcDefective } T_ProductCondition;
const int g_array_size = 512;
int generateProductID() {
	int id = 0;
	id = rand() % 10000;
	return id;
}
//InvntoryItem
class InventoryItem {
protected:
	string name_;
	int quantity_;
public:
	InventoryItem();
	InventoryItem(string, int);
	~InventoryItem();
	void set_name_and_quantity(string, int);
	void Display()const;
	string get_name()const;
	int get_quantity()const;
};
InventoryItem::InventoryItem():name_("Product"), quantity_(0) {}
InventoryItem::InventoryItem(string name, int quantity):name_(name), quantity_(quantity) {}
InventoryItem::~InventoryItem() {
	cout << " InventoryItem: " << name_ << " with " << quantity_ << " items destroyed ..." << endl;
}
void InventoryItem::set_name_and_quantity(string name, int quantity){
	name_ = name;
	quantity_ = quantity;
}
void InventoryItem::Display()const {
	cout << "Item: " << name_ << " Quanity: " << quantity_;
}
string InventoryItem::get_name()const {
	return name_;
}
int InventoryItem::get_quantity()const {
	return quantity_;
}
//Product
class Product : public InventoryItem {
private:
	int product_id_;
	double price_;
	T_ProductCondition condition_;
public:
	Product();
	Product(double, T_ProductCondition);
	~Product();
	//int get_id()const;
	double get_price()const;
	T_ProductCondition get_condition()const;
	char get_condition_letter()const;
	void Display()const;
};
Product::Product():product_id_(0), price_(0.00), InventoryItem() {}
Product::Product(double price, T_ProductCondition condition):product_id_(generateProductID()), price_(price), condition_(condition){}
Product::~Product() {
	cout << "Product: " << product_id_ << " priced $" << setprecision(6) << price_;
}
char Product::get_condition_letter()const{
	char condition_letter;
	switch (condition_) {
	case pcNew:
		condition_letter = 'N';
		break;
	case pcUsed:
		condition_letter = 'U';
		break;
	case pcRefurbished:
		condition_letter = 'R';
		break;
	case pcDefective:
		condition_letter = 'D';
		break;
	}
	return condition_letter;
}
void Product::Display()const{
	InventoryItem::Display();
	cout << " Product ID: " << product_id_ << " Price: " << setprecision(6) << price_ << " Condition: " << get_condition_letter() << endl;
}
//int Product::get_id()const{
//	return product_id_;
//}
double Product::get_price()const{
	return price_;
}
T_ProductCondition Product::get_condition()const{
	return condition_;
}
//InventorySystem
class InventorySystem {
private:
	string store_name_;
	int store_id_;
	InventoryItem * item_list_[g_array_size];
	int item_count_;
public:
	InventorySystem();
	InventorySystem(string, int);
	~InventorySystem();
	void BuildInventory();
	void ShowInventory()const;
	void ShowDefectInventory()const;
	void Terminate()const;
};
InventorySystem::InventorySystem():store_name_("Generic Store"), store_id_(0), item_count_(0){
	item_list_[g_array_size] = { NULL };
	srand(time(NULL)); //seed invoked
}
InventorySystem::InventorySystem(string name, int id):store_name_(name), store_id_(id), item_count_(0) {
	item_list_[g_array_size] = { NULL };
	srand(time(NULL)); //seed invoked
}
InventorySystem::~InventorySystem() {
	for (int i = 0; i < item_count_; i++) {
		InventoryItem * p_temp = item_list_[i];
		Product * p_product = static_cast<Product*>(p_temp);
		delete p_product;
	}
}
void InventorySystem::BuildInventory(){
	ifstream file("product_list.txt"); //assuming list is in the same folder as cpp
	string buffer;
	string product_name;
	int quantity;
	double price;
	char condition_letter;
	T_ProductCondition condition;
	if (!file) {
		cout << "ERROR: Failed to open input file\n";
		exit(-1);
	}
	else {
		while (getline(file, buffer, ';')) {
			product_name = buffer;

			getline(file, buffer, ';');
			quantity = stoi(buffer);

			getline(file, buffer, ';');
			price = atof(buffer.c_str());

			getline(file, buffer, '\n');
			condition_letter = buffer[0];

			switch (condition_letter) {
			case 'N':
				condition = pcNew;
				break;
			case 'U':
				condition = pcUsed;
				break;
			case 'R':
				condition = pcRefurbished;
				break;
			case 'D':
				condition = pcDefective;
				break;
			}	//memory dynamically allocated for a product object instantiated w/ non default constructor
				item_list_[item_count_] = new Product(price, condition);
				Product * p_product = static_cast<Product*>(item_list_[item_count_]); //InventoryItem pointer downcasted to product
				p_product->set_name_and_quantity(product_name, quantity);
				item_list_[item_count_] = p_product;
				++item_count_;
		}
	}
}
void InventorySystem::ShowInventory()const{
	for (int i = 0; i < item_count_; i++) {
		InventoryItem * p_temp = item_list_[i];
		Product * p_product = static_cast<Product*>(p_temp);
		p_product->Display();
	}
}
void InventorySystem::ShowDefectInventory()const{
	T_ProductCondition condition;
	for (int i = 0; i < item_count_; i++) {
		InventoryItem * p_temp = item_list_[i];
		Product * p_product = static_cast<Product*>(p_temp);
		condition = p_product->get_condition();
		if (condition == pcDefective) {
			p_product->Display();
		}
	}
}
void InventorySystem::Terminate()const{
	string buffer;
	string product_name;
	int quantity;
	double price;
	char condition;
	//int id;

	ofstream fileout("despacito.txt"); //writes to a file called despacito.txt to same folder this cpp file is in
	for (int i = 0; i < item_count_; i++) {
		InventoryItem * p_temp = item_list_[i];
		Product * p_product = static_cast<Product*>(p_temp);

		product_name = p_product->get_name();
		quantity = p_product->get_quantity();
		price = p_product->get_price();
		condition = p_product->get_condition_letter();
		//id = p_product->get_id();

		fileout << product_name << ';' << quantity << ';' << setprecision(6) << price << ';' << condition << endl;
	}
	fileout.close();
}
int main() {
	string store = "Circuit City";
	int store_id = 1234;
	InventorySystem * p_InventorySystem = new InventorySystem(store, store_id);
	p_InventorySystem->BuildInventory();
	p_InventorySystem->ShowInventory();
	p_InventorySystem->ShowDefectInventory();
	p_InventorySystem->Terminate();
	delete p_InventorySystem;

	//_getch();
	return 0;
}