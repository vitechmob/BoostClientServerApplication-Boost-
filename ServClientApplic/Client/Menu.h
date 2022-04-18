//
// Created by xink on 1.04.22.
//
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "../Server/Client.h"

#define LOCAL_HOST "127.0.0.1"
#define PORT 2001
#define EXIT_STATUS 0
#define USER_BACK 16


typedef boost :: shared_ptr<boost :: asio :: ip :: tcp :: socket> socket_ptr;
using std :: cout , std :: cin , std :: endl,std :: cerr;

#ifndef SERVCLIENTAPPLIC_MENU_H
#define SERVCLIENTAPPLIC_MENU_H
int LogMenu(){
    cout << "\t\t\t\t\t\t\t\t\t\t\t--------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t|Press b to go back|" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t--------------------" << endl;

    cout << "\t\t\t\t\t\t\t\t\t\t\t+----------+\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t|   MENU   |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t+----------+\n";

    cout << "\t\t\t\t\t\t\t\t\t\t\t+----------+\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t|  LOGIN   |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t+----------+\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t+----------+\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t| REGISTER |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t+----------+\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t+----------+\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t|   EXIT   |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t+----------+\n";
    int choice;
    cin >> choice;
    return choice;
}

int UserMenu(socket_ptr socket){
    try {
        while (true) {
            system("clear");
            cout << "1.Get info" << endl;
            cout << "2.Get books info" << endl;
            int choice;
            cin >> choice;
            switch (choice) {
                case 1 :;
                    {
                        char req[2] = {"1"};
                        socket->send(boost :: asio :: buffer(req));
                        char id[20], name[20], surname[20], login[20];
                        socket->receive(boost::asio::buffer(id));
                        socket->receive(boost::asio::buffer(name));
                        socket->receive(boost::asio::buffer(surname));
                        socket->receive(boost::asio::buffer(login));
                        std :: cout << "ID:" << id << "\nName:" << name << "\nSurname:" << surname << "\nLogin:" << login << std :: endl;
                    }
                    break;
                case 2 : ;
                    {
                        char req[2] = {"2"};
                        socket->send(boost :: asio :: buffer(req));
                        char id[20],book_name[20],author_name[20],author_surname[20],size[20];
                        socket->receive(boost :: asio :: buffer(size));
                        cout << size;
                        if(atoi(size) == 1){
                            char ans[20];
                            socket->receive(boost :: asio :: buffer(ans));
                            if(ans == "err"){
                                cout << "Error,there is no books in DB" << endl;
                                continue;
                            }
                        }
                        for(int i = 0;i < atoi(size);i++){
                            socket->receive(boost :: asio :: buffer(id));
                            socket->receive(boost :: asio :: buffer(book_name));
                            socket->receive(boost :: asio :: buffer(author_name));
                            socket->receive(boost :: asio :: buffer(author_surname));
                            std :: cout << "Book id:" << id << "\nBook name:" << book_name << "\nAuthor name:" << author_name
                                        << "\nAuthor surname:" << author_surname << endl;
                        }
                    }
                    break;
            }
        }
    }catch(std :: exception &exc){
        cout << "Exception\n";
    }
    catch(boost :: system :: error_code &ec){
        cout << "Error code:" << ec.message() << endl;
    }
}
#endif //SERVCLIENTAPPLIC_MENU_H
