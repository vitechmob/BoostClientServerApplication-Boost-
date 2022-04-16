//
// Created by xink on 8.04.22.
//


#pragma once
#ifndef SERVCLIENTAPPLIC_ORDER_H
#define SERVCLIENTAPPLIC_ORDER_H
#include "Client.h"
#include "Book.h"


class Order{
private:
    boost :: shared_ptr<Client> client;
    boost :: shared_ptr<Book> book;
public:
    Order();
    explicit Order(Client,Book);
    explicit Order(const Order&);
    ~Order();
};

Order :: Order(){
    this->client = boost :: shared_ptr<Client>(new Client);
    this->book = boost :: shared_ptr<Book>(new Book);
}

Order :: Order(Client client,Book book){
    this->client = boost :: shared_ptr<Client>(new Client);
    this->book = boost :: shared_ptr<Book>(new Book);
    *this->client = client;
    *this->book = book;
}

Order :: Order(const Order& order){
    this->client = boost :: shared_ptr<Client>(new Client);
    this->book = boost :: shared_ptr<Book>(new Book);
    *this->client = *order.client;
    *this->book = *order.book;
}

Order :: ~Order(){
    std :: cout << "Order destructor" << std :: endl;
}

#endif //SERVCLIENTAPPLIC_ORDER_H
