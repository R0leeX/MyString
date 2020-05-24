#include "mystring.h"
#include <cstring>

StringValue::StringValue(const char* s){
    size_ = strlen(s);
    //data_ = nullptr;
    data_ = new char[size_ + 1];
    strcpy(data_, s);
    refcount_ = 1;
}

StringValue::StringValue(const StringValue& rhs){
    size_ = rhs.size_ + 1;
    data_ = new char[size_ + 1];
    strcpy(data_, rhs.data_);
    data_[size_] = '\0';
    refcount_ = 1;

}
char& StringValue::operator[](int pos){
    return data_[pos];
}

const char& StringValue::operator[](int pos) const{
    return data_[pos];
}

StringValue StringValue::operator+(char c) const{
    StringValue newValue;
    delete[] newValue.data_;
    newValue.size_ = size_ + 1;
    newValue.data_ = new char[newValue.size_ + 1];
    strcpy(newValue.data_, data_);
    newValue.data_[newValue.size_ - 1] = c;
    newValue.data_[newValue.size_] = '\0';
    newValue.refcount_ = 1;
    return newValue;

}

StringValue StringValue::operator+(const StringValue& rhs) const{
    StringValue newValue;
    delete[] newValue.data_;
    newValue.size_ = this->size_ + rhs.size_;
    newValue.data_ = new char[newValue.size_ + 1];
    strcpy(newValue.data_, this->data_);
    strcat(newValue.data_, rhs.data_);
    return newValue;
}

StringValue::~StringValue(){
    delete[] data_;
}

int StringValue::getRefCount() const{
    return refcount_;
}

void StringValue::incRefCount(){
    refcount_++;
}

void StringValue::decRefCount(){
    refcount_--;
}

const char* StringValue::getData()const{
    return data_;
}

int StringValue::getLength(){
    return size_;
}

MyString::MyString(const char* s){
    p = new StringValue(s);
}

MyString::MyString(const MyString& rhs): p{rhs.p}{
    if(p){
        p->incRefCount();
    }
}

MyString::MyString(MyString && rhs) noexcept{
    p = rhs.p;
    rhs.p = nullptr;
}

MyString::~MyString(){
    if(p){
        p->decRefCount();
        if(p->getRefCount() == 0)
            delete p;
    }
}

MyString& MyString::operator=(const MyString& rhs){
    if(this != &rhs) {
        if(p)
            p->decRefCount();
        if(p->getRefCount() == 0)
            delete p;
        p = rhs.p;
        p->incRefCount();
    }
    return *this;
}

MyString& MyString::operator=(MyString&& rhs) noexcept{
    if(this != &rhs) {
        if(p)
            p->decRefCount();
        if(p->getRefCount() == 0)
            delete p;
        p = rhs.p;
        rhs.p = nullptr;
    }
    return *this;

}

MyString MyString::operator+(char c) const{
    //StringValue *newValue = new StringValue(*p + c);
    //MyString temp(newValue->getData());
    //delete newValue;
    MyString temp(*p->getData() + &c);
    return temp;
}

MyString& MyString::operator+=(char c){
    StringValue *newValue = new StringValue(*p + c);
    if(p)
        p->decRefCount();
    if(p->getRefCount() == 0)
        delete p;
    p = newValue;
    return *this;
}

MyString MyString::operator+(const MyString& rhs) const{
    StringValue *newValue = new StringValue(*p + *rhs.p);
    MyString temp(newValue->getData());
    delete newValue;
    return temp;
}

MyString& MyString::operator+=(const MyString& rhs){
    StringValue *newValue = new StringValue(*p + *rhs.p);
    if(p)
        p->decRefCount();
    if(p->getRefCount() == 0)
        delete p;
    p = newValue;
    return *this;
}

int MyString::length() const{
    return p->getLength();
}

char& MyString::operator[](int pos){
    StringValue *newValue = new StringValue(*p);
    if(p)
       p->decRefCount();
    if(p->getRefCount() == 0)
        delete p;
    p = newValue;
    return p->operator[](pos);
}

const char& MyString::operator[](int pos) const{
    return p->operator[](pos);
}

const char* MyString::toString() const{
    return p->getData();
}

int MyString::getValueRefCount(){
    return p->getRefCount();
}

std::ostream& operator<<(std::ostream& os, const MyString& s){
    return os << s.toString();
}

std::istream& operator>>(std::istream& is, MyString& s){
    char c;
    MyString temp;
    while(is.get(c) && c != '\n')
        temp += c;
    s = temp;
    return is;
}
