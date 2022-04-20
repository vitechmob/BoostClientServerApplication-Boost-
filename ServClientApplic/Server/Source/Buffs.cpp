//
// Created by xink on 20.04.22.
//
#include "../Buffs.h"

ClientBuffer :: ClientBuffer(Client client) {
    sprintf(id_buff,"%d",client.GetId());
    strcpy(name_buff,client.GetName().c_str());
    strcpy(surname_buff,client.GetSurname().c_str());
    strcpy(login_buff,client.GetLogin().c_str());
    strcpy(password_buff,client.GetPassword().c_str());
}

BookBuffer ::BookBuffer(BookInfo binf) {
    sprintf(book_ID,"%d",binf.ID);
    strcpy(book_name,binf.book_name.c_str());
    strcpy(author_name,binf.author_name.c_str());
    strcpy(author_surname,binf.author_surname.c_str());
}

BookInfo ::BookInfo(int ID, std::string book_name, std::string author_name, std::string author_surname) {
    this->ID = ID;
    this->book_name = book_name;
    this->author_name = author_name;
    this->author_surname = author_surname;
}

LogFlagReturning ::LogFlagReturning(int CODE, int id, std::string name, std::string surname, std::string login,
                                    std::string password) {
    this->CODE = CODE;
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->login = login;
    this->password = password;
}
LogFlagReturning ::LogFlagReturning(int CODE) {
    this->CODE = CODE;
}