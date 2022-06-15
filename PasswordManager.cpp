//
// Created by Kuba on 15.06.2022.
//

#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
#include "PasswordManager.h"
#include "CategoryManager.h"

PasswordManager::PasswordManager(std::vector<Password> passwords) {
    CategoryManager categoryManager;
    passwordManagement(passwords, categoryManager);
}

/**a
 * Starting management every option, main menu in application
 * @param pass vectory of passwords
 * @param categoryManager class of categoryManager which we will be working on
 */
void PasswordManager::passwordManagement(std::vector<Password> &pass, CategoryManager &categoryManager) {
    std::vector<std::string> categ = categoryManager.getCategories();
    while (true) {
        std::cout << std::endl;
        std::cout << "Wybierz opcje." << std::endl;
        std::cout << "1. Wyszukaj hasla." << std::endl;
        std::cout << "2. Posortuj hasla." << std::endl;
        std::cout << "3. Dodaj haslo." << std::endl;
        std::cout << "4. Edytuj haslo." << std::endl;
        std::cout << "5. Usun haslo." << std::endl;
        std::cout << "6. Dodaj kategorie." << std::endl;
        std::cout << "7. Usun kategorie." << std::endl;
        std::cout << "0. Zakoncz." << std::endl;

        int choose = 0;

        std::cout << "Podaj numer" << std::endl;
        std::cin >> choose;

        switch (choose) {
            case 1:
                lookingForPasswords(pass, categ);
                break;
            case 2:
                sortPasswords(pass);
                break;
            case 3:
                addPassword(pass, categ);
                break;
            case 4:
                writeOutPasswords(pass);
                editPassword(pass);
                break;
            case 5:
                writeOutPasswords(pass);
                deletePassword(pass);
                break;
            case 6:
                CategoryManager::writeOutCategories(categ);
                CategoryManager::addCategory(categ);
                break;
            case 7:
                CategoryManager::writeOutCategories(categ);
                CategoryManager::deleteCategory(pass, categ);
                break;
            case 0:
                exit(0);
            default:
                continue;
        }
    }
}

/**a
 * Choosing which specify passwords, we would like to find
 * @param pass vector of passwords
 * @param categ vector of categories
 */
void PasswordManager::lookingForPasswords(std::vector<Password> &pass, std::vector<std::string> &categ) {
    std::string name;
    int choose, categoryId;
    std::cout << "Chcesz wyszukac hasla wedlug?" << std::endl;
    std::cout << "1. Kategorii" << std::endl;
    std::cout << "2. Nazwy" << std::endl;
    std::cin >> choose;
    if (choose == 1) {
        CategoryManager::writeOutCategories(categ);
        std::cout << "Podaj numer kategorii: ";
        std::cin >> categoryId;
        writeOutPasswords(pass, categ.at(categoryId - 1));
    } else if (choose == 2) {
        std::cout << "Podaj nazwe hasla: ";
        std::cin >> name;
        writeOutPasswordsByName(pass, name);
    } else {
        std::cout << "Niepoprawny numer" << std::endl;
    }
}

bool sortName(const Password &a, const Password &b) { return (a.getName() < b.getName()); }

bool sortCategory(const Password &a, const Password &b) { return (a.getCategory() < b.getCategory()); }

bool sortNameAndCategory(const Password &a, const Password &b) {
    if (a.getName() < b.getName()) {
        return a.getName() < b.getName();
    } else if (a.getName() > b.getName()) {
        return a.getName() > b.getName();
    } else {
        return (a.getCategory() < b.getCategory());
    }
}

/**a
 * Sorting passwords
 * @param vector vector of passwords
 */
void PasswordManager::sortPasswords(std::vector<Password> &vector) {
    std::cout << std::endl;
    std::cout << "Wybierz opcje." << std::endl;
    std::cout << "1. Sortuj wedlug nazwy." << std::endl;
    std::cout << "2. Sortuj wedlug kategorii." << std::endl;
    std::cout << "3. Sortuj wedlug nazwy i kategorii." << std::endl;
    std::cout << "0. Zakoncz." << std::endl;

    int choose;
    std::cin >> choose;

    switch (choose) {
        case 1: {
            sort(vector.begin(), vector.end(), sortName);
            savePasswords(vector);
            writeOutPasswords(vector);
        }
            break;
        case 2: {
            sort(vector.begin(), vector.end(), sortCategory);
            savePasswords(vector);
            writeOutPasswords(vector);
        }
            break;
        case 3: {
            sort(vector.begin(), vector.end(), sortNameAndCategory);
            savePasswords(vector);
            writeOutPasswords(vector);
        }
            break;
        case 0:
        default:
            break;
    }
}

