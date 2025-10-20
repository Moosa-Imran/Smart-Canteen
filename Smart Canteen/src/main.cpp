#include <iostream>
#include <limits>
#include "MenuManager.h"
#include "OrderManager.h"
#include "SalesManager.h"
#include "Reports.h"
#include "AdminPanel.h"
#include "ClientPanel.h"

class SmartCanteenSystem {
private:
    MenuManager* menuManager;
    OrderManager* orderManager;
    SalesManager* salesManager;
    Reports* reports;
    AdminPanel* adminPanel;
    ClientPanel* clientPanel;

public:
    SmartCanteenSystem() {
        // Initialize all managers with file paths
        menuManager = new MenuManager("Text_files/menu.txt");
        salesManager = new SalesManager("Text_files/sales.txt");
        orderManager = new OrderManager(menuManager);
        reports = new Reports(salesManager);
        adminPanel = new AdminPanel(menuManager, salesManager, reports);
        clientPanel = new ClientPanel(menuManager, orderManager, salesManager);
    }

    ~SmartCanteenSystem() {
        delete menuManager;
        delete orderManager;
        delete salesManager;
        delete reports;
        delete adminPanel;
        delete clientPanel;
    }

    void displayMainMenu() {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "                SMART CANTEEN SYSTEM" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "1. Display Menu" << std::endl;
        std::cout << "2. Take Order (Client Panel)" << std::endl;
        std::cout << "3. View Daily Report" << std::endl;
        std::cout << "4. Update Item Price (Admin)" << std::endl;
        std::cout << "5. View Sales Log" << std::endl;
        std::cout << "6. Admin Panel" << std::endl;
        std::cout << "7. Client Panel" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "Enter your choice: ";
    }

    void displayWelcomeMessage() {
        std::cout << std::string(70, '*') << std::endl;
        std::cout << "*" << std::string(68, ' ') << "*" << std::endl;
        std::cout << "*" << std::string(20, ' ') << "WELCOME TO SMART CANTEEN SYSTEM" 
                  << std::string(17, ' ') << "*" << std::endl;
        std::cout << "*" << std::string(68, ' ') << "*" << std::endl;
        std::cout << "*" << std::string(15, ' ') << "Your Digital Solution for Food Ordering" 
                  << std::string(14, ' ') << "*" << std::endl;
        std::cout << "*" << std::string(68, ' ') << "*" << std::endl;
        std::cout << std::string(70, '*') << std::endl;
    }

    void takeOrder() {
        std::cout << "\n=== QUICK ORDER ===" << std::endl;
        menuManager->displayMenu();
        
        char continueOrdering = 'y';
        
        do {
            std::cout << "\nEnter item name: ";
            std::cin.ignore();
            std::string itemName;
            std::getline(std::cin, itemName);
            
            std::cout << "Enter quantity: ";
            int quantity;
            std::cin >> quantity;
            
            if (quantity <= 0) {
                std::cout << "Invalid quantity! Please enter a positive number." << std::endl;
            } else {
                orderManager->addToCart(itemName, quantity);
            }
            
            std::cout << "\nAdd more items? (y/n): ";
            std::cin >> continueOrdering;
            
        } while (continueOrdering == 'y' || continueOrdering == 'Y');
        
        if (!orderManager->isCartEmpty()) {
            orderManager->displayCart();
            
            std::cout << "\nProceed to checkout? (y/n): ";
            char checkout;
            std::cin >> checkout;
            
            if (checkout == 'y' || checkout == 'Y') {
                double total = orderManager->calculateTotal();
                std::string orderSummary = orderManager->getOrderSummary();
                
                if (salesManager->recordSale(orderSummary, total)) {
                    std::cout << "\n" << std::string(50, '=') << std::endl;
                    std::cout << "           ORDER CONFIRMED!" << std::endl;
                    std::cout << std::string(50, '=') << std::endl;
                    std::cout << "Thank you for your order!" << std::endl;
                    std::cout << std::string(50, '=') << std::endl;
                    
                    orderManager->clearCart();
                }
            }
        }
    }

    void updateItemPriceQuick() {
        std::cout << "\n=== QUICK PRICE UPDATE ===" << std::endl;
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

    void run() {
        displayWelcomeMessage();
        
        int choice;
        
        do {
            displayMainMenu();
            std::cin >> choice;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter a number." << std::endl;
                continue;
            }
            
            switch (choice) {
                case 1:
                    std::cout << "\n=== CURRENT MENU ===" << std::endl;
                    menuManager->displayMenu();
                    break;
                case 2:
                    takeOrder();
                    break;
                case 3:
                    reports->generateDailyReport();
                    break;
                case 4:
                    updateItemPriceQuick();
                    break;
                case 5:
                    salesManager->displaySalesLog();
                    break;
                case 6:
                    adminPanel->handleAdminOperations();
                    break;
                case 7:
                    clientPanel->handleClientOperations();
                    break;
                case 8:
                    std::cout << "\n" << std::string(50, '=') << std::endl;
                    std::cout << "     Thank you for using Smart Canteen!" << std::endl;
                    std::cout << "              Have a great day!" << std::endl;
                    std::cout << std::string(50, '=') << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice! Please try again." << std::endl;
            }
            
            if (choice != 8) {
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
            }
            
        } while (choice != 8);
    }
};

int main() {
    try {
        SmartCanteenSystem canteenSystem;
        canteenSystem.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}