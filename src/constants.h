#include<iostream>
#include<vector>

class Message
{
    public:
        std::string message;
        std::string author;
        long timestamp;
        long index;
};

class Sender
{
    public:
        std::string name;
        std::vector<Message> messages;
};

namespace Facebook 
{
    const std::string PARTICIPANTS[] = {"Eddie Chavez", "Degan Nestrichal", "JJ Joseph", 
                                        "Samuel Adams", "Austin Medina", "Emma Taylor",
                                        "J Cole Patt", "Elijah Parker", "Maci Marckx", 
                                        "Christopher Catunao", "Chloe Cumberworth", 
                                        "Berto Medina", "Valerie Kaley", "Dolly Saphire", 
                                        "Caleb Rondeau","Rande Plewka", "Lexi Fergelic", 
                                        "Drake Fox", "JJ San Nicolas", "Jacob Willke",
                                        "Jonathan Franks"};
    const unsigned int PARTICIPANT_COUNT = sizeof(PARTICIPANTS) / sizeof(PARTICIPANTS[0]);
    const std::string FILTERED[] = {"joined the group chat."};

    const std::string MESSAGE_DIRECTORY = "/home/eddie/code/c++/message-engine/messages/message_";
    const std::string RAW_DIRECTORY = "/home/eddie/code/c++/message-engine/raw/";

    const int FILE_COUNT = 21;
    /* Calculated based on avg. amount of lines between ppl to 
     * initialize vector with proper size to prevent constant O(n) resizing */
    const int AVG_LINES = 9350;
}
