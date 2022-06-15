//
// Created by Kuba on 15.06.2022.
//

#ifndef PASSWORDMANAGER_CATEGORYMANAGER_H
#define PASSWORDMANAGER_CATEGORYMANAGER_H


#include <string>
#include <vector>
#include "Password.h"

class CategoryManager {
    std::vector<std::string> categories;

public:
    CategoryManager();

    static void addCategory(std::vector<std::string> &vector);

    static void deleteCategory(std::vector<Password> &pass, std::vector<std::string> &categ);

    static void writeOutCategories(std::vector<std::string> &vector);

    std::vector<std::string> readCategories();

    static void saveCategories(std::vector<std::string> &vector);

    const std::vector<std::string> &getCategories() const;

    void setCategories(const std::vector<std::string> &categories);

};


#endif //PASSWORDMANAGER_CATEGORYMANAGER_H
