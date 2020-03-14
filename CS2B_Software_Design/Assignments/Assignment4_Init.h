/**STL containers should come first
should go containers -> iterators
wtf is an iterator????
why is exception taught so late
**/
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
	voice_message = new VoiceMessage();//VoiceMessage
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