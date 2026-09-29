// Developed by Pavlo Vus on 08.03.2026
#include "String.h"

void String::init_from(const char* str, const size_t len)
{
    _length = len;
    _data = new char[_length + 1];
    if (str) std::copy_n(str, _length, _data);
    _data[_length] = '\0';
}

String::String() : _data(new char[1]{'\0'}), _length(0) {}

String::String(const char* str)
{
    if (str) {
        init_from(str, std::strlen(str));
    } else {
        _data = new char[1]{'\0'};
        _length = 0;
    }
}

String::String(const std::string& str)
{
    init_from(str.c_str(), str.length());
}

String::String(const String& other)
{
    init_from(other._data, other._length);
}

String::String(String&& other) noexcept : _data(other._data), _length(other._length)
{
    other._data = nullptr;
    other._length = 0;
}

String& String::operator=(const String& other)
{
    if (this != &other) {
        delete[] _data;
        init_from(other._data, other._length);
    }
    return *this;
}

String& String::operator=(String&& other) noexcept
{
    if (this != &other) {
        delete[] _data;
        _data = other._data;
        _length = other._length;

        other._data = nullptr;
        other._length = 0;
    }
    return *this;
}

String::~String() { delete[] _data; }

size_t String::length() const { return _length; }

const char* String::c_str() const { return _data ? _data : ""; }

String::operator const char*() const { return c_str(); }


char& String::operator[](const size_t index)
{
    if (index >= _length) throw std::out_of_range("Index out of range");
    return _data[index];
}

const char& String::operator[](const size_t index) const
{
    if (index >= _length) throw std::out_of_range("Index out of range");
    return _data[index];
}


String& String::operator+=(const String& other)
{
    const size_t new_length = _length + other._length;
    char* new_data = new char[new_length + 1];

    std::copy_n(_data, _length, new_data);
    std::copy_n(other._data, other._length, new_data + _length);
    new_data[new_length] = '\0';

    delete[] _data;
    _data = new_data;
    _length = new_length;

    return *this;
}
String& String::operator+=(const char* other) { return *this += String(other); }
String& String::operator+=(const std::string& other) { return *this += String(other); }


String operator+(const String& lhs, const String& rhs)
{
    String result = lhs;
    result += rhs;
    return result;
}
String operator+(const String& lhs, const char* rhs) { return lhs + String(rhs); }
String operator+(const char* lhs, const String& rhs) { return String(lhs) + rhs;}
String operator+(const String& lhs, const std::string& rhs) { return lhs + String(rhs); }
String operator+(const std::string& lhs, const String& rhs) { return String(lhs) + rhs; }

bool operator==(const String& lhs, const String& rhs)
{
    if (lhs.length() != rhs.length()) return false;
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs) { return !(lhs == rhs); }