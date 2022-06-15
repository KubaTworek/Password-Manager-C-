//
// Created by Kuba on 02.06.2022.
//

#include "Password.h"


Password::Password(std::string &name, std::string &passwordText, std::string &category) : name(name),
                                                                                          passwordText(passwordText),
                                                                                          category(category) {}
// GETTERS

const std::string &Password::getName() const {
    return name;
}

const std::string &Password::getPasswordText() const {
    return passwordText;
}

const std::string &Password::getCategory() const {
    return category;
}

const std::string &Password::getService() const {
    return service;
}

const std::string &Password::getLogin() const {
    return login;
}

// SETTERS

void Password::setName(const std::string &name) {
    Password::name = name;
}

void Password::setPasswordText(const std::string &passwordText) {
    Password::passwordText = passwordText;
}

void Password::setCategory(const std::string &category) {
    Password::category = category;
}

void Password::setService(const std::string &service) {
    Password::service = service;
}

void Password::setLogin(const std::string &login) {
    Password::login = login;
}

