#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <string>
#include <vector>
#include <map>
#include "MenuManager.h"

struct OrderItem {
    std::string name;
    int quantity;
    double unitPrice;
    double totalPrice;
};

class OrderManager {
private:
    std::vector<OrderItem> cart;
    MenuManager* menuManager;

public:
    OrderManager(MenuManager* menu);
    
    // Display available menu
    void displayAvailableMenu();
    
    // Add item to cart
    bool addToCart(const std::string& itemName, int quantity);
    
    // Remove item from cart
    bool removeFromCart(const std::string& itemName);
    
    // Update quantity in cart
    bool updateCartQuantity(const std::string& itemName, int newQuantity);
    
    // Display cart
    void displayCart();
    
    // Calculate total cost
    double calculateTotal();
    
    // Clear cart
    void clearCart();
    
    // Get cart items
    std::vector<OrderItem> getCart() const;
    
    // Check if cart is empty
    bool isCartEmpty() const;
    
    // Generate order summary string
    std::string getOrderSummary();
};

#endif