#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "var.h"

using json = nlohmann::json;

void read_file(const int file_number, Sender* sender, const bool write_to_file)
{
    std::ifstream stream(Facebook::MESSAGE_DIRECTORY + std::to_string(file_number) + ".json");
    json file_data = json::parse(stream);
    auto messages = file_data["messages"];

    if (sender->messages.size() == 0) 
    {
        sender->messages = std::vector<Message>(messages.size() / Facebook::PARTICIPANT_COUNT);
        /* sender->messages = std::vector<Message>(Facebook::AVG_LINES); */
        /* sender->messages = std::vector<Message>(50000); */
    }

    std::string first_name = sender->name.compare("JJ Joseph") ? 
        sender->name.substr(0, sender->name.find(" ")) : "JJJ";
    std::ofstream file{Facebook::RAW_DIRECTORY + first_name + ".txt", std::ios_base::app};

    for (unsigned int i = 0; i < messages.size(); i++) 
    {
        if (messages.at(i)["content"] == nullptr)
        {
            continue;
        }
        std::string message = messages.at(i)["content"];
        std::string author = messages.at(i)["sender_name"];
        long timestamp = messages.at(i)["timestamp_ms"];

        if(author.compare(sender->name) == 0 && message != "") 
        {
            Message msg = {message, timestamp};
            sender->messages.push_back(msg);
            if (write_to_file)
            {
                std::string formatted = msg.message + "|?|?|" + std::to_string(msg.timestamp) + "\n";
                file << formatted;
                /* file.write(formatted.c_str(), formatted.size()); */
            }
        }
    }
    file.close();
    stream.close();
}

void read_all(Sender* sender, bool write_to_file) 
{
    for(unsigned int i = 1; i <= Facebook::FILE_COUNT; i++) 
    {
        read_file(i, sender, write_to_file);
    }
}
