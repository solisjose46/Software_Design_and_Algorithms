//=====================================================================================
// Name        : Assignment 1
// Author      : Jose Solis Salazar
// Date        : 10/7/18
// Version     : 2
// Copyright   : Copyright (C). CS Department Foothill College 2015. All rights reserved.
// Program purpose: Illustration of variables and their memory addresses                                   

// Revisions history: (10/5/18/Jose Solis Salazar/added revion history)
//=====================================================================================

#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>

using namespace std;

//Global Var
const int g_array_size = 8;
//Classes here
class Movie {
private:
	string movie_name_;
	double ticket_price_;
	int seats_available_;

public:
	Movie();//Default constructor
	Movie(string, double, int);//Constructor w/ parameters
	~Movie();//Destructor
	void set_movie_name(string); //mutators
	double set_purchase_ticket(int); 
	void set_ticket_price(double);
	void set_seats_available(int);
	void get_movie_name_ticket_price_seats()const; //accessors //aka display
	string get_movie_name()const;
};
class MovieTicketMaster {
private:
	string theater_name_;
	string theater_location_;
	Movie movies[g_array_size];
public:
	MovieTicketMaster(); //default constructor
	MovieTicketMaster(string, string); //Contructor w/ parameters
	~MovieTicketMaster(); //destructor
	void set_movies(); //Mutators //aka InIt
	void ViewMovies(); //Regular functions
	void SearchMovie();
	Movie * FindMovie(string);
	void PurchaseTicket();
	void Run(); 
	void Menu()const; //accessor
};
string Movie::get_movie_name()const {
	return movie_name_;
}
//Movie Defintion here
Movie::Movie() {
	movie_name_ = "Fast7";
	ticket_price_ = NULL;
	seats_available_ = NULL;
}
Movie::Movie(string name, double price, int seats) {
	movie_name_ = name;
	ticket_price_ = price;
	seats_available_ = seats;
}
Movie::~Movie() {
	cout << movie_name_ << " is no longer showing..." << endl;
}
void Movie::set_movie_name(string name) {
	movie_name_ = name;
}
double Movie::set_purchase_ticket(int tickets) {
	double total_cost;
	if (tickets > seats_available_) {
		return -1; //tickets user wants to purchase exceeds seats avail.
	}
	else {
		total_cost = tickets * ticket_price_; //calculates total cost of purchase
		seats_available_ = seats_available_ - tickets; //subtracts number of tickets to seats availiable
		return total_cost; //the cost is returned
	}
}
void Movie::set_ticket_price(double price) {
	ticket_price_ = price;
}
void Movie::set_seats_available(int seats) {
	seats_available_ = seats;
}
void Movie::get_movie_name_ticket_price_seats()const {
	cout << "Movie: " << movie_name_ << ", Ticket Price: $" << ticket_price_ << ", Seats Available: " << seats_available_ << endl;
}
//MovieTicketMaster Defintion here
MovieTicketMaster::MovieTicketMaster() {
	//Theater_Name = "Harkins";
	//Theater_Location = "123 fake street";
	//no-op but defined 
}
MovieTicketMaster::MovieTicketMaster(string movie_name, string location) {
	theater_name_ = movie_name; //initializes private member w/ parameter
	theater_location_ = location; //initializes private member w/ parameter
}
MovieTicketMaster::~MovieTicketMaster(){
	cout << "Theater " << theater_name_ << " at " << theater_location_ << " has been closed.." << endl; //cout statemnt when object is destroyed
}
void MovieTicketMaster::set_movies() {
	string movie_names[g_array_size] = {
		"Black Mass", "The Visit", "Mission Impossible - Rougue Nation", "Straight Outta Compton",
		"No Escape", "Maze Runner: Scorch Trials", "Everest", "War Room"
	}; //list of movies
	double prices[g_array_size] = {
		6.99, 5.65, 7.03, 5.55, 6.01, 5.99, 6.98, 5.59
	}; //list of prices
	int seats[g_array_size] = {
		20, 25, 18, 15, 19, 16, 20, 23
	}; //list of seats availiable
	Movie* p_movies = NULL;
	p_movies = &movies[0]; //points to first element of movie array of class Movie
	string* p_movie_names = &movie_names[0]; //points to first element of movie names array
	double* p_prices = &prices[0]; //points to first element of prices array
	int* p_seats = &seats[0]; //points to first element of seats array
	
	for(int i = 0; i < 8; i++) {
		p_movies->set_movie_name(*p_movie_names); //using arrow operator to access set movie function and passing derefrenced pointer(contents) as parameter 
		p_movies->set_ticket_price(*p_prices); //using arrow operator to access set purchase ticket function and passing derefrenced pointer(contents) as parameter
		p_movies->set_seats_available(*p_seats); //using arrow operator to access set seats avail. function and passing derefrenced pointer(contents) as parameter
		p_movies++; //incremnts where pointer is pointing by 1
		p_movie_names++; //incremnts where pointer is pointing by 1
		p_seats++; //incremnts where pointer is pointing by 1
		p_prices++; //incremnts where pointer is pointing by 1
	}
}
void MovieTicketMaster::ViewMovies() {
	Movie *p_movies = &movies[0]; //points to first element in the Movie array
	for (int i = 0; i < 8; i++) {
		p_movies->get_movie_name_ticket_price_seats(); //using arrow operator to access the display function
		p_movies++; //increments where the pointer is pointing
	}
}
void MovieTicketMaster::SearchMovie() {
	string search; //The name of movie the user is searching for
	Movie *p_result = NULL; //will be used to point at the location of movie searched fors
	cout << "Enter name of movie: " << endl;
	cin.ignore();
	getline(cin, search);
	p_result = FindMovie(search); //value returned will be the address of the movie user was looking for or NULL
	if (p_result == NULL) {
		cout << "Error: Sorry, Movie Not Found." << endl; //if the pointer returned is null then movie user was searching for does not exist
	}
	else {
		p_result->get_movie_name_ticket_price_seats(); //arrow operator used to access get movie name function
	}
}
Movie * MovieTicketMaster::FindMovie(string search) {
	Movie *p_movies = &movies[0]; //points to first element of movie array
	for (int i = 0; i < 8; i++) { //using linear search to find movie user is searching for
		string compare = p_movies->get_movie_name(); //compare is intialized to movie name of whatever element it is pointing to
		if (compare == search) {
			return p_movies; //returns address of movie the user was searching for
		}
		p_movies++; //pponter is incremented by one
	}
	return NULL; //returns NULL of movie is not found
}
void MovieTicketMaster::PurchaseTicket() {
	string movie_name;
	int nuumber_of_tickets;
	double purchased;
	Movie *p_movie = NULL;
	cout << "Enter Name of Movie you would like to view" << endl;
	cin.ignore();
	getline(cin, movie_name);
	p_movie = FindMovie(movie_name); //points to the movie the user is searching for or is NULL if not found
	if (p_movie == NULL) {
		cout << "Error: Sorry, movie not found" << endl; //the movie user was searching for was not found
	}
	else {
		cout << "Enter number of tickets you would like to purchase" << endl; //movie is found, proceeds to purchase
		cin >> nuumber_of_tickets;
		while (nuumber_of_tickets < 0) { //checks for validity
			cout << "Enter number of tickets you would like to purchase" << endl;
			cin >> nuumber_of_tickets;
		}
		purchased = p_movie->set_purchase_ticket(nuumber_of_tickets);
		if (purchased == -1) {
			cout << "The show has been sold out or not enough tickets available per your request." << endl;
		}
		else {
			cout << "Your total is: $" << setprecision(4) << purchased << endl;
		}
	}
}
void MovieTicketMaster::Run() {
	int user_choice;
	do {
		Menu(); //dispalys menu
		cin >> user_choice;
		while (user_choice > 4 || user_choice < 1) {
			cout << "Enter A Valid Choice Please" << endl;
			cin >> user_choice;
			cout << endl; //checks for validity
		}
		if (user_choice == 1) {
			ViewMovies();
		}
		if (user_choice == 2) {
			SearchMovie();
		}
		if (user_choice == 3) {
			PurchaseTicket();
		}
	} while (user_choice != 4); //exists program if 4 is choosen
}
void MovieTicketMaster::Menu()const {
	cout << "\t\tMOVIE TICKET MASTER" << endl;
	cout << "\tTheater: " << theater_name_ << " at " << theater_location_ << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "Coming Soon: The Avengers 29\tAnother Bad RomCom\tWolverine, yes hes back" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "1. View All Movies" << endl;
	cout << "2. Search A Movie" << endl;
	cout << "3. Purchase A Ticket" << endl;
	cout << "4. Quit" << endl;
}
//Main here
int main() {
	MovieTicketMaster Main("Harkins", "321 Real Street"); //objects created w/ parameters passed
	MovieTicketMaster* p_Main = &Main; //pointer points to obeject created above
	p_Main->set_movies(); //Movie array is fully loaded
	p_Main->Run(); //starts the program
	p_Main->~MovieTicketMaster(); //object destroyed
	_getch();
	return 0;
}