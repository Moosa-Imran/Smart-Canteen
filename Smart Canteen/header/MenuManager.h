#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <string>
#include <vector>
#include <map>

struct MenuItem {
    std::string name;
    double price;
};

class MenuManager {
private:
    std::vector<MenuItem> menu;
    std::string menuFilePath;

public:
    MenuManager(const std::string& filePath);
    
    // Load menu from file
    bool loadMenu();
    
    // Save menu to file
    bool saveMenu();
    
    // Display menu
    void displayMenu();
    
    // Add new item
    void addItem(const std::string& name, double price);
    
    // Update item price
    bool updateItemPrice(const std::string& name, double newPrice);
    
    // Delete item
    bool deleteItem(const std::string& name);
    
    // Get menu items
    std::vector<MenuItem> getMenu() const;
    
    // Find item by name
    MenuItem* findItem(const std::string& name);
    
    // Get item price
    double getItemPrice(const std::string& name);
};

#endif