/**a
 * Adding a new password
 * @param pass vector of passwords
 * @param categ vector of categories
 */
void PasswordManager::addPassword(std::vector<Password> &pass, std::vector<std::string> &categ) {
    std::string name, passwordText, category, service, login;
    char confirmService, confirmLogin, confirmAutoPassword;
    int categoryId;
    std::cout << "Wybierz nazwe hasla, ktora chcesz dodac: " << std::endl;
    std::cin >> name;

    std::cout << "Czy chcesz wygenerowac automatyczne haslo? (y/n)" << std::endl;
    std::cin >> confirmAutoPassword;
    if (tolower(confirmAutoPassword) == 'y') {
        passwordText = autoGeneratePassword();
    } else {
        while (true) {
            std::cout << "Napisz haslo, ktora chcesz dodac: " << std::endl;
            std::cin >> passwordText;
            if (!isPasswordRepeat(pass, passwordText)) {
                if (passwordText.length() > 8) {
                    break;
                } else {
                    std::cout << "Haslo jest za krotkie" << std::endl;
                }
            } else {
                std::cout << "Haslo sie powtarza" << std::endl;
            }
        }
    }

    CategoryManager::writeOutCategories(categ);
    std::cout << "Wybierz kategorie(numer), ktora ma miec haslo: " << std::endl;
    std::cin >> categoryId;
    category = categ.at(categoryId - 1);
    Password password(name, passwordText, category);

    std::cout << "Chcesz wpisac serwis do ktorego nalezy haslo? (y/n)";
    std::cin >> confirmService;
    if (tolower(confirmService) == 'y') {
        std::cout << "Wpisz: " << std::endl;
        std::cin >> service;
        password.setService(service);
    } else {
        password.setService("brak");
    }

    std::cout << "Chcesz wpisac login do ktorego nalezy haslo? (y/n)";
    std::cin >> confirmLogin;
    if (tolower(confirmLogin) == 'y') {
        std::cout << "Wpisz: " << std::endl;
        std::cin >> login;
        password.setLogin(login);
    } else {
        password.setLogin("brak");
    }

    pass.push_back(password);
    savePasswords(pass);
    std::cout << "Haslo zostalo dodane" << std::endl;
}

/**a
 * Choosing a passwords to edit and next choose specific parameter to edit
 * @param vector vector of passwords
 */
void PasswordManager::editPassword(std::vector<Password> &vector) {
    int choosePassword, chooseEdit;
    std::string newData;
    std::cout << "Wybierz numer hasla, ktore chcesz edytowac: " << std::endl;
    std::cin >> choosePassword;
    std::cout << "1. Nazwa: " << vector.at(choosePassword - 1).getName() << std::endl;
    std::cout << "2. Haslo: " << vector.at(choosePassword - 1).getPasswordText() << std::endl;
    std::cout << "3. Kategoria: " << vector.at(choosePassword - 1).getCategory() << std::endl;
    std::cout << "4. StronaWWW/Serwis: " << vector.at(choosePassword - 1).getService() << std::endl;
    std::cout << "5. Login: " << vector.at(choosePassword - 1).getLogin() << std::endl;
    std::cout << "Wybierz numer danej, ktora chcesz edytowac: " << std::endl;
    std::cin >> chooseEdit;
    std::cout << "Wpisz nowa wartosc: " << std::endl;
    std::cin >> newData;
    switch (chooseEdit) {
        case 1:
            vector.at(choosePassword - 1).setName(newData);
            break;
        case 2:
            vector.at(choosePassword - 1).setPasswordText(newData);
            break;
        case 3:
            vector.at(choosePassword - 1).setCategory(newData);
            break;
        case 4:
            vector.at(choosePassword - 1).setService(newData);
            break;
        case 5:
            vector.at(choosePassword - 1).setLogin(newData);
            break;
        default:
            break;
    }
    savePasswords(vector);
    std::cout << "Zmieniles dana w hasle" << std::endl;
}

