//
// Created by xink on 20.04.22.
//

#include "../ClientSession.h"


int RegFunction(socket_ptr socket){
    char login[255], password[255], name[255], surname[255];
    socket->receive(boost::asio::buffer(name));
    if(CheckBack(name)){
        return USER_BACK;
    }
    socket->receive(boost::asio::buffer(surname));
    if(CheckBack(surname)){
        return USER_BACK;
    }
    socket->receive(boost::asio::buffer(login));
    if(CheckBack(login)){
        return USER_BACK;
    }
    socket->receive(boost::asio::buffer(password));
    if(CheckBack(password)){
        return USER_BACK;
    }
    if (AddNewUser(std :: string(name), std :: string(surname), std :: string(login), std :: string(password)) == SQL_SUCCESSFULLY_ADDED) {
        char resp[2] = {"1"};
        socket->send(boost::asio::buffer(resp));
        return SQL_SUCCESSFULLY_ADDED;
    } else if (AddNewUser(std :: string(name), std :: string(surname), std :: string(login), std :: string(password)) == SQL_LOGIN_EXISTS) {
        char resp[2] = {"5"};
        socket->send(boost::asio::buffer(resp));
        return RegFunction(socket);
    } else if(AddNewUser(std :: string(name), std :: string(surname), std :: string(login), std :: string(password)) == SQL_ERROR) {
        cerr << "Error, cant add new user in DB\n";
        char err_code[2] = {"3"};
        socket->send(boost::asio::buffer(err_code));
        return RegFunction(socket);
    }
    return SQL_CANT_LOGGED;
}

int ClientSession(socket_ptr socket,boost :: shared_ptr<std :: vector<boost :: shared_ptr<boost :: asio :: ip :: tcp :: socket>>> sockets,int this_socket_id,boost :: shared_ptr<std :: vector<Client>> clients,boost :: shared_ptr<int> value_of_logged_clients){
    int this_logged_id = 0;
    try {
        while (true) {
            char req[255];
            socket->receive(boost::asio::buffer(req));
            switch (req[0]) {
                case '1' :;
                    {
                        int regFlag = RegFunction(socket);
                        if(regFlag == SQL_SUCCESSFULLY_ADDED){
                            cout << "New user has been added in DB\n";
                        }
                        else if(regFlag == USER_BACK){
                            continue;
                        }
                    }
                    break;
                case '2' :;
                    {
                        LogFlagReturning logFlag = LogFunction(socket);
                        if(logFlag.CODE == SQL_SUCCESSFULLY_LOGGED){
                            cout << "User has entered his account\n";
                            Client this_user(logFlag.id,logFlag.name,logFlag.surname,logFlag.login,logFlag.password);
                            clients->push_back(this_user);
                            *value_of_logged_clients = *value_of_logged_clients + 1;
                            this_logged_id = *value_of_logged_clients;
                            return UserMenu(this_user,socket);
                        }
                        else if(logFlag.CODE == USER_BACK){
                            continue;
                        }
                    }
                    break;
                case '3' :;
                    {
                        cerr << "User disconnected" << endl;
                        sockets->erase(sockets->begin() + this_socket_id);
                        if(this_logged_id != 0) {
                            clients->erase(clients->begin() + this_logged_id);
                        }
                        return SERV_USER_EXIT;
                    }
                    break;
            }
        }
    }
    catch(const std :: exception &ex){
        cerr << "Error:user has been disconnected:" << ex.what() << endl;
        sockets->erase(sockets->begin() + this_socket_id);
        if(this_logged_id != 0) {
            clients->erase(clients->begin() + this_logged_id);
        }
        return BOOST_CONNECTION_ERROR;
    }
}

LogFlagReturning LogFunction(socket_ptr socket){
    char login[255], passw[255];
    socket->receive(boost::asio::buffer(login));
    if(CheckBack(login)){
        LogFlagReturning lgFl(USER_BACK);
        return lgFl;
    }
    socket->receive(boost::asio::buffer(passw));
    if(CheckBack(passw)){
        LogFlagReturning lgFl(USER_BACK);
        return lgFl;
    }
    LogFlagReturning lgFl = CheckLoginPassword(login, passw);
    if (lgFl.CODE == SQL_SUCCESSFULLY_LOGGED) {
        char answ[2] = {"1"};
        socket->send(boost::asio::buffer(answ));
        return lgFl;
    } else {
        char answ[2] = {"2"};
        socket->send(boost::asio::buffer(answ));
        return LogFunction(socket);
    };
}

