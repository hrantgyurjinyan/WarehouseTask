#pragma once

#include <iostream>
#include <string>

enum class ValueType 
{
    INT,
    DOUBLE,
    STRING
};

class Value 
{
private:
    ValueType type;
    union Data {
        int i;
        double d;
        std::string s;
        Data() {}
        ~Data() {}
    } data;

    void clear();
    
public:
    Value(int i);
    Value(double d);
    Value(const std::string& s);
    Value(const Value& other);
    Value& operator=(const Value& other);
    ~Value();

    void print() const;


};

Value determineTypeAndConvert(const std::string& str);