/**a
 * deleting specify password to delete
 * @param vector vector of passwords
 */
void PasswordManager::deletePassword(std::vector<Password> &vector) {
    int choosePassword;
    char confirm;
    std::cout << "Wybierz numer hasla, ktore chcesz usunac: " << std::endl;
    std::cin >> choosePassword;
    std::cout << "Na pewno chcesz to usunac? (y/n) " << std::endl;
    std::cin >> confirm;
    if (tolower(confirm) == 'y') {
        vector.erase(vector.cbegin() + choosePassword - 1);
        savePasswords(vector);
        std::cout << "Usunales haslo" << std::endl;
    } else {
        std::cout << "Nie usunales hasla" << std::endl;
    }
}

/**a
 * Write out every password
 * @param vector vector of passwords
 */
void PasswordManager::writeOutPasswords(std::vector<Password> &vector) {
    int i = 1;
    for (const Password &password: vector) {
        std::cout << i++ << ". " << password.getName() << std::endl;
    }
}

/**a
 * Write out passwords with specify category
 * @param vector vector of passwords
 * @param string specify name of category
 */
void PasswordManager::writeOutPasswords(std::vector<Password> &vector, const std::string &category) {
    int i = 1;
    for (const Password &password: vector) {
        if (password.getCategory() == category) {
            std::cout << i++ << ". " << password.getName() << std::endl;
        }
    }
}

/**a
 * Write out passwords with specify name
 * @param vector vector of passwords
 * @param string specify name of password
 */
void PasswordManager::writeOutPasswordsByName(std::vector<Password> &vector, const std::string &name) {
    for (const Password &password: vector) {
        if (password.getName() == name) {
            std::cout << "Nazwa: " << password.getName() << std::endl;
            std::cout << "Haslo: " << password.getPasswordText() << std::endl;
            std::cout << "Kategoria: " << password.getCategory() << std::endl;
            std::cout << "StronaWWW/Serwis: " << password.getService() << std::endl;
            std::cout << "Login: " << password.getLogin() << std::endl;
        }
    }
}

/**a
 * Save every password to file
 * @param vector vector of passwords
 */
void PasswordManager::savePasswords(std::vector<Password> &vector) {
    std::string str;
    std::ofstream save("../passwords.txt");
    for (const Password &password: vector) {
        str += "Nazwa: " + password.getName() + "\n"
               + "Haslo: " + encryption(password.getPasswordText()) + "\n"
               + "Kategoria: " + password.getCategory() + "\n"
               + "StronaWWW/Serwis: " + password.getService() + "\n"
               + "Login: " + password.getLogin() + "\n";
    }
    save << str;
    save.close();
}

/**a
 * Checking is password repeated with any other in file
 * @param vector vector of passwords
 * @param passwordText password choosen by user
 * @return true is password repeated, false if it isn't
 */
bool PasswordManager::isPasswordRepeat(std::vector<Password> &vector, const std::string &passwordText) {
    if (std::any_of(vector.cbegin(), vector.cend(),
                    [passwordText](const Password &x) { return x.getPasswordText() == passwordText; })) {
        return true;
    }
    return false;
}

/**a
 * Auto generate password, asking for amount of letters and use specify signs
 * @return auto generated passsword
 */
