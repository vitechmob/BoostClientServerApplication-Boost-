//
// Created by xink on 20.04.22.
//

#include "../Order.h"


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
