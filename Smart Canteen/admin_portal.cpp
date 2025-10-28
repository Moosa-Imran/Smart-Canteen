#include "common.h"

using namespace std;

// Function to display admin menu
void displayAdminMenu() {
    displayHeader("ADMIN PANEL");
    cout << "1. View Menu" << endl;
    cout << "2. Add New Item" << endl;
    cout << "3. Update Item Price" << endl;
    cout << "4. Delete Item" << endl;
    cout << "5. View Sales Report" << endl;
    cout << "6. View Sales History" << endl;
    cout << "7. Exit Admin Panel" << endl;
    cout << string(60, '=') << endl;
    cout << "Enter your choice: ";
}

// Function to add new menu item
void addNewItem() {
    displayHeader("ADD NEW MENU ITEM");
    
    string itemName = getValidStringInput("Enter item name: ");
    
    // Check if item already exists
    if (findMenuItem(itemName) != -1) {
        cout << "Error: Item '" << itemName << "' already exists in menu!" << endl;
        return;
    }
    
    double price = getValidDoubleInput("Enter price (Rs.): ");
    
    MenuItem newItem;
    newItem.name = itemName;
    newItem.price = price;
    
    menu.push_back(newItem);
    
    if (saveMenu()) {
        cout << "\nSuccess! '" << itemName << "' has been added to the menu." << endl;
        cout << "Price: Rs. " << fixed << setprecision(2) << price << endl;
    } else {
        cout << "Error: Could not save menu to file." << endl;
    }
}

// Function to update item price
void updateItemPrice() {
    displayHeader("UPDATE ITEM PRICE");
    
    if (menu.empty()) {
        cout << "Menu is empty. Please add items first." << endl;
        return;
    }
    
    displayMenu();
    
    string itemInput = getValidStringInput("\nEnter item number or name to update: ");
    
    int itemIndex = findMenuItem(itemInput);
    if (itemIndex == -1) {
        cout << "Error: Item '" << itemInput << "' not found in menu!" << endl;
        cout << "Please enter a valid item number (1-" << menu.size() << ") or exact item name." << endl;
        return;
    }
    
    string itemName = menu[itemIndex].name; // Get the actual item name
    
    cout << "Current price of '" << itemName << "' is Rs. " 
         << fixed << setprecision(2) << menu[itemIndex].price << endl;
    
    double newPrice = getValidDoubleInput("Enter new price (Rs.): ");
    
    double oldPrice = menu[itemIndex].price;
    menu[itemIndex].price = newPrice;
    
    if (saveMenu()) {
        cout << "\nSuccess! Price updated for '" << itemName << "'" << endl;
        cout << "Old Price: Rs. " << fixed << setprecision(2) << oldPrice << endl;
        cout << "New Price: Rs. " << fixed << setprecision(2) << newPrice << endl;
    } else {
        cout << "Error: Could not save menu to file." << endl;
        menu[itemIndex].price = oldPrice; // Revert the change
    }
}

// Function to delete menu item
void deleteMenuItem() {
    displayHeader("DELETE MENU ITEM");
    
    if (menu.empty()) {
        cout << "Menu is empty. Nothing to delete." << endl;
        return;
    }
    
    displayMenu();
    
    string itemInput = getValidStringInput("\nEnter item number or name to delete: ");
    
    int itemIndex = findMenuItem(itemInput);
    if (itemIndex == -1) {
        cout << "Error: Item '" << itemInput << "' not found in menu!" << endl;
        cout << "Please enter a valid item number (1-" << menu.size() << ") or exact item name." << endl;
        return;
    }
    
    string itemName = menu[itemIndex].name; // Get the actual item name
    
    cout << "Are you sure you want to delete '" << itemName << "'? (y/n): ";
    char confirm;
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        double deletedPrice = menu[itemIndex].price;
        menu.erase(menu.begin() + itemIndex);
        
        if (saveMenu()) {
            cout << "\nSuccess! '" << itemName << "' has been deleted from the menu." << endl;
            cout << "Deleted item price was: Rs. " << fixed << setprecision(2) << deletedPrice << endl;
        } else {
            cout << "Error: Could not save menu to file." << endl;
        }
    } else {
        cout << "Deletion cancelled." << endl;
    }
}

// Function to generate sales report
void generateSalesReport() {
    displayHeader("DAILY SALES REPORT");
    
    if (salesHistory.empty()) {
        cout << "No sales data available." << endl;
        return;
    }
    
    double totalRevenue = 0;
    int totalOrders = 0;
    
    cout << "\nSales Summary:" << endl;
    cout << string(50, '-') << endl;
    
    for (const auto& sale : salesHistory) {
        totalRevenue += sale.total;
        totalOrders++;
    }
    
    cout << "Total Orders: " << totalOrders << endl;
    cout << "Total Revenue: Rs. " << fixed << setprecision(2) << totalRevenue << endl;
    
    if (totalOrders > 0) {
        cout << "Average Order Value: Rs. " << fixed << setprecision(2) << (totalRevenue / totalOrders) << endl;
    }
    
    cout << string(50, '-') << endl;
}

// Function to view sales history
void viewSalesHistory() {
    displayHeader("SALES HISTORY");
    
    if (salesHistory.empty()) {
        cout << "No sales records found." << endl;
        return;
    }
    
    cout << "\n" << left << setw(5) << "No."
         << setw(30) << "Items Ordered"
         << setw(15) << "Total (Rs.)"
         << setw(15) << "Date" << endl;
    cout << string(65, '-') << endl;
    
    for (size_t i = 0; i < salesHistory.size(); i++) {
        cout << left << setw(5) << (i + 1)
             << setw(30) << salesHistory[i].items
             << setw(15) << fixed << setprecision(2) << salesHistory[i].total
             << setw(15) << salesHistory[i].date << endl;
    }
}

// Main function for admin portal
int main() {
    displayWelcome("ADMIN PORTAL");
    
    // Load data from files
    if (!loadMenu()) {
        cout << "\nStarting with empty menu. You can add items using the admin panel." << endl;
    }
    
    loadSalesHistory();
    
    int choice;
    
    do {
        displayAdminMenu();
        choice = getValidIntInput("");
        
        switch (choice) {
            case 1:
                displayHeader("CURRENT MENU");
                displayMenu();
                break;
                
            case 2:
                addNewItem();
                break;
                
            case 3:
                updateItemPrice();
                break;
                
            case 4:
                deleteMenuItem();
                break;
                
            case 5:
                generateSalesReport();
                break;
                
            case 6:
                viewSalesHistory();
                break;
                
            case 7:
                displayHeader("GOODBYE");
                cout << "Thank you for using Smart Canteen Admin Portal!" << endl;
                cout << "All changes have been saved automatically." << endl;
                break;
                
            default:
                cout << "Invalid choice! Please select a number between 1-7." << endl;
        }
        
        if (choice != 7) {
            pauseScreen();
        }
        
    } while (choice != 7);
    
    return 0;
}