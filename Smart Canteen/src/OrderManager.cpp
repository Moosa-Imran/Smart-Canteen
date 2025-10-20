#include "OrderManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

OrderManager::OrderManager(MenuManager* menu) : menuManager(menu) {}

void OrderManager::displayAvailableMenu() {
    menuManager->displayMenu();
}

bool OrderManager::addToCart(const std::string& itemName, int quantity) {
    if (quantity <= 0) {
        std::cout << "Invalid quantity. Please enter a positive number." << std::endl;
        return false;
    }
    
    double unitPrice = menuManager->getItemPrice(itemName);
    if (unitPrice == -1.0) {
        std::cout << "Item not found in menu: " << itemName << std::endl;
        return false;
    }
    
    // Check if item already exists in cart
    for (auto& cartItem : cart) {
        if (cartItem.name == itemName) {
            cartItem.quantity += quantity;
            cartItem.totalPrice = cartItem.quantity * cartItem.unitPrice;
            std::cout << "Updated quantity for " << itemName << " in cart." << std::endl;
            return true;
        }
    }
    
    // Add new item to cart
    OrderItem newItem;
    newItem.name = itemName;
    newItem.quantity = quantity;
    newItem.unitPrice = unitPrice;
    newItem.totalPrice = quantity * unitPrice;
    
    cart.push_back(newItem);
    std::cout << "Added " << quantity << " " << itemName << "(s) to cart." << std::endl;
    return true;
}

bool OrderManager::removeFromCart(const std::string& itemName) {
    auto it = std::find_if(cart.begin(), cart.end(),
        [&itemName](const OrderItem& item) { return item.name == itemName; });
    
    if (it != cart.end()) {
        cart.erase(it);
        std::cout << "Removed " << itemName << " from cart." << std::endl;
        return true;
    }
    
    std::cout << "Item not found in cart: " << itemName << std::endl;
    return false;
}

bool OrderManager::updateCartQuantity(const std::string& itemName, int newQuantity) {
    if (newQuantity <= 0) {
        return removeFromCart(itemName);
    }
    
    for (auto& cartItem : cart) {
        if (cartItem.name == itemName) {
            cartItem.quantity = newQuantity;
            cartItem.totalPrice = newQuantity * cartItem.unitPrice;
            std::cout << "Updated quantity for " << itemName << " to " << newQuantity << std::endl;
            return true;
        }
    }
    
    std::cout << "Item not found in cart: " << itemName << std::endl;
    return false;
}

void OrderManager::displayCart() {
    if (cart.empty()) {
        std::cout << "\nYour cart is empty." << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "                        YOUR CART" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << std::left << std::setw(20) << "Item Name"
              << std::setw(10) << "Quantity"
              << std::setw(15) << "Unit Price"
              << std::setw(15) << "Total Price" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    double grandTotal = 0.0;
    for (const auto& item : cart) {
        std::cout << std::left << std::setw(20) << item.name
                  << std::setw(10) << item.quantity
                  << std::setw(15) << std::fixed << std::setprecision(2) << item.unitPrice
                  << std::setw(15) << item.totalPrice << std::endl;
        grandTotal += item.totalPrice;
    }
    
    std::cout << std::string(70, '-') << std::endl;
    std::cout << std::right << std::setw(50) << "GRAND TOTAL: Rs. "
              << std::fixed << std::setprecision(2) << grandTotal << std::endl;
    std::cout << std::string(70, '=') << std::endl;
}

double OrderManager::calculateTotal() {
    double total = 0.0;
    for (const auto& item : cart) {
        total += item.totalPrice;
    }
    return total;
}

void OrderManager::clearCart() {
    cart.clear();
    std::cout << "Cart cleared." << std::endl;
}

std::vector<OrderItem> OrderManager::getCart() const {
    return cart;
}

bool OrderManager::isCartEmpty() const {
    return cart.empty();
}

std::string OrderManager::getOrderSummary() {
    std::stringstream ss;
    bool first = true;
    
    for (const auto& item : cart) {
        if (!first) {
            ss << ", ";
        }
        ss << item.name << " x" << item.quantity;
        first = false;
    }
    
    return ss.str();
}