//=====================================================================================
// Name        : Index.cpp
// Author      : Jose Solis Salazar
// Copyright   : Copyright (C). CS Department Foothill College 2015. All rights reserved.
// Program purpose: For use by customer service to search and edit customer's phone accounts.
//=====================================================================================

#include <iostream>
#include <string>
//#include <conio.h>
#include <vector>
#include <map>
#include <exception>
#include <iomanip>
#include <fstream>

//everything is functioning, start maps
using namespace std;
//Class Message
class Message {
private:
	string from_, to_;
public:
	Message();
	Message(string, string);
	bool operator==(const Message&);
	string GetFrom(); //GetFrom and GetTo used stricly to detect a message instantiated by default constructor ex: new TextMessage()
	string GetTo();
	virtual double ComputeCharge()const = 0;
	virtual ~Message() = 0;
};
Message::Message() :from_("N/A"), to_("N/A") {}
Message::Message(string from, string to) : from_(from), to_(to) {}
bool Message::operator==(const Message & obj) {
	if (this->from_ == obj.from_ && this->to_ == obj.to_) {
		return true;
	}
	else {
		return false;
	}
}
string Message::GetFrom() {
	return from_;
}
string Message::GetTo() {
	return to_;
}
double Message::ComputeCharge()const {
	return 0.0;
}
Message::~Message() {
	//no op
}
//class TextMessage
class TextMessage : public Message {
private:
	string text_message_;
public:
	TextMessage();
	TextMessage(string, string, string);
	friend ostream & operator<<(ostream&, TextMessage obj);
	virtual double ComputeCharge()const;
	virtual ~TextMessage();
};
TextMessage::TextMessage() :text_message_("N/A"), Message() {}
TextMessage::TextMessage(string from, string to, string text) : Message(from, to), text_message_(text) {}
ostream & operator<<(ostream &out, TextMessage obj) {
	out << "From: " << obj.GetFrom() << " To: " << obj.GetTo() << " Message: " << obj.text_message_ << endl;
	return out;
}
double TextMessage::ComputeCharge() const {
	double cost = 0.2;
	return cost;
}
TextMessage::~TextMessage() {
	//no op
}
//class VoiceMessage
class VoiceMessage : public Message {
private:
	int time_of_voice_; //in seconds
public:
	VoiceMessage();
	VoiceMessage(string, string, int);
	friend ostream & operator<<(ostream&, VoiceMessage obj);
	virtual double ComputeCharge()const;
	virtual ~VoiceMessage();
};
VoiceMessage::VoiceMessage() :time_of_voice_(0), Message() {}
VoiceMessage::VoiceMessage(string from, string to, int time) : Message(from, to), time_of_voice_(time) {}
ostream & operator<<(ostream &out, VoiceMessage obj) {
	out << "From: " << obj.GetFrom() << " To: " << obj.GetTo() << " Length of Message: " << obj.time_of_voice_ << " seconds" << endl;
	return out;
}
double VoiceMessage::ComputeCharge()const {
	double cost = time_of_voice_ * 0.015;
	return cost;
}
VoiceMessage::~VoiceMessage() {
	//no op
}
//class MediaMessage
class MediaMessage : public Message {
private:
	int media_size_; //in MB
public:
	MediaMessage();
	MediaMessage(string, string, int);
	friend ostream & operator<<(ostream&, MediaMessage obj);
	virtual double ComputeCharge()const;
	virtual ~MediaMessage();
};
MediaMessage::MediaMessage() :media_size_(0), Message() {}
MediaMessage::MediaMessage(string from, string to, int size) : Message(from, to), media_size_(size) {}
ostream & operator<<(ostream &out, MediaMessage obj) {
	out << "From: " << obj.GetFrom() << " To: " << obj.GetTo() << " Media Size: " << obj.media_size_ << " MB" << endl;
	return out;
}
double MediaMessage::ComputeCharge()const {
	double cost = media_size_ * 0.1;
	return cost;
}
MediaMessage::~MediaMessage() {
	//no op
}
//class SmartCarrier
class SmartCarrier {
private:
	string carrier_name_;
	map <string, vector<Message*>> map_of_accounts_;
	void Menu();
	int Choice();
	void ListAll();
	void SearchMessage();
	void EraseMessage();
	void DisconnectAccount();
	void TextOut();
public:
	SmartCarrier();
	SmartCarrier(string, map <string, vector<Message*>>&);
	~SmartCarrier();
	string GetCarrierName()const;
	void SetCarrierName(string);
	map <string, vector<Message*>> & GetMap();
	void Init();
	void StartService();
};
SmartCarrier::SmartCarrier() :carrier_name_("Cingular") { map_of_accounts_["N/A"].push_back(NULL); }
SmartCarrier::SmartCarrier(string name, map <string, vector<Message*>>& account_map) : carrier_name_(name), map_of_accounts_(account_map) {}
SmartCarrier::~SmartCarrier() {
	map <string, vector<Message*>>::iterator map_iterator;
	vector <Message*>::iterator vector_iterator;

	for (map_iterator = map_of_accounts_.begin(); map_iterator != map_of_accounts_.end(); map_iterator++) {
		for (vector_iterator = map_iterator->second.begin(); vector_iterator != map_iterator->second.end(); vector_iterator++) {
			delete *vector_iterator;
		}
	}
	map_of_accounts_.clear();
}
string SmartCarrier::GetCarrierName()const {
	return carrier_name_;
}
void SmartCarrier::SetCarrierName(string name) {
	carrier_name_ = name;
}
map <string, vector<Message*>> & SmartCarrier::GetMap() {
	map <string, vector<Message*>> & map_to_return = map_of_accounts_;
	return map_to_return;
}
void SmartCarrier::Init() {
	//650-267-1289
	//Text: 1, Voice Message: 1, Media Message: 1
	Message * text_message = new TextMessage("650-267-1289", "408-235-1500", "Do you want to learn Java"); //TextMessage
	map_of_accounts_["650-267-1289"].push_back(text_message);
	Message * voice_message = new VoiceMessage("650-267-1289", "408-111-2222", 120); //VoiceMessage
	map_of_accounts_["650-267-1289"].push_back(voice_message);
	Message *   media_message = new MediaMessage("650-267-1289", "310-777-8888", 25); //MediaMessage
	map_of_accounts_["650-267-1289"].push_back(media_message);
	//408-235-1500
	//Text: 3, Voice Message: 3, Media Message: 4
	text_message = new TextMessage("408-235-1500", "650-267-1289", "I like Java but C++ is better");//TextMessage
	map_of_accounts_["408-235-1500"].push_back(text_message);
	text_message = new TextMessage("408-235-1500", "650-781-7900", "**The funniest joke ever told from Monty Python**");
	map_of_accounts_["408-235-1500"].push_back(text_message);
	text_message = new TextMessage("408-235-1500", "408-111-2222", "This is your Uber, I'm outside");
	map_of_accounts_["408-235-1500"].push_back(text_message);
	voice_message = new VoiceMessage("408-235-1500", "650-267-1289", 30);//VoiceMessage
	map_of_accounts_["408-235-1500"].push_back(voice_message);
	voice_message = new VoiceMessage("408-235-1500", "408-111-2222", 50);
	map_of_accounts_["408-235-1500"].push_back(voice_message);
	voice_message = new VoiceMessage("408-235-1500", "650-781-7900", 52);
	map_of_accounts_["408-235-1500"].push_back(voice_message);
	media_message = new MediaMessage("408-235-1500", "650-280-1200", 5); //MediaMessage
	map_of_accounts_["408-235-1500"].push_back(media_message);
	media_message = new MediaMessage("408-235-1500", "650-267-1289", 10);
	map_of_accounts_["408-235-1500"].push_back(media_message);
	media_message = new MediaMessage("408-235-1500", "408-111-2222", 15);
	map_of_accounts_["408-235-1500"].push_back(media_message);
	media_message = new MediaMessage("408-235-1500", "310-777-8888", 20);
	map_of_accounts_["408-235-1500"].push_back(media_message);
	//650-781-7900
	//Text: 2, Voice Message: 0, Media Message: 3
	text_message = new TextMessage("650-781-7900", "408-235-1500", "I am laughing out loud, this is very amusing hahaha you've done it again");//TextMessage
	map_of_accounts_["650-781-7900"].push_back(text_message);
	text_message = new TextMessage("650-781-7900", "310-777-8888", "Have you seen cheddar Bob?");
	map_of_accounts_["650-781-7900"].push_back(text_message);
	voice_message = new VoiceMessage();//VoiceMessage //default constructor called, from = N/A, user did not make a message of this type
	map_of_accounts_["650-781-7900"].push_back(voice_message);
	media_message = new MediaMessage("650-781-7900", "408-235-1500", 10);//MediaMessage
	map_of_accounts_["650-781-7900"].push_back(media_message);
	media_message = new MediaMessage("650-781-7900", "310-777-8888", 12);
	map_of_accounts_["650-781-7900"].push_back(media_message);
	media_message = new MediaMessage("650-781-7900", "408-111-2222", 5);
	map_of_accounts_["650-781-7900"].push_back(media_message);
	//415-298-2162
	//Text: 0, Voice Message: 1, Media Message: 1
	text_message = new TextMessage();//TextMessage //default constructed called sent and from = N/A, if from and to = N/A, user did not make a message of this type
	map_of_accounts_["415-298-2162"].push_back(text_message);
	voice_message = new VoiceMessage("415-298-2162", "650-781-7900", 200);//VoiceMessage
	map_of_accounts_["415-298-2162"].push_back(voice_message);
	media_message = new MediaMessage("415-298-2162", "650-267-1289", 13);//MediaMessage
	map_of_accounts_["415-298-2162"].push_back(media_message);
	//945-890-5913
	//Text: 0, Voice Message: 0, Media Message: 0
	text_message = new TextMessage();//TextMessage
	map_of_accounts_["945-890-5913"].push_back(text_message);
	voice_message = new VoiceMessage();//VoiceMessage
	map_of_accounts_["945-890-5913"].push_back(voice_message);
	media_message = new MediaMessage();//MediaMessage
	map_of_accounts_["945-890-5913"].push_back(media_message);
	//408-720-0012
	//Text: 1, Voice Message: 4, Media Message: 0
	text_message = new TextMessage("408-720-0012", "408-235-1500", "Can you walk the dogs?");//TextMessage
	map_of_accounts_["408-720-0012"].push_back(text_message);
	voice_message = new VoiceMessage("408-720-0012", "945-890-5913", 180);//VoiceMessage
	map_of_accounts_["408-720-0012"].push_back(voice_message);
	voice_message = new VoiceMessage("408-720-0012", "415-298-2162", 10);
	map_of_accounts_["408-720-0012"].push_back(voice_message);
	voice_message = new VoiceMessage("408-720-0012", "408-235-1500", 80);
	map_of_accounts_["408-720-0012"].push_back(voice_message);
	voice_message = new VoiceMessage("408-720-0012", "650-267-1289", 70);
	map_of_accounts_["408-720-0012"].push_back(voice_message);
	media_message = new MediaMessage();//MediaMessage
	map_of_accounts_["408-720-0012"].push_back(media_message);
	//650-230-9912
	//Text: 0, Voice Message: 0, Media Message: 3
	text_message = new TextMessage();//TextMessage
	map_of_accounts_["650-230-9912"].push_back(text_message);
	voice_message = new VoiceMessage();//VoiceMessage
	map_of_accounts_["650-230-9912"].push_back(voice_message);
	media_message = new MediaMessage("650-230-9912", "650-267-1289", 12);//MediaMessage
	map_of_accounts_["650-230-9912"].push_back(media_message);
	media_message = new MediaMessage("650-230-9912", "408-720-0012", 14);
	map_of_accounts_["650-230-9912"].push_back(media_message);
	media_message = new MediaMessage("650-230-9912", "945-890-5913", 10);
	map_of_accounts_["650-230-9912"].push_back(media_message);
	//408-462-7890
	//Text: 4, Voice Message: 2, Media Message: 3
	text_message = new TextMessage("408-462-7890", "408-235-1500", "do you think he'll curve the final???");//TextMessage
	map_of_accounts_["408-462-7890"].push_back(text_message);
	text_message = new TextMessage("408-462-7890", "650-781-7900", "Can you help me with my Calc?");
	map_of_accounts_["408-462-7890"].push_back(text_message);
	text_message = new TextMessage("408-462-7890", "310-290-1666", "LOL does not mean lots of love");
	map_of_accounts_["408-462-7890"].push_back(text_message);
	text_message = new TextMessage("408-462-7890", "415-902-9581", "Can I get the day off tomorrow?");
	map_of_accounts_["408-462-7890"].push_back(text_message);
	voice_message = new VoiceMessage("408-462-7890", "945-890-5913", 180);//VoiceMessage
	map_of_accounts_["408-462-7890"].push_back(voice_message);
	voice_message = new VoiceMessage("408-462-7890", "650-230-9912", 30);
	map_of_accounts_["408-462-7890"].push_back(voice_message);
	media_message = new MediaMessage("408-462-7890", "650-267-1289", 20);//MediaMessage
	map_of_accounts_["408-462-7890"].push_back(media_message);
	media_message = new MediaMessage("408-462-7890", "650-230-9912", 18);
	map_of_accounts_["408-462-7890"].push_back(media_message);
	media_message = new MediaMessage("408-462-7890", "945-890-5913", 11);
	map_of_accounts_["408-462-7890"].push_back(media_message);
	//415-902-9581
	//Text: 1, Voice Message: 2, Media Message: 2
	text_message = new TextMessage("415-902-9581", "310-290-1666", "I need you to come in early tomorrow");//TextMessage
	map_of_accounts_["415-902-9581"].push_back(text_message);
	voice_message = new VoiceMessage("415-902-9581", "310-290-1666", 100);//VoiceMessage
	map_of_accounts_["415-902-9581"].push_back(voice_message);
	voice_message = new VoiceMessage("415-902-9581", "408-462-7890", 110);
	map_of_accounts_["415-902-9581"].push_back(voice_message);
	media_message = new MediaMessage("415-902-9581", "310-290-1666", 10);//MediaMessage
	map_of_accounts_["415-902-9581"].push_back(media_message);
	media_message = new MediaMessage("415-902-9581", "408-462-7890", 8);
	map_of_accounts_["415-902-9581"].push_back(media_message);
	//310-290-1666
	//Text: 3, Voice Message: 0, Media Message: 0
	text_message = new TextMessage("310-290-1666", "415-902-9581", "I cant come in tomorrow, my cat is sick :(");//TextMessage
	map_of_accounts_["310-290-1666"].push_back(text_message);
	text_message = new TextMessage("310-290-1666", "408-462-7890", "I can't wait for Foo Fighters tomorrow!!!");
	map_of_accounts_["310-290-1666"].push_back(text_message);
	text_message = new TextMessage("310-290-1666", "480-426-7890", "LOL");
	map_of_accounts_["310-290-1666"].push_back(text_message);
	voice_message = new VoiceMessage();//VoiceMessage
	map_of_accounts_["310-290-1666"].push_back(voice_message);
	media_message = new MediaMessage();//MediaMessage
	map_of_accounts_["310-290-1666"].push_back(media_message);
}
void SmartCarrier::StartService() {
	int option;
	do {
		Menu();
		option = Choice();
		switch (option) {
		case 1:
			ListAll();
			break;
		case 2:
			SearchMessage();
			break;
		case 3:
			EraseMessage();
			break;
		case 4:
			DisconnectAccount();
			break;
		case 5:
			ListAll();
			cout << "Thank you for choosing FOOTHILL WIRELESS" << endl;
			TextOut();
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
	} while (option != 5);
}
void SmartCarrier::Menu() {
	cout << "\t\tFOOTHILL WIRELESS" << endl;
	cout << "\tMESSAGE UTILIZATION AND ACCOUNT ADMIN" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "1. List summary of message usages/charges for all accounts" << endl;
	cout << "2. Search a message from an account" << endl;
	cout << "3. Erase a message from an account " << endl;
	cout << "4. Disconnect an account" << endl;
	cout << "5. Quit" << endl;

}
int SmartCarrier::Choice() {
	int option;
	cin >> option;
	return option;
}
void SmartCarrier::ListAll() {
	map <string, vector<Message*>>::iterator map_iterator;
	vector <Message*>::iterator vector_iterator;
	TextMessage * p_text = NULL; VoiceMessage * p_voice = NULL; MediaMessage * p_media = NULL;
	int total_messages, text_count, voice_count, media_count;
	double total_cost;

	cout << "Phone Number\tTotal Messages\tText\tVoice\tMedia\tTotal Charges" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;
	for (map_iterator = map_of_accounts_.begin(); map_iterator != map_of_accounts_.end(); map_iterator++) {
		if (map_iterator->first != "N/A") { //To prevent printing of default objects
			cout << map_iterator->first << "\t";
			total_messages = 0; text_count = 0; voice_count = 0; media_count = 0; total_cost = 0.0;
			for (vector_iterator = map_iterator->second.begin(); vector_iterator != map_iterator->second.end(); vector_iterator++) {
				if ((*vector_iterator)->GetFrom() != "N/A") { //if a message's from = N/A, this means the user made no text/voice/media message
					p_text = dynamic_cast<TextMessage*>(*vector_iterator); p_voice = dynamic_cast<VoiceMessage*>(*vector_iterator); p_media = dynamic_cast<MediaMessage*>(*vector_iterator);
					if (p_text) {
						total_messages++;
						text_count++;
						total_cost = total_cost + (*vector_iterator)->ComputeCharge();
					}
					else if (p_voice) {
						total_messages++;
						voice_count++;
						total_cost = total_cost = total_cost + (*vector_iterator)->ComputeCharge();
					}
					else if (p_media)
					{
						total_messages++;
						media_count++;
						total_cost = total_cost = total_cost + (*vector_iterator)->ComputeCharge();
					}
				}
			}
			cout << total_messages << "\t\t" << text_count << "\t" << voice_count << "\t" << media_count << "\t" << "$" << setprecision(2) << fixed << total_cost << endl;
		}

	}
}
void SmartCarrier::SearchMessage() {
	map <string, vector<Message*>>::iterator map_iterator;
	vector <Message*>::iterator vector_iterator;
	string search_phone_number, search_from, search_to;
	TextMessage * p_text = NULL; VoiceMessage * p_voice = NULL; MediaMessage * p_media = NULL; Message * search_message = NULL;
	int message_type_option, message_count = 0;

	cout << "Enter Account(Phone Number): " << endl;
	cin >> search_phone_number;

	try {
		map_iterator = map_of_accounts_.find(search_phone_number);
		if (map_iterator == map_of_accounts_.end()) { //checks if account exists
			throw string("Sorry, account not found");
		}
		else {
			cout << "Choose Message Type: " << endl;
			cout << "\t1. Text 2. Voice 3. Media" << endl;
			cin >> message_type_option;
			vector_iterator = map_iterator->second.begin();
			switch (message_type_option) { // checks if there are messages of this type
			case 1: //Text
				for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
					p_text = dynamic_cast<TextMessage*>(*vector_iterator);
					if (p_text && (*vector_iterator)->GetFrom() != "N/A") { //if from = N/A, the user did not make a message of this type, just from default constructor
						message_count++;
					}
				}
				if (message_count == 0) {
					throw string("No messages of this type found");
				}
				break;
			case 2: //Voice
				for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
					p_voice = dynamic_cast<VoiceMessage*>(*vector_iterator);
					if (p_voice && (*vector_iterator)->GetFrom() != "N/A") { //if from = N/A, the user did not make a message of this type, just from default constructor
						message_count++;
					}
				}
				if (message_count == 0) {
					throw string("No messages of this type found");
				}
				break;
			case 3: //Media
				for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
					p_media = dynamic_cast<MediaMessage*>(*vector_iterator);
					if (p_media && (*vector_iterator)->GetFrom() != "N/A") { //if from = N/A, the user did not make a message of this type, just from default constructor
						message_count++;
					}
				}
				if (message_count == 0) {
					throw string("No messages of this type found");
				}
				break;
			default:
				throw string("Invalid Option");
				break;
			}
		}
		cout << "Enter Sender (from) : " << endl;
		cin >> search_from;
		cout << "Enter Reciever (to): " << endl;
		cin >> search_to;

		vector_iterator = map_iterator->second.begin();
		message_count = 0;
		switch (message_type_option) {//searches for message based on from and to, if found then print
		case 1:
			search_message = new TextMessage(search_from, search_to, "N/A");
			for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
				p_text = dynamic_cast<TextMessage*>(*vector_iterator);
				if (p_text && (*vector_iterator)->GetFrom() != "N/A") {
					if (*p_text == *search_message) { //== overloaded
						cout << *p_text << endl;
						message_count++;
					}
				}
			}
			if (message_count == 0) {
				delete search_message;
				throw string("Message with From: " + search_from + "and To: " + search_to + " not found.");
			}
			delete search_message;
			break;
		case 2:
			search_message = new VoiceMessage(search_from, search_to, 0);
			for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
				p_voice = dynamic_cast<VoiceMessage*>(*vector_iterator);
				if (p_voice && (*vector_iterator)->GetFrom() != "N/A") {
					if (*p_voice == *search_message) { //== overloaded
						cout << *p_voice << endl;
						message_count++;
					}
				}
			}
			if (message_count == 0) {
				delete search_message;
				throw string("Message with From: " + search_from + "and To: " + search_to + " not found.");
			}
			delete search_message;
			break;
		case 3:
			search_message = new MediaMessage(search_from, search_to, 0);
			for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
				p_media = dynamic_cast<MediaMessage*>(*vector_iterator);
				if (p_media && (*vector_iterator)->GetFrom() != "N/A") {
					if (*p_media == *search_message) { //== overloaded
						cout << *p_media << endl;
						message_count++;
					}
				}
			}
			if (message_count == 0) {
				delete search_message;
				throw string("Message with From: " + search_from + "and To: " + search_to + " not found.");
			}
			delete search_message;
			break;
		}
	}
	catch (string not_found) {
		cout << not_found << endl;
	}
}
void SmartCarrier::EraseMessage() {
	map <string, vector<Message*>>::iterator map_iterator;
	vector <Message*>::iterator vector_iterator;
	string search_phone_number, search_from, search_to;
	TextMessage * p_text = NULL; VoiceMessage * p_voice = NULL; MediaMessage * p_media = NULL; Message * search_message = NULL;
	int message_type_option, message_count = 0;

	cout << "Enter Account(Phone Number): " << endl;
	cin >> search_phone_number;

	try {
		map_iterator = map_of_accounts_.find(search_phone_number);
		if (map_iterator == map_of_accounts_.end()) { //checks if account exists
			throw string("Sorry, account not found");
		}
		else {
			cout << "Choose Message Type: " << endl;
			cout << "\t1. Text 2. Voice 3. Media" << endl;
			cin >> message_type_option;
			vector_iterator = map_iterator->second.begin();
			switch (message_type_option) { // checks if there are messages of this type
			case 1: //Text
				for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
					p_text = dynamic_cast<TextMessage*>(*vector_iterator);
					if (p_text && (*vector_iterator)->GetFrom() != "N/A") { //if from = N/A, the user did not make a message of this type, just from default constructor
						message_count++;
					}
				}
				if (message_count == 0) {
					throw string("No messages of this type found");
				}
				break;
			case 2: //Voice
				for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
					p_voice = dynamic_cast<VoiceMessage*>(*vector_iterator);
					if (p_voice && (*vector_iterator)->GetFrom() != "N/A") { //if from = N/A, the user did not make a message of this type, just from default constructor
						message_count++;
					}
				}
				if (message_count == 0) {
					throw string("No messages of this type found");
				}
				break;
			case 3: //Media
				for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
					p_media = dynamic_cast<MediaMessage*>(*vector_iterator);
					if (p_media && (*vector_iterator)->GetFrom() != "N/A") { //if from = N/A, the user did not make a message of this type, just from default constructor
						message_count++;
					}
				}
				if (message_count == 0) {
					throw string("No messages of this type found");
				}
				break;
			default:
				throw string("Invalid Option");
				break;
			}
		}
		cout << "Enter Sender (from) : " << endl;
		cin >> search_from;
		cout << "Enter Reciever (to): " << endl;
		cin >> search_to;

		vector_iterator = map_iterator->second.begin();
		message_count = 0;
		switch (message_type_option) {//searches for message based on from and to, if found then print
		case 1:
			search_message = new TextMessage(search_from, search_to, "N/A");
			for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
				p_text = dynamic_cast<TextMessage*>(*vector_iterator);
				if (p_text && (*vector_iterator)->GetFrom() != "N/A") {
					if (*p_text == *search_message) { //== overloaded
						delete *vector_iterator;
						map_of_accounts_.find(search_phone_number)->second.erase(map_iterator->second.begin() + message_count);
						cout << "Message Removed" << endl;
						message_count++;
						break;
					}
				}
			}
			if (message_count == 0) {
				delete search_message;
				throw string("Message with From: " + search_from + "and To: " + search_to + " not found.");
			}
			delete search_message;
			break;
		case 2:
			search_message = new VoiceMessage(search_from, search_to, 0);
			for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
				p_voice = dynamic_cast<VoiceMessage*>(*vector_iterator);
				if (p_voice && (*vector_iterator)->GetFrom() != "N/A") {
					if (*p_voice == *search_message) { //== overloaded
						delete *vector_iterator;
						map_of_accounts_.find(search_phone_number)->second.erase(map_iterator->second.begin() + message_count);
						cout << "Message Removed" << endl;
						message_count++;
						break;
					}
				}
			}
			if (message_count == 0) {
				delete search_message;
				throw string("Message with From: " + search_from + "and To: " + search_to + " not found.");
			}
			delete search_message;
			break;
		case 3:
			search_message = new MediaMessage(search_from, search_to, 0);
			for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
				p_media = dynamic_cast<MediaMessage*>(*vector_iterator);
				if (p_media && (*vector_iterator)->GetFrom() != "N/A") {
					if (*p_media == *search_message) { //== overloaded
						delete *vector_iterator;
						map_of_accounts_.find(search_phone_number)->second.erase(map_iterator->second.begin() + message_count);
						cout << "Message Removed" << endl;
						message_count++;
						break;
					}
				}
			}
			if (message_count == 0) {
				delete search_message;
				throw string("Message with From: " + search_from + "and To: " + search_to + " not found.");
			}
			delete search_message;
			break;
		}
	}
	catch (string not_found) {
		cout << not_found << endl;
	}
}
void SmartCarrier::DisconnectAccount() {
	string disconnect_account;
	map <string, vector<Message*>>::iterator map_iterator;
	vector <Message*>::iterator vector_iterator;
	cout << "Enter account (Phone Number) to be disconnected: " << endl;
	cin >> disconnect_account;
	map_iterator = map_of_accounts_.find(disconnect_account);
	try {
		if (map_iterator == map_of_accounts_.end()) {
			throw string("Sorry, account not found");
		}
		else {
			vector_iterator = map_iterator->second.begin();
			for (vector_iterator; vector_iterator != map_iterator->second.end(); vector_iterator++) {
				delete *vector_iterator;
			}
			map_iterator->second.clear(); //then clear vector
			map_of_accounts_.erase(disconnect_account);  //then remove this element from map
			cout << "Account removed " << endl;
		}
	}
	catch (string not_found) {
		cout << not_found << endl;
	}
}
void SmartCarrier::TextOut() {
	map <string, vector<Message*>>::iterator map_iterator;
	vector <Message*>::iterator vector_iterator;
	TextMessage * p_text = NULL; VoiceMessage * p_voice = NULL; MediaMessage * p_media = NULL;
	int total_messages, text_count, voice_count, media_count;
	double total_cost;
	ofstream fileout;
	fileout.open("FOOTHILL_WIRELESS.txt");

	fileout << "Phone Number\tTotal Messages\tText\tVoice\t\tMedia\tTotal Charges" << endl;
	fileout << "------------------------------------------------------------------------------------------" << endl;
	for (map_iterator = map_of_accounts_.begin(); map_iterator != map_of_accounts_.end(); map_iterator++) {
		if (map_iterator->first != "N/A") { //To prevent printing of default objects
			fileout << map_iterator->first << "\t";
			total_messages = 0; text_count = 0; voice_count = 0; media_count = 0; total_cost = 0.0;
			for (vector_iterator = map_iterator->second.begin(); vector_iterator != map_iterator->second.end(); vector_iterator++) {
				if ((*vector_iterator)->GetFrom() != "N/A") { //if a message's from = N/A, this means the user made no text/voice/media message
					p_text = dynamic_cast<TextMessage*>(*vector_iterator); p_voice = dynamic_cast<VoiceMessage*>(*vector_iterator); p_media = dynamic_cast<MediaMessage*>(*vector_iterator);
					if (p_text) {
						total_messages++;
						text_count++;
						total_cost = total_cost + (*vector_iterator)->ComputeCharge();
					}
					else if (p_voice) {
						total_messages++;
						voice_count++;
						total_cost = total_cost = total_cost + (*vector_iterator)->ComputeCharge();
					}
					else if (p_media)
					{
						total_messages++;
						media_count++;
						total_cost = total_cost = total_cost + (*vector_iterator)->ComputeCharge();
					}
				}
			}
			fileout << total_messages << "\t\t\t\t" << text_count << "\t\t\t" << voice_count << "\t\t\t" << media_count << "\t\t\t" << "$" << setprecision(2) << fixed << total_cost << endl;
		}
	}
	fileout.close();
}
int main() {

	SmartCarrier * Phone;
	Phone = new SmartCarrier(); //default constructor called, empty vector with key "N/A" in map
	Phone->Init();
	Phone->StartService();
	delete Phone;

	//_getch();
	return 0;
}