#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include "MenuManager.h"
#include "SalesManager.h"
#include "Reports.h"

class AdminPanel {
private:
    MenuManager* menuManager;
    SalesManager* salesManager;
    Reports* reports;

public:
    AdminPanel(MenuManager* menu, SalesManager* sales, Reports* rep);
    
    // Display admin menu
    void displayAdminMenu();
    
    // Handle admin operations
    void handleAdminOperations();
    
    // Update item price
    void updateItemPrice();
    
    // Delete menu item
    void deleteMenuItem();
    
    // Add new menu item
    void addMenuItem();
    
    // View sales reports
    void viewReports();
    
    // View sales log
    void viewSalesLog();
    
    // Manage menu items
    void manageMenuItems();
};

#endif