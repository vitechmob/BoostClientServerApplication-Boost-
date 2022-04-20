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

#endif //SERVCLIENTAPPLIC_BOOK_H
