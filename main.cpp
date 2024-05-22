#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Value.hpp"

int main() {
    std::ifstream file("TXT.txt");
    if (!file) 
    {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<Value> values;

    while (std::getline(file, line)) 
    {
        if (!line.empty()) 
        {
            values.push_back(determineTypeAndConvert(line));
        }
    }

    file.close();

    for (const auto& value : values) 
    {
        value.print();
    }

    return 0;
}
