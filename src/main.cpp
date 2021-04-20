#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <nlohmann/json.hpp>

#include "engine.cpp"

using json = nlohmann::json;
using Clock = std::chrono::high_resolution_clock;

int main(const int argc, const char* argv[]) 
{
    switch(argv[1][0])
    {
        case 'b':
        {
            auto start = Clock::now();
            for (unsigned int i = 0; i < Facebook::PARTICIPANT_COUNT; i++) 
            {
                Sender sender = {Facebook::PARTICIPANTS[i], std::vector<Message>()};
                write_sender(&sender);
            }
            auto end = Clock::now();
            std::chrono::duration<double, std::milli> ms_double = end - start;
            std::cout << "read_all() - all participants: " << (float)ms_double.count() / 1000 << "s\n";
            break;
        }
        case 'F':
        {
            reformat_json();
        }
    }
}
