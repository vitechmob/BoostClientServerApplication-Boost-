//
// Created by xink on 20.04.22.
//

#ifndef SERVCLIENTAPPLIC_BUFFS_H
#define SERVCLIENTAPPLIC_BUFFS_H

#include "Client.h"
#include <cstring>

struct LogFlagReturning{
    int CODE;
    int id;
    std :: string name;
    std :: string surname;
    std :: string login;
    std :: string password;
    LogFlagReturning(int CODE,int id,std :: string name,std :: string surname,std :: string login,std :: string password);
    LogFlagReturning(int CODE);
};

struct BookInfo{
    int ID;
    std :: string book_name;
    std :: string author_name;
    std :: string author_surname;
    int value_of_books;
    std :: string writing_language;
    BookInfo(int ID,std :: string book_name,std :: string author_name,std :: string author_surname,int,std :: string);
};

struct ClientBuffer{
    char id_buff[20];
    char name_buff[20];
    char surname_buff[20];
    char login_buff[20];
    char password_buff[20];
    explicit ClientBuffer(Client client);
};
struct BookBuffer{
    char book_ID[20];
    char book_name[20];
    char author_surname[20];
    char author_name[20];
    explicit BookBuffer(BookInfo binf);
};




#endif //SERVCLIENTAPPLIC_BUFFS_H
