//
// Created by xink on 8.04.22.
//
#pragma once
#ifndef SERVCLIENTAPPLIC_AUTHOR_H
#define SERVCLIENTAPPLIC_AUTHOR_H


#include "Person.h"

class Author : public Person{
private:
    boost :: shared_ptr<int> value_of_books;
    boost :: shared_ptr<std :: string> writing_language;
public:
    explicit Author(std :: string,std :: string,int,std :: string);
    void PrintInfo() override;
    Author(const Author &auth);
    Author();
    ~Author();
};

Author :: Author() : Person() {
    this->value_of_books = boost :: shared_ptr<int>(new int);
    this->writing_language = boost :: shared_ptr<std :: string>(new std :: string);
}

Author ::Author(std :: string name,std :: string surname,int value_of_books,std :: string writing_language) : Person(name,surname){
    this->value_of_books = boost :: shared_ptr<int>(new int);
    this->writing_language = boost :: shared_ptr<std :: string>(new std :: string);
    *this->value_of_books = value_of_books;
    *this->writing_language = writing_language;
}

Author ::Author(const Author &auth) : Person(auth){
    this->value_of_books = boost :: shared_ptr<int>(new int);
    this->writing_language = boost :: shared_ptr<std :: string>(new std :: string);
    *this->value_of_books = *auth.value_of_books;
    *this->writing_language = *auth.writing_language;
}
Author :: ~Author() {
    std :: cout << "Author destructor\n";
}

void Author::PrintInfo() {
    std :: cout << *name <<  " " << *surname << " " << *value_of_books << " " << *writing_language << std :: endl;
}
#endif //SERVCLIENTAPPLIC_AUTHOR_H
