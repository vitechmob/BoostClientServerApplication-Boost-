//
// Created by xink on 8.04.22.
//
#pragma once
#ifndef SERVCLIENTAPPLIC_PERSON_H
#define SERVCLIENTAPPLIC_PERSON_H

class Person{
protected:
    boost :: shared_ptr<std :: string> name;
    boost :: shared_ptr<std :: string> surname;
public:
    explicit Person(std :: string,std :: string);
    virtual void PrintInfo() = 0;
    std :: string GetName(){
        return* name;
    }
    std :: string GetSurname(){
        return *surname;
    }
    Person();
    explicit Person(const Person&);
    virtual ~Person();
};

Person :: Person(){
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->surname = boost :: shared_ptr<std :: string>(new std :: string);
}

Person ::Person(std :: string name,std :: string surname) {
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->surname = boost :: shared_ptr<std :: string>(new std :: string);
    *this->name = name;
    *this->surname = surname;
}
Person :: Person(const Person &pers){
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->surname = boost :: shared_ptr<std :: string>(new std :: string);
    *this->name = *pers.name;
    *this->surname = *pers.surname;
}
Person :: ~Person(){
    std :: cout << "Person destructor\n" << std :: endl;
}

#endif //SERVCLIENTAPPLIC_PERSON_H
