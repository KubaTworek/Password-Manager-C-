#include <iostream>
#include <fstream>
#include <vector>
#include "Password.h"
#include<algorithm>

std::string path;

bool sortName (Password a,Password b) { return (a.getName()<b.getName()); }
bool sortCategory (Password a,Password b) { return (a.getCategory()<b.getCategory()); }
bool sortNameAndCategory (Password a,Password b) {
    if(a.getName()<b.getName()){
        return a.getName()<b.getName();
    } else if(a.getName()==b.getName()){
        return (a.getCategory()<b.getCategory());
    }
}

void lookingForPasswords(std::vector<Password> &pass, std::vector<std::string> &categ);

bool checkPassword(std::string password);

std::string szyfrowanie(std::string oldPassword);

std::string odszyfrowanie(std::string oldPassword);

void odczytCategories(std::vector<std::string> &vector);

void saveCategories(std::vector<std::string> &vector);

void choosingFile(std::vector<Password> &vector);

void passwordManagement(std::vector<Password> &pass, std::vector<std::string> &categ);

void editPassword(std::vector<Password> &vector);

void addPassword(std::vector<Password> &pass, std::vector<std::string> &categ);

void deletePassword(std::vector<Password> &vector);

void deleteCategory(std::vector<Password> &pass, std::vector<std::string> &categ);

void addCategory(std::vector<std::string> &vector);

void writeOutPasswords(std::vector<Password> &vector);

void writeOutPasswords(std::vector<Password> &vector, std::string category);

void writeOutPasswordsByName(std::vector<Password> &vector, std::string name);

void writeOutCategories(std::vector<std::string> &vector);

void sortPasswords(std::vector<Password> &vector);

void savePasswords(std::vector<Password> &vector);

int main() {
    std::vector<Password> passwords;
    std::vector<std::string> categories;
    odczytCategories(categories);
    choosingFile(passwords);
    passwordManagement(passwords,categories);

    return 0;
}

void odczytCategories(std::vector<std::string> &vector){
    std::ifstream Wodczyt;
    std::string wiersz;
    Wodczyt.open("../categories.txt");
    while (!Wodczyt.eof()) {
        std::string category;
        Wodczyt >> category;
        vector.push_back(category);
    }
    Wodczyt.close();
}

void saveCategories(std::vector<std::string> &vector){
    std::string str = "";
    std::ofstream zapis("../categories.txt");
    for (std::string category : vector) {
        str += "\n" + category;
    }
    zapis<<str;
    zapis.close();
}

void choosingFile(std::vector<Password> &vector) {
    while (true) {

    std::cout << "Wybierz opcje." << std::endl;
    std::cout << "1. Podaj sciezke do pliku." << std::endl;
    std::cout << "2. Wybierz plik standardowy." << std::endl;
    std::cout << "0. Zakoncz." << std::endl;

    int choose;

    std::cin >> choose;

        switch (choose) {
            case 1: {
                std::string &absolutePath = path;
                std::cout << "Podaj sciezke absolutna: " << std::endl;
                std::cin >> absolutePath;
                std::ifstream Wodczyt1;
                std::string wiersz1;
                Wodczyt1.open(absolutePath);
                while (!Wodczyt1.eof()) {
                    std::string a, name, c, passwordText, e, category, g, service, i, login;
                    Wodczyt1 >> a >> name >> c >> passwordText >> e >> category >> g >> service >> i >> login;

                    std::string newPassword = odszyfrowanie(passwordText);

                    Password password(name, newPassword, category);
                    password.setService(service);
                    password.setLogin(login);
                    vector.push_back(password);
                }
                Wodczyt1.close();
                break;
            }
            case 2: {
                while(true){
                    std::string enteringPassword;
                    std::cout << "Podaj haslo dostepu: " << std::endl;
                    std::cin >> enteringPassword;

                    if(checkPassword(enteringPassword)){
                        std::ofstream managementOdczyt;
                        managementOdczyt.open("../management.txt", std::ios::out|std::ios::app);
                        managementOdczyt << "\n" + std::string(__TIME__) + " SUCCEED";
                        managementOdczyt.close();
                        std::ifstream Wodczyt2;
                        std::string wiersz2;
                        std::string &standardPath = path;
                        standardPath = "../passwords.txt";
                        Wodczyt2.open(standardPath);
                        while (!Wodczyt2.eof()) {
                            std::string a, name, c, passwordText, e, category, g, service, i, login;
                            Wodczyt2 >> a >> name >> c >> passwordText >> e >> category >> g >> service >> i >> login;
                            if(a.empty()){
                                continue;
                            }

                            std::string newPassword = odszyfrowanie(passwordText);

                            Password password(name, newPassword, category);
                            password.setService(service);
                            password.setLogin(login);
                            vector.push_back(password);
                        }
                        Wodczyt2.close();
                        break;
                    } else {
                        std::ofstream managementOdczyt;
                        managementOdczyt.open("../management.txt", std::ios::out|std::ios::app);
                        managementOdczyt << "\n" + std::string(__TIME__) + " FAILED";
                        managementOdczyt.close();
                        std::cout << "Nieprawidlowe haslo." << std::endl;
                    }
                }
                break;
            }
            case 0:
                break;
        }
        break;
    }

}