bool CheckBack(char *buffer){
    cout << strlen(buffer) << endl;
    if(strlen(buffer) == 1){
        if(buffer[0] == 'b' || buffer[0] == 'B'){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

int SortBy(socket_ptr socket,int sort_key,std :: map<int,BookInfo> &books){
    switch(sort_key){
        case 1 : ;
            {
                std::multimap<std::string, BookInfo> sorted_books;
                for (const auto &[id, bk]: books) {
                    sorted_books.insert(std::pair<std::string, BookInfo>(bk.book_name, bk));
                }
                for (const auto &[id, bk]: sorted_books) {
                    BookBuffer bkBuff(bk);
                    socket->send(boost::asio::buffer(bkBuff.book_ID));
                    socket->send(boost::asio::buffer(bkBuff.book_name));
                    socket->send(boost::asio::buffer(bkBuff.author_name));
                    socket->send(boost::asio::buffer(bkBuff.author_surname));
                }
            }
            break;
        case 2 : ;
            {
                std::multimap<std::string, BookInfo> sorted_books;
                for (const auto &[id, bk]: books) {
                    sorted_books.insert(std::pair<std::string, BookInfo>(bk.author_name, bk));
                }
                for (const auto &[id, bk]: sorted_books) {
                    BookBuffer bkBuff(bk);
                    socket->send(boost::asio::buffer(bkBuff.book_ID));
                    socket->send(boost::asio::buffer(bkBuff.book_name));
                    socket->send(boost::asio::buffer(bkBuff.author_name));
                    socket->send(boost::asio::buffer(bkBuff.author_surname));
                }
                for (const auto &[id, bk]: sorted_books) {
                    std :: cout << id << " " << endl;
                }
            }
            break;
        case 3 : ;
            {
                std::multimap<std::string, BookInfo> sorted_books;
                for (const auto &[id, bk]: books) {
                    sorted_books.insert(std::pair<std::string, BookInfo>(bk.author_surname, bk));
                }
                for (const auto &[id, bk]: sorted_books) {
                    BookBuffer bkBuff(bk);
                    socket->send(boost::asio::buffer(bkBuff.book_ID));
                    socket->send(boost::asio::buffer(bkBuff.book_name));
                    socket->send(boost::asio::buffer(bkBuff.author_name));
                    socket->send(boost::asio::buffer(bkBuff.author_surname));
                }
            }
            break;
    }
    return SORT_SUCCESS;
}

int UserMenu(Client client,socket_ptr socket){
    while(true){
        char req[2];
        socket->receive(boost :: asio :: buffer(req));
        switch(req[0]){
            case '1' : ;
                {
                    ClientBuffer clBuff(client);
                    socket->send(boost :: asio :: buffer(clBuff.id_buff));
                    socket->send(boost :: asio :: buffer(clBuff.name_buff));
                    socket->send(boost :: asio :: buffer(clBuff.surname_buff));
                    socket->send(boost :: asio :: buffer(clBuff.login_buff));
                }
                break;
            case '2' : ;
                {
                    std :: map<int,BookInfo> books = BooksMap();
                    uint64_t size = books.size();
                    char sizeT[20];
                    sprintf(sizeT,"%lu",size);
                    cout << sizeT << endl;
                    cout << "123\n";
                    socket->send(boost :: asio :: buffer(sizeT));
                    cout << "256\n";
                    if(atoi(sizeT) == 1){
                        if(books.begin()->first == -5) {
                            socket->send(boost::asio::buffer("err"));
                        }
                    }
                    else {
                        for (const auto &[id, bk]: books) {
                            BookBuffer bkBuff(bk);
                            socket->send(boost :: asio :: buffer(bkBuff.book_ID));
                            socket->send(boost :: asio :: buffer(bkBuff.book_name));
                            socket->send(boost :: asio :: buffer(bkBuff.author_name));
                            socket->send(boost :: asio :: buffer(bkBuff.author_surname));
                        }
                    }
                    char buf[20];
                    socket->receive(boost :: asio :: buffer(buf));
                    switch(buf[0]){
                        case '1' : ;
                            {
                                char rq[20];
                                socket->receive(boost :: asio :: buffer(rq));
                                switch(rq[0]){
                                    case '1' : ;
                                        {
                                            SortBy(socket,1,books);
                                        }
                                        break;
                                    case '2' : ;
                                        {
                                            SortBy(socket,2,books);
                                        }
                                        break;
                                    case '3' : ;
                                        {
                                            SortBy(socket,3,books);
                                        }
                                        break;
                                    default : ;
                                        {

                                        }
                                        break;
                                }
                            }
                            break;
                        case '2' : ;
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
        }
    }
}
