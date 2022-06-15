#include <iostream>
#include <fstream>
#include <vector>
#include "Password.h"
#include "PasswordManager.h"

std::vector<Password> choosingFile();

int main() {
    PasswordManager PasswordManager(choosingFile());
    return 0;
}

std::vector<Password> choosingFile() {
    std::vector<Password> vector;
    while (true) {
        std::cout << "Wybierz opcje." << std::endl;
        std::cout << "1. Podaj sciezke do pliku." << std::endl;
        std::cout << "2. Wybierz plik standardowy." << std::endl;
        std::cout << "0. Zakoncz." << std::endl;

        int choose;

        std::cin >> choose;

        switch (choose) {
            case 1: {
                std::string absolutePath;
                std::cout << "Podaj sciezke absolutna: " << std::endl;
                std::cin >> absolutePath;
                std::ifstream read1;
                read1.open(absolutePath);
                while (!read1.eof()) {
                    std::string a, name, c, passwordText, e, category, g, service, i, login;
                    read1 >> a >> name >> c >> passwordText >> e >> category >> g >> service >> i >> login;

                    std::string newPassword = PasswordManager::decryption(passwordText);

                    Password password(name, newPassword, category);
                    password.setService(service);
                    password.setLogin(login);
                    vector.push_back(password);
                }
                read1.close();
                break;
            }
            case 2: {
                while (true) {
                    std::string enteringPassword;
                    std::cout << "Podaj haslo dostepu: " << std::endl;
                    std::cin >> enteringPassword;

                    if (PasswordManager::checkPassword(enteringPassword)) {
                        std::ofstream managementOdczyt;
                        managementOdczyt.open("../management.txt", std::ios::out | std::ios::app);
                        managementOdczyt << "\n" + std::string(__TIME__) + " SUCCEED";
                        managementOdczyt.close();
                        std::ifstream read2;
                        read2.open("../passwords.txt");
                        while (!read2.eof()) {
                            std::string a, name, c, passwordText, e, category, g, service, i, login;
                            read2 >> a >> name >> c >> passwordText >> e >> category >> g >> service >> i >> login;
                            if (a.empty()) {
                                continue;
                            }

                            std::string newPassword = PasswordManager::decryption(passwordText);

                            Password password(name, newPassword, category);
                            password.setService(service);
                            password.setLogin(login);
                            vector.push_back(password);
                        }
                        read2.close();
                        break;
                    } else {
                        std::ofstream managamentRead;
                        managamentRead.open("../management.txt", std::ios::out | std::ios::app);
                        managamentRead << "\n" + std::string(__TIME__) + " FAILED";
                        managamentRead.close();
                        std::cout << "Nieprawidlowe haslo." << std::endl;
                    }
                }
                break;
            }
            case 0:
                exit(0);
            default:
                continue;
        }
        break;
    }
    return vector;
}





















