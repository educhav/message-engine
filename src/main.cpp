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
        case 'b':
        {
            for (unsigned int i = 0; i < Facebook::PARTICIPANT_COUNT; i++) 
            {
                Sender sender = {Facebook::PARTICIPANTS[i], std::vector<Message>()};
                write_sender(&sender);
            }
        }
        case 'F':
        {
            reformat_json();
        }
    }
}
