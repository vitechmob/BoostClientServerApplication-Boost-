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

#endif //SERVCLIENTAPPLIC_ORDER_H
