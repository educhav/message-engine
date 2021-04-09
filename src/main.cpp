#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
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

    std::ifstream stream(Facebook::MESSAGE_DIRECTORY + std::to_string(file_number) + ".json");
    json file_data = json::parse(stream);
    auto messages = file_data["messages"];

    if (sender->messages.size() == 0) 
    {
        sender->messages = std::vector<Message>(messages.size() / Facebook::PARTICIPANT_COUNT);
    }

    for (unsigned long i = 0; i < messages.size(); i++) 
    {
        if (messages.at(i)["content"] == nullptr || 
                messages.at(i)["content"] == "")
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
    for(unsigned int i = 1; i <= Facebook::FILE_COUNT; i++) 
    {
        read_file(i, sender);
    }
}

int main(int argc, char* argv[]) 
{
    switch(argv[1][0])
    {
        case 'r':
            for (unsigned int i = 0; i < Facebook::PARTICIPANT_COUNT; i++) 
            {
                std::string first_name = Facebook::PARTICIPANTS[i].compare("JJ Joseph") ? 
                    Facebook::PARTICIPANTS[i].substr(0, Facebook::PARTICIPANTS[i].find(" "))
                    : "JJJ";
                Sender sender = {Facebook::PARTICIPANTS[i], std::vector<Message>()};
                read_all(&sender);
                std::ofstream file{Facebook::RAW_DIRECTORY + first_name + ".txt"};
                for (Message m : sender.messages)
                {
                    if (m.message != "") 
                    {
                        file << m.message << "|?|?|" << m.timestamp << std::endl;
                    }
                }
            }
            break;
        case 't': 
            Sender sender = {"Samuel Adams", std::vector<Message>()};
            read_all(&sender);
            for(Message m : sender.messages)
            {
                std::cout << m.message << std::endl;
            }
    }
}
