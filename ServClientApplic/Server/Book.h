//
// Created by xink on 8.04.22.
//
#pragma once
#include "Author.h"
#ifndef SERVCLIENTAPPLIC_BOOK_H
#define SERVCLIENTAPPLIC_BOOK_H

class Book{
private:
    boost :: shared_ptr<int> id;
    boost :: shared_ptr<std :: string> name;
    boost :: shared_ptr<Author> author;
public:
    explicit Book(int,std :: string,Author);
    Book();
    explicit Book(const Book&);
    ~Book();
};

Book :: Book(){
    this->id = boost :: shared_ptr<int>(new int);
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->author = boost :: shared_ptr<Author>(new Author);
}

Book :: Book(int id, std :: string name,Author author){
    this->id = boost :: shared_ptr<int>(new int);
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->author = boost :: shared_ptr<Author>(new Author);
    *this->id = id;
    *this->name = name;
    *this->author = author;
}

Book :: Book(const Book &book){
    this->id = boost :: shared_ptr<int>(new int);
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->author = boost :: shared_ptr<Author>(new Author);
    *this->id = *book.id;
    *this->name = *book.name;
    *this->author = *book.author;
}

Book :: ~Book(){
    std :: cout << "Book constructor" << std :: endl;
}
#endif //SERVCLIENTAPPLIC_BOOK_H
