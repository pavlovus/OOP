// Developed by Pavlo Vus on 08.03.2026
#pragma once
#include <string>

class String
{
    char* _data;
    size_t _length;

    void init_from(const char* str, size_t len);

public:
    String();
    explicit String(const char* str);
    explicit String(const std::string& str);

    String(const String& other);
    String(String&& other) noexcept;
    String& operator=(const String& other);
    String& operator=(String&& other) noexcept;

    ~String();

    size_t length() const;
    const char* c_str() const;

    operator const char*() const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    String& operator+=(const String& other);
    String& operator+=(const char* other);
    String& operator+=(const std::string& other);
};

String operator+(const String& lhs, const String& rhs);
String operator+(const String& lhs, const char* rhs);
String operator+(const char* lhs, const String& rhs);
String operator+(const String& lhs, const std::string& rhs);
String operator+(const std::string& lhs, const String& rhs);

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);