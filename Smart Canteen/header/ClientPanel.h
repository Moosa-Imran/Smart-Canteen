#ifndef CLIENTPANEL_H
#define CLIENTPANEL_H

#include "MenuManager.h"
#include "OrderManager.h"
#include "SalesManager.h"

class ClientPanel {
private:
    MenuManager* menuManager;
    OrderManager* orderManager;
    SalesManager* salesManager;

public:
    ClientPanel(MenuManager* menu, OrderManager* order, SalesManager* sales);
    
    // Display client menu
    void displayClientMenu();
    
    // Handle client operations
    void handleClientOperations();
    
    // Display menu to client
    void displayMenu();
    
    // Take order from client
    void takeOrder();
    
    // Process checkout
    void processCheckout();
    
    // Manage shopping cart
    void manageCart();
};

#endif