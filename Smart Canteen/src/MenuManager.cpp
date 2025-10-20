#include "MenuManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

MenuManager::MenuManager(const std::string& filePath) : menuFilePath(filePath) {
    loadMenu();
}

bool MenuManager::loadMenu() {
    menu.clear();
    std::ifstream file(menuFilePath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open menu file: " << menuFilePath << std::endl;
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, priceStr;
        
        if (std::getline(ss, name, ',') && std::getline(ss, priceStr)) {
            try {
                double price = std::stod(priceStr);
                menu.push_back({name, price});
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }
    }
    
    file.close();
    return true;
}

bool MenuManager::saveMenu() {
    std::ofstream file(menuFilePath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open menu file for writing: " << menuFilePath << std::endl;
        return false;
    }
    
    for (const auto& item : menu) {
        file << item.name << "," << item.price << std::endl;
    }
    
    file.close();
    return true;
}

void MenuManager::displayMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "                   MENU" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::left << std::setw(20) << "Item Name" 
              << std::right << std::setw(15) << "Price (Rs.)" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (size_t i = 0; i < menu.size(); ++i) {
        std::cout << std::left << std::setw(3) << (i + 1) << ". "
                  << std::setw(16) << menu[i].name 
                  << std::right << std::setw(15) << std::fixed 
                  << std::setprecision(2) << menu[i].price << std::endl;
    }
    std::cout << std::string(50, '=') << std::endl;
}

void MenuManager::addItem(const std::string& name, double price) {
    menu.push_back({name, price});
    saveMenu();
}

bool MenuManager::updateItemPrice(const std::string& name, double newPrice) {
    for (auto& item : menu) {
        if (item.name == name) {
            item.price = newPrice;
            saveMenu();
            return true;
        }
    }
    return false;
}

bool MenuManager::deleteItem(const std::string& name) {
    auto it = std::find_if(menu.begin(), menu.end(),
        [&name](const MenuItem& item) { return item.name == name; });
    
    if (it != menu.end()) {
        menu.erase(it);
        saveMenu();
        return true;
    }
    return false;
}

std::vector<MenuItem> MenuManager::getMenu() const {
    return menu;
}

MenuItem* MenuManager::findItem(const std::string& name) {
    for (auto& item : menu) {
        if (item.name == name) {
            return &item;
        }
    }
    return nullptr;
}

double MenuManager::getItemPrice(const std::string& name) {
    MenuItem* item = findItem(name);
    return item ? item->price : -1.0;
}