#include <iostream>
#include <fstream>
#include <vector>
#include "Password.h"
#include "PasswordManager.h"

std::vector<Password> choosingFile();

void readingFromFile(std::ifstream &read, std::vector<Password> &vector);

int main() {
    PasswordManager PasswordManager(choosingFile());
    return 0;
}

/**a
 * CReading from choosen file all passwords to use in application
 * @return vector of passwords
 */
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
                readingFromFile(read1, vector);
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
                        readingFromFile(read2, vector);
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

/**a
 * Reading passwords from file and adding them to vector
 * @param read stream where we get access to file with passwords
 * @param vector vector of passwords
 */
void readingFromFile(std::ifstream &read, std::vector<Password> &vector) {
    while (!read.eof()) {
        std::string a, name, passwordText, category, service, login;
        read >> a >> name >> passwordText >> category >> service >> login;
        if (a.empty()) {
            continue;
        }

        std::string newPassword = PasswordManager::decryption(passwordText);
        std::string newName = PasswordManager::decryption(name);
        std::string newCategory = PasswordManager::decryption(category);
        std::string newService = PasswordManager::decryption(service);
        std::string newLogin = PasswordManager::decryption(login);

        Password password(newName, newPassword, newCategory);
        password.setService(newService);
        password.setLogin(newLogin);
        vector.push_back(password);
    }
}



















