#include<iostream>

namespace Facebook {
    const std::string PARTICIPANTS[] = {"Eddie Chavez", "Degan Nestrichal", "JJ Joseph", 
                                        "Samuel Adams", "Austin Medina", "Emma Taylor",
                                        "J Cole Patt", "Elijah Parker", "Maci Marckx", 
                                        "Christopher Catunao", "Chloe Cumberworth", 
                                        "Berto Medina", "Valerie Kaley", "Dolly Saphire", 
                                        "Caleb Rondeau","Rande Plewka", "Lexi Fergelic", 
                                        "Drake Fox", "JJ San Nicolas"};
    const unsigned int PARTICIPANT_COUNT = sizeof(PARTICIPANTS) / sizeof(PARTICIPANTS[0]);
    const std::string FILTERED[] = {"joined the group chat."};

    const std::string MESSAGE_DIRECTORY = "/home/eddie/code/c++/message-engine/messages/message_";
    const std::string RAW_DIRECTORY = "/home/eddie/code/c++/message-engine/raw/";

    const int FILE_COUNT = 21;
}
