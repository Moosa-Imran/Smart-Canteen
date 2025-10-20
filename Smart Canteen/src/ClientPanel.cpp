#include "ClientPanel.h"
#include <iostream>
#include <limits>

ClientPanel::ClientPanel(MenuManager* menu, OrderManager* order, SalesManager* sales)
    : menuManager(menu), orderManager(order), salesManager(sales) {}

void ClientPanel::displayClientMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "                 CLIENT PANEL" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. Display Menu" << std::endl;
    std::cout << "2. Add Items to Cart" << std::endl;
    std::cout << "3. View Cart" << std::endl;
    std::cout << "4. Manage Cart" << std::endl;
    std::cout << "5. Checkout" << std::endl;
    std::cout << "6. Back to Main Menu" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Enter your choice: ";
}

void ClientPanel::handleClientOperations() {
    int choice;
    
    do {
        displayClientMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                takeOrder();
                break;
            case 3:
                orderManager->displayCart();
                break;
            case 4:
                manageCart();
                break;
            case 5:
                processCheckout();
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

void ClientPanel::displayMenu() {
    std::cout << "\n=== AVAILABLE MENU ===" << std::endl;
    menuManager->displayMenu();
}

void ClientPanel::takeOrder() {
    char continueOrdering = 'y';
    
    do {
        std::cout << "\n=== ADD ITEMS TO CART ===" << std::endl;
        menuManager->displayMenu();
        
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
        
        std::cout << "\nDo you want to add more items? (y/n): ";
        std::cin >> continueOrdering;
        
    } while (continueOrdering == 'y' || continueOrdering == 'Y');
    
    if (!orderManager->isCartEmpty()) {
        orderManager->displayCart();
    }
}

void ClientPanel::processCheckout() {
    if (orderManager->isCartEmpty()) {
        std::cout << "\nYour cart is empty! Please add items before checkout." << std::endl;
        return;
    }
    
    std::cout << "\n=== CHECKOUT ===" << std::endl;
    orderManager->displayCart();
    
    double total = orderManager->calculateTotal();
    
    std::cout << "\nConfirm your order? (y/n): ";
    char confirm;
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        std::string orderSummary = orderManager->getOrderSummary();
        
        if (salesManager->recordSale(orderSummary, total)) {
            std::cout << "\n" << std::string(50, '=') << std::endl;
            std::cout << "           ORDER CONFIRMED!" << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            std::cout << "Thank you for your order!" << std::endl;
            std::cout << "Your order will be prepared shortly." << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            
            orderManager->clearCart();
        } else {
            std::cout << "Error processing your order. Please try again." << std::endl;
        }
    } else {
        std::cout << "Order cancelled. Your items remain in the cart." << std::endl;
    }
}

void ClientPanel::manageCart() {
    if (orderManager->isCartEmpty()) {
        std::cout << "\nYour cart is empty!" << std::endl;
        return;
    }
    
    int choice;
    
    do {
        std::cout << "\n" << std::string(40, '=') << std::endl;
        std::cout << "           MANAGE CART" << std::endl;
        std::cout << std::string(40, '=') << std::endl;
        std::cout << "1. View Cart" << std::endl;
        std::cout << "2. Update Item Quantity" << std::endl;
        std::cout << "3. Remove Item" << std::endl;
        std::cout << "4. Clear Cart" << std::endl;
        std::cout << "5. Back to Client Panel" << std::endl;
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
                orderManager->displayCart();
                break;
            case 2: {
                orderManager->displayCart();
                std::cout << "\nEnter item name to update: ";
                std::cin.ignore();
                std::string itemName;
                std::getline(std::cin, itemName);
                std::cout << "Enter new quantity (0 to remove): ";
                int newQuantity;
                std::cin >> newQuantity;
                orderManager->updateCartQuantity(itemName, newQuantity);
                break;
            }
            case 3: {
                orderManager->displayCart();
                std::cout << "\nEnter item name to remove: ";
                std::cin.ignore();
                std::string itemName;
                std::getline(std::cin, itemName);
                orderManager->removeFromCart(itemName);
                break;
            }
            case 4: {
                std::cout << "Are you sure you want to clear the cart? (y/n): ";
                char confirm;
                std::cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    orderManager->clearCart();
                }
                break;
            }
            case 5:
                std::cout << "Returning to Client Panel..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
        
        if (choice != 5 && choice >= 1 && choice <= 4) {
            std::cout << "\nPress Enter to continue...";
            if (choice == 1 || choice == 4) std::cin.ignore();
            std::cin.get();
        }
        
    } while (choice != 5);
}