void passwordManagement(std::vector<Password> &pass, std::vector<std::string> &categ) {
    while (true) {
    std::cout <<  std::endl;
    std::cout << "Wybierz opcje." << std::endl;
    std::cout << "1. Wyszukaj hasla." << std::endl;
    std::cout << "2. Posortuj hasla." << std::endl;
    std::cout << "3. Dodaj haslo." << std::endl;
    std::cout << "4. Edytuj haslo." << std::endl;
    std::cout << "5. Usun haslo." << std::endl;
    std::cout << "6. Dodaj kategorie." << std::endl;
    std::cout << "7. Usun kategorie." << std::endl;
    std::cout << "0. Zakoncz." << std::endl;

    int choose;
    std::cin >> choose;


        switch (choose) {
            case 1:
                lookingForPasswords(pass,categ);
                break;
            case 2:
                sortPasswords(pass);
                break;
            case 3:
                addPassword(pass,categ);
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
                writeOutCategories(categ);
                addCategory(categ);
                break;
            case 7:
                writeOutCategories(categ);
                deleteCategory(pass,categ);
                break;
            case 0:
                exit(0);
            default:
                break;
        }
    }
}

void lookingForPasswords(std::vector<Password> &pass, std::vector<std::string> &categ){
    std::string name;
    int choose, categoryId;
    std::cout << "Chcesz wyszukac hasla wedlug?" << std::endl;
    std::cout << "1. Kategorii" << std::endl;
    std::cout << "2. Nazwy" << std::endl;
    std::cin >> choose;
    if(choose == 1){
        writeOutCategories(categ);
        std::cout << "Podaj numer kategorii: ";
        std::cin >> categoryId;
        writeOutPasswords(pass, categ.at(categoryId-1));
    } else if(choose == 2){
        std::cout << "Podaj nazwe hasla: ";
        std::cin >> name;
        writeOutPasswordsByName(pass, name);
    } else {
        std::cout << "Niepoprawny numer" << std::endl;
    }

}

void writeOutPasswords(std::vector<Password> &vector) {
    int i = 1;
    for (Password password: vector) {
        std::cout << i++ << ". " << password.getName() << std::endl;
    }
}

void writeOutPasswords(std::vector<Password> &vector, std::string category) {
    int i = 1;
    for (Password password: vector) {
        if(password.getCategory() == category){
            std::cout << i++ << ". " << password.getName() << std::endl;
        }
    }
}

void writeOutPasswordsByName(std::vector<Password> &vector, std::string name){
    for (Password password: vector) {
        if(password.getName() == name){
            std::cout << "Nazwa: " << password.getName() << std::endl;
            std::cout << "Haslo: " << password.getPasswordText() << std::endl;
            std::cout << "Kategoria: " << password.getCategory() << std::endl;
            std::cout << "StronaWWW/Serwis: " << password.getService() << std::endl;
            std::cout << "Login: " << password.getLogin() << std::endl;
        }
    }
}

void writeOutCategories(std::vector<std::string> &vector) {
    int i = 1;
    for (std::string category : vector) {
        std::cout << i++ << ". " << category << std::endl;
    }
}

void editPassword(std::vector<Password> &vector) {
    int choosePassword;
    int chooseEdit;
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
    }
    savePasswords(vector);
    std::cout << "Zmieniles dana w hasle" << std::endl;
}

void deletePassword(std::vector<Password> &vector) {
    int choosePassword;
    char confirm;
    std::cout << "Wybierz numer hasla, ktore chcesz usunac: " << std::endl;
    std::cin >> choosePassword;
    std::cout << "Na pewno chcesz to usunac? (y/n) " << std::endl;
    std::cin >> confirm;
    if(tolower(confirm)=='y'){
        vector.erase(vector.cbegin()+choosePassword-1);
        savePasswords(vector);
        std::cout << "Usunales haslo" << std::endl;
    } else {
        std::cout << "Nie usunales hasla" << std::endl;
    }
}

void addCategory(std::vector<std::string> &vector){
    std::string category;
    std::cout << "Napisz nazwe kategorii, ktora chcesz dodac: " << std::endl;
    std::cin >> category;
    vector.push_back(category);
    saveCategories(vector);
    std::cout << "Dodales kategorie." << std::endl;
}

