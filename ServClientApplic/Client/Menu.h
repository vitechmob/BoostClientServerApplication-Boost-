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

template<class T>
T Rtr(){
    T obj;
    cin >> obj;
    return obj;
}

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
            switch (auto choice = Rtr<int>();choice) {
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
                        if(atoi(size) == 1){
                            char ans[20];
                            socket->receive(boost :: asio :: buffer(ans));
                            if(ans == "err"){
                                cout << "Error,there is no books in DB" << endl;
                                continue;
                            }
                        }
                        cout.width(20);
                        cout.setf(std :: ios :: left);
                        cout << "Book ID";
                        cout.width(20);
                        cout.setf(std :: ios :: left);
                        cout << "Book name";
                        cout.width(20);
                        cout.setf(std :: ios :: left);
                        cout << "Author name";
                        cout.width(20);
                        cout.setf(std :: ios :: left);
                        cout << "Author surname" << endl;
                        for(int i = 0;i < atoi(size);i++){
                            socket->receive(boost :: asio :: buffer(id));
                            socket->receive(boost :: asio :: buffer(book_name));
                            socket->receive(boost :: asio :: buffer(author_name));
                            socket->receive(boost :: asio :: buffer(author_surname));
                            cout.width(20);
                            cout.setf(std :: ios :: left);
                            cout << id;
                            cout.width(20);
                            cout.setf(std :: ios :: left);
                            cout << book_name;
                            cout.width(20);
                            cout.setf(std :: ios :: left);
                            cout << author_name;
                            cout.width(20);
                            cout.setf(std :: ios :: left);
                            cout << author_surname << endl;
                        }
                        cout << "1.Sort by..." << endl;
                        cout << "2.Go back\n>";
                        switch(auto chs = Rtr<int>();chs){
                            case 1 : ;
                                {
                                    char rq[2] = {"1"};
                                    socket->send(boost :: asio :: buffer(rq));
                                    cout << "1.Sort by book name" << endl;
                                    cout << "2.Sort by author name" << endl;
                                    cout << "3.Sort by author surname\n>";
                                    switch(auto sort_choice = Rtr<int>();sort_choice){
                                        case 1 : ;
                                        {
                                        }
                                        default: ;
                                        {

                                        }
                                        break;
                                    }
                                }
                                break;
                            case 2 : ;
                                {
                                    continue;
                                }
                                break;
                            default : ;
                                {

                                }
                                break;
                        }
                    }
                    break;
                default : ;
                    {

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
