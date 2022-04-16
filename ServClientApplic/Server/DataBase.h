//
// Created by xink on 31.03.22.
//
#include "Global.h"

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

LogFlagReturning::LogFlagReturning(int CODE,int id,std :: string name,std :: string surname,std :: string login,std :: string password) {
    this->CODE = CODE;
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->login = login;
    this->password = password;
}

LogFlagReturning :: LogFlagReturning(int CODE){
    this->CODE = CODE;
}


int GetUsersValue(sql :: Statement *stmt);
LogFlagReturning CheckLoginPassword(std :: string input_login,std :: string input_password);
int CheckLogin(std :: string input_login);

int AddNewUser(std :: string name,std :: string surname,std :: string login,std :: string password){
    try {
        if(CheckLogin(login) == SQL_LOGIN_EXISTS){
            return SQL_LOGIN_EXISTS;
        }
        else {
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
            sql::ResultSet *res;
            sql::PreparedStatement *prep_stmt;
            driver = get_driver_instance();
            con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
            con->setSchema("ApplicationDB");
            prep_stmt = con->prepareStatement("INSERT INTO users(id,name,surname,login,password) VALUES (?,?,?,?,?)");
            stmt = con->createStatement();
            prep_stmt->setInt(1, GetUsersValue(stmt));
            prep_stmt->setString(2, name);
            prep_stmt->setString(3, surname);
            prep_stmt->setString(4, login);
            prep_stmt->setString(5, password);
            prep_stmt->execute();
            delete con;
            delete prep_stmt;
            return SQL_SUCCESSFULLY_ADDED;
        }
    }
    catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "
             << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return SQL_ERROR;
    }
}

int GetUsersValue(sql :: Statement *stmt){
    sql :: ResultSet *res;
    res = stmt->executeQuery("SELECT id,name,surname,login,password FROM users ORDER BY id ASC");
    int i = 1;
    while(res->next()){
        i++;
    }
    delete res;
    return i;
}

int AddNewBook(std :: string name,Author author){
    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        sql::PreparedStatement *prep_stmt;
        driver = get_driver_instance();
        con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
        con->setSchema("ApplicationDB");
        prep_stmt = con->prepareStatement("INSERT INTO books(id,name,author) VALUES(?,?,?)");
        delete con;
        delete prep_stmt;
    }
    catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "
             << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return SQL_ERROR;
    }
}

int CheckLogin(std :: string input_login){
    sql :: Driver *driver;
    sql :: Connection *con;
    sql :: Statement *stmt;
    sql :: ResultSet *res;
    driver = get_driver_instance();
    con = driver->connect(DATABASE_ADDRESS,USERNAME,PASSWORD);
    con->setSchema("ApplicationDB");
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT id,name,surname,login,password FROM users ORDER BY id ASC");
    while(res->next()){
        std :: string name = res->getString("name");
        std :: string surname = res->getString("surname");
        std :: string login = res->getString("login");
        std :: string password = res->getString("password");
        if(input_login.compare(login) == 0){
            delete con;
            delete stmt;
            delete res;
            return SQL_LOGIN_EXISTS;
        }
    }
    delete con;
    delete stmt;
    delete res;
    return SQL_LOGIN_IS_NOT_EXISTS;

}

LogFlagReturning CheckLoginPassword(std :: string input_login,std :: string input_password){
    try{
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        driver = get_driver_instance();
        con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
        con->setSchema("ApplicationDB");
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT id,name,surname,login,password FROM users ORDER BY id ASC");
        while(res->next()){
            int ID = res->getInt(1);
            std :: string name = res->getString("name");
            std :: string surname = res->getString("surname");
            std :: string login = res->getString("login");
            std :: string password = res->getString("password");
            if(input_login.compare(login) == 0){
                if(input_password.compare(password) == 0){
                    delete con;
                    delete stmt;
                    delete res;
                    LogFlagReturning log(SQL_SUCCESSFULLY_LOGGED,ID,name,surname,login,password);
                    return log;
                }
            }
        }
        delete con;
        delete stmt;
        delete res;
        LogFlagReturning log(SQL_CANT_LOGGED);
        return log;
    }
    catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "
             << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        LogFlagReturning log(SQL_ERROR);
        return log;
    }
}

#ifndef SERVCLIENTAPPLIC_DATABASE_H
#define SERVCLIENTAPPLIC_DATABASE_H

#endif //SERVCLIENTAPPLIC_DATABASE_H
