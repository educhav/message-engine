#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "engine.cpp"

using json = nlohmann::json;

int main(const int argc, const char* argv[]) 
{
    switch(argv[1][0])
    {
        case 'r':
            for (unsigned int i = 0; i < Facebook::PARTICIPANT_COUNT; i++) 
            {
                Sender sender = {Facebook::PARTICIPANTS[i], std::vector<Message>()};
                read_all(&sender, true);
            }
            break;
        case 't': 
            Sender sender = {"Samuel Adams", std::vector<Message>()};
            read_all(&sender, true);
            for(Message m : sender.messages)
            {
                std::cout << m.message << std::endl;
            }
    }
}
