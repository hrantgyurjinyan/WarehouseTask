#include "Value.hpp"

Value::Value(int i) : type(ValueType::INT) {
    data.i = i;
}

Value::Value(double d) : type(ValueType::DOUBLE) {
    data.d = d;
}

Value::Value(const std::string& s) : type(ValueType::STRING) {
    new(&data.s) std::string(s);
}

Value::Value(const Value& other) : type(other.type) 
{
    switch (type) 
    {
        case ValueType::INT:
            data.i = other.data.i;
            break;
        case ValueType::DOUBLE:
            data.d = other.data.d;
            break;
        case ValueType::STRING:
            new(&data.s) std::string(other.data.s);
            break;
    }
}

Value& Value::operator=(const Value& other) 
{
    if (this != &other) 
    {
        clear();
        type = other.type;
        switch (type) 
        {
            case ValueType::INT:
                data.i = other.data.i;
                break;
            case ValueType::DOUBLE:
                data.d = other.data.d;
                break;
            case ValueType::STRING:
                new(&data.s) std::string(other.data.s);
                break;
        }
    }
    return *this;
}

Value::~Value() 
{
    clear();
}

void Value::clear() 
{
    if (type == ValueType::STRING) 
    {
        using std::string;
        data.s.~string();
    }
}

void Value::print() const 
{
    switch (type) 
    {
        case ValueType::INT:
            std::cout << data.i << std::endl;
            break;
        case ValueType::DOUBLE:
            std::cout << data.d << std::endl;
            break;
        case ValueType::STRING:
            std::cout << data.s << std::endl;
            break;
    }
}

Value determineTypeAndConvert(const std::string& str) 
{
    bool hasDecimalPoint = false;
    bool isNumeric = true;

    for (size_t i = 0; i < str.length(); ++i) 
    {
        if (str[i] == '.') {
            if (hasDecimalPoint) {
                isNumeric = false;
                break;
            }
            hasDecimalPoint = true;
        } else if (!isdigit(str[i]) && !(i == 0 && (str[i] == '-' || str[i] == '+'))) {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric) 
    {
        if (hasDecimalPoint) 
        {
            return Value(std::stod(str));
        } 
        else 
        {
            return Value(std::stoi(str));
        }
    } 
    else 
    {
        return Value(str);
    }
}