std::string PasswordManager::autoGeneratePassword() {
    std::string tabs[] = {"qwertyuiopasdfghjklzxcvbnm", "1234567890", "!@#$%^&*", "QWERTYUIOPASDFGHJKLZXCVBNM"};

    char confirmBigLetters, confirmSpecialSigns;
    int amountOfSigns;
    bool isBigLetters;
    bool isSpecialSigns;
    while (true) {
        std::cout << "Jaka dlugosc hasla chcesz miec? " << std::endl;
        std::cin >> amountOfSigns;
        if (amountOfSigns < 8) {
            std::cout << "Za krotkie haslo" << std::endl;
        } else {
            break;
        }
    }
    std::cout << "Chcesz wielkie i male litery? (y/n)" << std::endl;
    std::cin >> confirmBigLetters;
    if (tolower(confirmBigLetters) == 'y') {
        isBigLetters = true;
    } else {
        isBigLetters = false;
    }
    std::cout << "Chcesz znaki specjalne? (y/n)" << std::endl;
    std::cin >> confirmSpecialSigns;
    if (tolower(confirmSpecialSigns) == 'y') {
        isSpecialSigns = true;
    } else {
        isSpecialSigns = false;
    }

    std::default_random_engine defEngine(time(nullptr));
    char password[amountOfSigns];
    if (isBigLetters && isSpecialSigns) {
        for (int i = 0; i < amountOfSigns; i++) {
            int amountOfLetters;
            std::uniform_int_distribution<int> intDistro(0, 3);
            int random = intDistro(defEngine);
            if (random == 3) amountOfLetters = 26;
            if (random == 2) amountOfLetters = 9;
            if (random == 1) amountOfLetters = 10;
            if (random == 0) amountOfLetters = 26;

            std::uniform_int_distribution<int> sizeOfPassword(0, amountOfLetters);
            password[i] = tabs[random][sizeOfPassword(defEngine)];
        }
    } else if (isBigLetters) {
        for (int i = 0; i < amountOfSigns; i++) {
            int amountOfLetters;
            std::uniform_int_distribution<int> intDistro(0, 2);
            int random = intDistro(defEngine);
            if (random == 2) amountOfLetters = 26;
            if (random == 1) amountOfLetters = 10;
            if (random == 0) amountOfLetters = 26;

            std::uniform_int_distribution<int> sizeOfPassword(0, amountOfLetters);
            if (random == 2) {
                password[i] = tabs[random + 1][sizeOfPassword(defEngine)];
            } else {
                password[i] = tabs[random][sizeOfPassword(defEngine)];
            }
        }
    } else if (isSpecialSigns) {
        for (int i = 0; i < amountOfSigns; i++) {
            int amountOfLetters;
            std::uniform_int_distribution<int> intDistro(0, 2);
            int random = intDistro(defEngine);
            if (random == 2) amountOfLetters = 26;
            if (random == 1) amountOfLetters = 10;
            if (random == 0) amountOfLetters = 26;

            std::uniform_int_distribution<int> sizeOfPassword(0, amountOfLetters);
            password[i] = tabs[random][sizeOfPassword(defEngine)];
        }
    } else {
        for (int i = 0; i < amountOfSigns; i++) {
            int amountOfLetters;
            std::uniform_int_distribution<int> intDistro(0, 1);
            int random = intDistro(defEngine);
            if (random == 1) amountOfLetters = 10;
            if (random == 0) amountOfLetters = 26;

            std::uniform_int_distribution<int> sizeOfPassword(0, amountOfLetters);
            password[i] = tabs[random][sizeOfPassword(defEngine)];
        }
    }
    return {password};
}

/**a
 * Checking is password of access to the file is right
 * @param password password passed by user
 * @return true if password is true, false if it is false
 */
bool PasswordManager::checkPassword(const std::string &password) {
    std::ifstream managementRead;
    managementRead.open("../management.txt");
    while (!managementRead.eof()) {
        std::string firstLine;
        managementRead >> firstLine;

        if (password == decryption(firstLine)) {
            managementRead.close();
            return true;
        }
        managementRead.close();
    }
    return false;
}

/**a
 * Function encrypting password passed by user
 * @param oldPassword password passed
 * @return encrypted password passed to file
 */
std::string PasswordManager::encryption(const std::string &oldPassword) {
    std::string newPassword;
    for (char sign: oldPassword) {
        sign += 5;
        newPassword += sign;
    }
    return newPassword;
}

/**a
 * Function decrypting password get from file
 * @param oldPassword password get from file
 * @return encrypted password passed to user
 */
std::string PasswordManager::decryption(const std::string &oldPassword) {
    std::string newPassword;
    for (char sign: oldPassword) {
        sign -= 5;
        newPassword += sign;
    }
    return newPassword;
}

