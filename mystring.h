#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

namespace String {
    
class StringValue {
private:
    char* data_;
    int size_;
    int refcount_;

public:
    StringValue(const char* = "");
    StringValue(const StringValue&);
    char& operator[](int);
    const char& operator[](int) const;
    StringValue operator+(char) const;
    StringValue operator+(const StringValue&) const;
    ~StringValue();
    int getRefCount() const;
    void incRefCount();
    void decRefCount();
    const char* getData() const;
    int getLength();

};

class MyString {
private:
    StringValue *p;

public:
    MyString(const char* = "");
    MyString(const MyString&);
    MyString(MyString &&) noexcept;
    ~MyString();
    MyString& operator=(const MyString&);
    MyString& operator=(MyString&&) noexcept;
    MyString operator+(char) const;
    MyString& operator+=(char);
    MyString operator+(const MyString&) const;
    MyString& operator+=(const MyString&);
    int length() const;
    char& operator[](int);
    const char& operator[](int) const;
    const char* toString() const;
    int getValueRefCount();
};

std::ostream& operator<<(std::ostream&, const MyString&);
std::istream& operator>>(std::istream&, MyString&);

#endif // MYSTRING_H

} // ns String
