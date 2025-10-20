#include "AdminPanel.h"
#include <iostream>
#include <limits>

AdminPanel::AdminPanel(MenuManager* menu, SalesManager* sales, Reports* rep)
    : menuManager(menu), salesManager(sales), reports(rep) {}

void AdminPanel::displayAdminMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "                 ADMIN PANEL" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. Manage Menu Items" << std::endl;
    std::cout << "2. Update Item Price" << std::endl;
    std::cout << "3. View Sales Reports" << std::endl;
    std::cout << "4. View Sales Log" << std::endl;
    std::cout << "5. View Analytics" << std::endl;
    std::cout << "6. Back to Main Menu" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Enter your choice: ";
}

void AdminPanel::handleAdminOperations() {
    int choice;
    
    do {
        displayAdminMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                manageMenuItems();
                break;
            case 2:
                updateItemPrice();
                break;
            case 3:
                viewReports();
                break;
            case 4:
                viewSalesLog();
                break;
            case 5:
                reports->displayAnalytics();
                break;
            case 6:
                std::cout << "Returning to main menu..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
        
        if (choice != 6) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
        
    } while (choice != 6);
}

void AdminPanel::updateItemPrice() {
    std::cout << "\n=== UPDATE ITEM PRICE ===" << std::endl;
    menuManager->displayMenu();
    
    std::cout << "\nEnter item name: ";
    std::cin.ignore();
    std::string itemName;
    std::getline(std::cin, itemName);
    
    std::cout << "Enter new price: Rs. ";
    double newPrice;
    std::cin >> newPrice;
    
    if (newPrice <= 0) {
        std::cout << "Invalid price! Price must be positive." << std::endl;
        return;
    }
    
    if (menuManager->updateItemPrice(itemName, newPrice)) {
        std::cout << "Price updated successfully!" << std::endl;
        std::cout << itemName << " is now priced at Rs. " << newPrice << std::endl;
    } else {
        std::cout << "Item not found: " << itemName << std::endl;
    }
}

void AdminPanel::deleteMenuItem() {
    std::cout << "\n=== DELETE MENU ITEM ===" << std::endl;
    menuManager->displayMenu();
    
    std::cout << "\nEnter item name to delete: ";
    std::string itemName;
    std::getline(std::cin, itemName);
    
    std::cout << "Are you sure you want to delete '" << itemName << "'? (y/n): ";
    char confirm;
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        if (menuManager->deleteItem(itemName)) {
            std::cout << "Item deleted successfully!" << std::endl;
        } else {
            std::cout << "Item not found: " << itemName << std::endl;
        }
    } else {
        std::cout << "Deletion cancelled." << std::endl;
    }
}

void AdminPanel::addMenuItem() {
    std::cout << "\n=== ADD NEW MENU ITEM ===" << std::endl;
    
    std::cout << "Enter item name: ";
    std::string itemName;
    std::getline(std::cin, itemName);
    
    std::cout << "Enter price: Rs. ";
    double price;
    std::cin >> price;
    
    if (price <= 0) {
        std::cout << "Invalid price! Price must be positive." << std::endl;
        return;
    }
    
    menuManager->addItem(itemName, price);
    std::cout << "Item added successfully!" << std::endl;
    std::cout << itemName << " added at Rs. " << price << std::endl;
}

void AdminPanel::viewReports() {
    reports->generateDailyReport();
}

void AdminPanel::viewSalesLog() {
    salesManager->displaySalesLog();
}

void AdminPanel::manageMenuItems() {
    int choice;
    
    do {
        std::cout << "\n" << std::string(40, '=') << std::endl;
        std::cout << "           MANAGE MENU ITEMS" << std::endl;
        std::cout << std::string(40, '=') << std::endl;
        std::cout << "1. View Current Menu" << std::endl;
        std::cout << "2. Add New Item" << std::endl;
        std::cout << "3. Delete Item" << std::endl;
        std::cout << "4. Back to Admin Panel" << std::endl;
        std::cout << std::string(40, '=') << std::endl;
        std::cout << "Enter your choice: ";
        
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                menuManager->displayMenu();
                break;
            case 2:
                std::cin.ignore();
                addMenuItem();
                break;
            case 3:
                std::cin.ignore();
                deleteMenuItem();
                break;
            case 4:
                std::cout << "Returning to Admin Panel..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
        
        if (choice != 4) {
            std::cout << "\nPress Enter to continue...";
            if (choice == 1) std::cin.ignore();
            std::cin.get();
        }
        
    } while (choice != 4);
}