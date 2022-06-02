//
// Created by Kuba on 02.06.2022.
//
#include <string>

#ifndef PASSWORDMANAGER_PASSWORD_H
#define PASSWORDMANAGER_PASSWORD_H


class Password {
    std::string name;
    std::string passwordText;
    std::string category;
    std::string service;
    std::string login;

public:
    Password(std::string &name, std::string &passwordText, std::string &category);
    Password(std::string &name, std::string &passwordText, std::string &category, std::string &service);
    Password(std::string &name, std::string &passwordText, std::string &category, std::string &service,
             std::string &login);

    //GETTERS

    const std::string &getName() const;

    const std::string &getPasswordText() const;

    const std::string &getCategory() const;

    const std::string &getService() const;

    const std::string &getLogin() const;

    //SETTERS

    void setName(const std::string &name);

    void setPasswordText(const std::string &passwordText);

    void setCategory(const std::string &category);

    void setService(const std::string &service);

    void setLogin(const std::string &login);
};


#endif //PASSWORDMANAGER_PASSWORD_H
