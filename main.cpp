#include <iostream>
#include <fstream>
#include <vector>
#include "Password.h"

void choosingFile(std::vector<Password>& vector);
void passwordManagement();

int main() {
    std::vector < Password > passwords;
    choosingFile(passwords);
    passwordManagement();


    return 0;
}

void choosingFile(std::vector<Password>& vector){
    std::cout << "Wybierz opcje." << std::endl;
    std::cout << "1. Podaj sciezke do pliku." << std::endl;
    std::cout << "2. Wybierz plik." << std::endl;
    std::cout << "0. Zakoncz." << std::endl;

    int choose;
    std::string absolutePath;

    std::cin >> choose;

    while(true){
        switch(choose){
            case 1:
            {
                std::cout << "Podaj sciezke absolutna: " << std::endl;
                std::cin >> absolutePath;
                std::ifstream Wodczyt;
                std::string wiersz;
                Wodczyt.open(absolutePath);
                while (!Wodczyt.eof()){
                    std::string a,name,c,passwordText,e,category,g,service,i,login;
                    Wodczyt >> a >> name >> c >> passwordText >> e >> category >> g >> service >> i >> login;
                    Password password(name,passwordText,category,service,login);
                    vector.push_back(password);
                }
                Wodczyt.close();
                break;
            }
            case 2:
                break;
            case 0:
                break;
        }
        break;
    }
}

void passwordManagement(){
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

    while(true){
        switch(choose){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 0:
                break;
        }
        break;
    }
}