void deleteCategory(std::vector<Password> &pass, std::vector<std::string> &categ) {
    int chooseCategory;
    char confirm;
    std::cout << "Wybierz numer kategorii, ktora chcesz usunac: " << std::endl;
    std::cin >> chooseCategory;
    std::cout << "Wiaze sie to z usunieciem wszystkich hasel z tej kategorii. Na pewno chcesz to usunac? (y/n) " << std::endl;
    std::cin >> confirm;
    if(tolower(confirm)=='y'){
        for (Password password : pass) {
            if(password.getCategory() == categ.at(chooseCategory-1)){
                pass.erase(pass.cbegin()+(chooseCategory-1));
            }
        }
        categ.erase(categ.cbegin()+chooseCategory-1);
        saveCategories(categ);
        std::cout << "Usunales kategorie i hasla" << std::endl;
    } else {
        std::cout << "Nie usunales kategorii" << std::endl;
    }
}

void addPassword(std::vector<Password> &pass, std::vector<std::string> &categ){
    std::string name, passwordText, category, service, login;
    char confirmService, confirmLogin;
    int categoryId;
    std::cout << "Wybierz nazwe hasla, ktora chcesz dodac: " << std::endl;
    std::cin >> name;
    std::cout << "Napisz haslo, ktora chcesz dodac: " << std::endl;
    std::cin >> passwordText;

    writeOutCategories(categ);
    std::cout << "Wybierz kategorie(numer), ktora ma miec haslo: " << std::endl;
    std::cin >> categoryId;
    category = categ.at(categoryId-1);
    Password password(name, passwordText, category);

    std::cout << "Chcesz wpisac serwis do ktorego nalezy haslo? (y/n)";
    std::cin >> confirmService;
    if(tolower(confirmService)=='y'){
        std::cout << "Wpisz: " << std::endl;
        std::cin >> service;
        password.setService(service);
    } else {
        password.setService("brak");
    }

    std::cout << "Chcesz wpisac login do ktorego nalezy haslo? (y/n)";
    std::cin >> confirmLogin;
    if(tolower(confirmLogin)=='y'){
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

void sortPasswords(std::vector<Password> &vector){

    std::cout <<  std::endl;
    std::cout << "Wybierz opcje." << std::endl;
    std::cout << "1. Sortuj wedlug nazwy." << std::endl;
    std::cout << "2. Sortuj wedlug kategorii." << std::endl;
    std::cout << "3. Sortuj wedlug nazwy i kategorii." << std::endl;
    std::cout << "0. Zakoncz." << std::endl;

    int choose;
    std::cin >> choose;


    switch (choose) {
        case 1:
        {
            sort(vector.begin(),vector.end(), sortName);
            savePasswords(vector);
            writeOutPasswords(vector);
            //sortowanie wedlug nazwy
        }
            break;
        case 2:
        {
            sort(vector.begin(),vector.end(), sortCategory);
            savePasswords(vector);
            writeOutPasswords(vector);
            //sortowanie wedlug kategorii
        }
            break;
        case 3:
        {
            sort(vector.begin(),vector.end(), sortNameAndCategory);
            savePasswords(vector);
            writeOutPasswords(vector);
            //sortowanie wedlug nazwy i kategorii
        }
            break;
        case 0:
        default:
            break;
    }
}

void savePasswords(std::vector<Password> &vector){
    std::string str = "";
    std::ofstream zapis(path);
    for (Password password: vector) {
        str += "Nazwa: " + password.getName() + "\n"
                + "Haslo: " + szyfrowanie(password.getPasswordText()) + "\n"
                + "Kategoria: " + password.getCategory() + "\n"
                + "StronaWWW/Serwis: " + password.getService() + "\n"
                + "Login: " + password.getLogin() + "\n";
    }
    zapis<<str;
    zapis.close();
}

std::string szyfrowanie(std::string oldPassword){
    std::string newPassword = "";
    for ( char znak : oldPassword ){
        znak += 5;
        newPassword += znak;
    }
    return newPassword;
}

std::string odszyfrowanie(std::string oldPassword){
    std::string newPassword = "";
    for ( char znak : oldPassword ){
        znak -= 5;
        newPassword += znak;
    }
    return newPassword;
}

bool checkPassword(std::string password){
    std::ifstream managementOdczyt;
    managementOdczyt.open("../management.txt");
    while (!managementOdczyt.eof()) {
        std::string firstLine;
        managementOdczyt >> firstLine;

        if(password == odszyfrowanie(firstLine)) {
            managementOdczyt.close();
            return true;
        } else {
            managementOdczyt.close();
            return false;
        }
    }
}