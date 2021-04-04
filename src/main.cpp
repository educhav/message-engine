#include<iostream>
#include<fstream>
#include<vector>
#include<nlohmann/json.hpp>

using json = nlohmann::json;

typedef struct 
{
    const std::string name;
    std::vector<std::string> messages;
    std::vector<int> timestamps;
} Person;

typedef struct
{
    
} Message;

void read_file(const int file_number) 
{
    std::ifstream stream("/home/eddie/code/c++/message-engine/messages/message_" + std::to_string(file_number) + ".json");
    json file_data = json::parse(stream);
    std::cout << file_data << std::endl;
}

void read_all(Person person) 
{
}

void display_page(std::string page) 
{
}

void display_page(std::string page, std::string delim)
{
}

int main(void) 
{
    read_file(3);
}
