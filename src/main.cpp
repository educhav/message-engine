#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "engine.h"

using json = nlohmann::json;

class Message
{
    public:
        std::string message;
        long timestamp;
};

class Sender
{
    public:
        std::string name;
        std::vector<Message> messages;
};

void read_file(const int file_number, Sender* sender)
{

    std::ifstream stream("/home/eddie/code/c++/message-engine/messages/message_" 
            + std::to_string(file_number) + ".json");
    json file_data = json::parse(stream);
    auto messages = file_data["messages"];

    unsigned int participant_count = sizeof(Facebook::participants) / sizeof(Facebook::participants[0]);
    sender->messages = std::vector<Message>(messages.size() / participant_count);

    for (unsigned long i = 0; i < messages.size(); i++) 
    {
        if (messages.at(i)["content"] == nullptr)
        {
            continue;
        }
        std::string message = messages.at(i)["content"];
        std::string author = messages.at(i)["sender_name"];
        long timestamp = messages.at(i)["timestamp_ms"];

        if(author.compare(sender->name) == 0) 
        {
            Message msg = {message, timestamp};
            sender->messages.push_back(msg);
        }
    }
}

void read_all(Sender* sender) 
{
    for(unsigned int i = 0; i < Facebook::FILE_COUNT; i++) 
    {
    }
}

void display_page(std::string page) 
{
}

void display_page(std::string page, std::string delim)
{
}

int main(void) 
{
}
