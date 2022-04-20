//
// Created by xink on 20.04.22.
//

#include "../DataBase.h"

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

std :: map<int,BookInfo> BooksMap(){
    try {
        std::map<int, BookInfo> books;
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        driver = get_driver_instance();
        con = driver->connect(DATABASE_ADDRESS, USERNAME, PASSWORD);
        con->setSchema("ApplicationDB");
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT books.id,books.book_name,authors.name,authors.surname FROM books JOIN authors on authors.id = books.author_id");
        while (res->next()) {
            int ID = res->getInt("id");
            std::string book_name = res->getString("book_name");
            std::string author_name = res->getString("name");
            std::string author_surname = res->getString("surname");
            BookInfo inf(ID, book_name, author_name, author_surname);
            books.insert(std::pair<int, BookInfo>(inf.ID, inf));
        }

        delete con;
        delete stmt;
        delete res;
        return books;
    }catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "
             << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        std :: map<int,BookInfo> m;
        m.insert(std :: pair<int,BookInfo>(-5,BookInfo(-5,"err","err","err")));
        return m;
    }
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
        prep_stmt = con->prepareStatement("INSERT INTO books(id,book_name,author) VALUES(?,?,?)");
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

int AddNewUser(const std :: string& name,const std :: string &surname,const std :: string &login,const std :: string &password){
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
