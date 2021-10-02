#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "constants.h"

using json = nlohmann::json;

void write_sender(Sender* sender)
{
    std::ifstream stream(Facebook::MESSAGE_DIRECTORY + "full.json");
    json file_data = json::parse(stream);
    auto messages = file_data["messages"];

    sender->messages = std::vector<Message>(messages.size() / Facebook::PARTICIPANT_COUNT);

    std::string first_name = sender->name.compare("JJ Joseph") ? 
        sender->name.substr(0, sender->name.find(" ")) : "JJJ";
    std::ofstream writer{Facebook::RAW_DIRECTORY + first_name + ".json", std::ios_base::app};
    writer << "{\n\"messages\": [\n";
    std::string delim = "";

    for (uint32_t i = 0; i < messages.size(); i++) 
    {
        std::string author = messages.at(i)["sender_name"];
        if(!author.compare(sender->name))
        {
            Message msg = { messages.at(i)["content"], 
                            messages.at(i)["sender_name"], 
                            messages.at(i)["timestamp_ms"], 
                            messages.at(i)["index_number"]  };
            sender->messages.push_back(msg);
            json j = json{{"sender_name", messages.at(i)["sender_name"]}, 
                {"content", messages.at(i)["content"]}, {"timestamp_ms", messages.at(i)["timestamp_ms"]}, 
                {"index_number", messages.at(i)["index_number"]}};
            writer << delim << j.dump() << "\n";
            delim = ",";
        }
    }
    writer << "]\n}";
    writer.close();
    stream.close();
}

void reformat_json() 
{
    int global_count = 0;
    std::string delim = "";
    std::ofstream writer(Facebook::MESSAGE_DIRECTORY + "full.json", std::ios_base::app);
    writer << "{\n\"messages\": [\n";
    for (uint32_t i = Facebook::FILE_COUNT; i > 0; i--)
    {
        std::ifstream stream(Facebook::MESSAGE_DIRECTORY + 
                std::to_string(i) + ".json");
        json file_data = json::parse(stream);
        auto messages = file_data["messages"];
        for(long int i = messages.size() - 1; i >= 0; i--)
        {
            if (messages.at(i)["content"] != nullptr && messages.at(i)["content"] != "")
            {
                json j = json{{"sender_name", messages.at(i)["sender_name"]}, 
                    {"content", messages.at(i)["content"]}, {"timestamp_ms", messages.at(i)["timestamp_ms"]}, 
                    {"index_number", global_count}};
                writer << delim << j.dump() << "\n";
                delim = ",";
                global_count++;
            }
        }
        stream.close();
    }
    writer << "]\n}";
    writer.close();
}
