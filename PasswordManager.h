//
// Created by Kuba on 15.06.2022.
//

#ifndef PASSWORDMANAGER_PASSWORDMANAGER_H
#define PASSWORDMANAGER_PASSWORDMANAGER_H


#include <vector>
#include "Password.h"
#include "CategoryManager.h"

class PasswordManager {
    std::vector<Password> passwords;

public:
    explicit PasswordManager(std::vector<Password> passwords);

    void passwordManagement(std::vector<Password> &pass, CategoryManager &categoryManager);

    void lookingForPasswords(std::vector<Password> &pass, std::vector<std::string> &categ);

    void sortPasswords(std::vector<Password> &vector);

    void addPassword(std::vector<Password> &pass, std::vector<std::string> &categ);

    void editPassword(std::vector<Password> &vector);

    void deletePassword(std::vector<Password> &vector);

    void writeOutPasswords(std::vector<Password> &vector);

    void writeOutPasswords(std::vector<Password> &vector, const std::string &category);

    void writeOutPasswordsByName(std::vector<Password> &vector, const std::string &name);

    void savePasswords(std::vector<Password> &vector);

    bool isPasswordRepeat(std::vector<Password> &vector, const std::string &password);

    std::string autoGeneratePassword();

    static bool checkPassword(const std::string &password);

    std::string encryption(const std::string &oldPassword);

    static std::string decryption(const std::string &oldPassword);
};


#endif //PASSWORDMANAGER_PASSWORDMANAGER_H
