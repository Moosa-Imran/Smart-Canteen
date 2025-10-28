#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

using namespace std;

// Simple structure for menu items
struct MenuItem {
    string name;
    double price;
};

// Simple structure for cart items
struct CartItem {
    string name;
    double price;
    int quantity;
};

// Simple structure for sales records
struct SaleRecord {
    string items;
    double total;
    string date;
};

// Global variables for the system
vector<MenuItem> menu;
vector<CartItem> cart;
vector<SaleRecord> salesHistory;

// Function to clear screen (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to pause and wait for user input
void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Function to display a decorative header
void displayHeader(const string& title) {
    cout << "\n" << string(60, '=') << endl;
    cout << "  " << title << endl;
    cout << string(60, '=') << endl;
}

// Function to display welcome message
void displayWelcome(const string& portalType) {
    clearScreen();
    cout << string(70, '*') << endl;
    cout << "*" << string(68, ' ') << "*" << endl;
    cout << "*" << string(15, ' ') << "SMART CANTEEN SYSTEM - " << portalType << string(15, ' ') << "*" << endl;
    cout << "*" << string(68, ' ') << "*" << endl;
    cout << "*" << string(20, ' ') << "Simple Food Ordering System" << string(21, ' ') << "*" << endl;
    cout << "*" << string(68, ' ') << "*" << endl;
    cout << string(70, '*') << endl;
}

// Function to load menu from file
bool loadMenu() {
    menu.clear();
    ifstream file("Text_files/menu.txt");
    
    if (!file.is_open()) {
        cout << "Warning: Could not open menu.txt. Starting with empty menu." << endl;
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            MenuItem item;
            item.name = line.substr(0, commaPos);
            item.price = stod(line.substr(commaPos + 1));
            menu.push_back(item);
        }
    }
    
    file.close();
    return true;
}

// Function to save menu to file
bool saveMenu() {
    ofstream file("Text_files/menu.txt");
    
    if (!file.is_open()) {
        cout << "Error: Could not save menu to file." << endl;
        return false;
    }
    
    for (const auto& item : menu) {
        file << item.name << "," << item.price << endl;
    }
    
    file.close();
    return true;
}

// Function to display menu
void displayMenu() {
    if (menu.empty()) {
        cout << "No items in menu." << endl;
        return;
    }
    
    cout << "\n" << left << setw(5) << "No." 
         << setw(25) << "Item Name" 
         << setw(15) << "Price (Rs.)" << endl;
    cout << string(45, '-') << endl;
    
    for (size_t i = 0; i < menu.size(); i++) {
        cout << left << setw(5) << (i + 1)
             << setw(25) << menu[i].name
             << "Rs. " << fixed << setprecision(2) << menu[i].price << endl;
    }
}

// Function to find menu item by name or number
int findMenuItem(const string& input) {
    // First try to parse as a number (1-based index)
    try {
        int itemNumber = stoi(input);
        if (itemNumber >= 1 && itemNumber <= (int)menu.size()) {
            return itemNumber - 1; // Convert to 0-based index
        }
    } catch (const invalid_argument&) {
        // Not a number, try as name
    }
    
    // Try to find by name (case-insensitive)
    for (size_t i = 0; i < menu.size(); i++) {
        string menuItemLower = menu[i].name;
        string inputLower = input;
        
        // Convert both to lowercase for comparison
        transform(menuItemLower.begin(), menuItemLower.end(), menuItemLower.begin(), ::tolower);
        transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);
        
        if (menuItemLower == inputLower) {
            return i;
        }
    }
    return -1;
}

// Function to load sales history
bool loadSalesHistory() {
    salesHistory.clear();
    ifstream file("Text_files/sales.txt");
    
    if (!file.is_open()) {
        return false; // File doesn't exist yet, that's okay
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        SaleRecord sale;
        stringstream ss(line);
        string token;
        
        // Parse the line - format: items|total|date
        if (getline(ss, token, '|')) sale.items = token;
        if (getline(ss, token, '|')) sale.total = stod(token);
        if (getline(ss, token, '|')) sale.date = token;
        
        salesHistory.push_back(sale);
    }
    
    file.close();
    return true;
}

// Function to save sale to file
bool saveSale(const string& items, double total) {
    ofstream file("Text_files/sales.txt", ios::app);
    
    if (!file.is_open()) {
        cout << "Error: Could not save sale to file." << endl;
        return false;
    }
    
    // Get current date/time (simplified)
    string currentDate = "Today"; // You can implement proper date/time if needed
    
    file << items << "|" << total << "|" << currentDate << endl;
    file.close();
    
    // Add to memory as well
    SaleRecord sale;
    sale.items = items;
    sale.total = total;
    sale.date = currentDate;
    salesHistory.push_back(sale);
    
    return true;
}

// Function to get valid integer input
int getValidIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        try {
            value = stoi(input);
            return value;
        } catch (const invalid_argument& e) {
            cout << "Invalid input! Please enter a number." << endl;
        } catch (const out_of_range& e) {
            cout << "Number too large! Please enter a smaller number." << endl;
        }
    }
}

// Function to get valid double input
double getValidDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        try {
            value = stod(input);
            if (value > 0) {
                return value;
            } else {
                cout << "Invalid input! Please enter a positive number." << endl;
            }
        } catch (const invalid_argument& e) {
            cout << "Invalid input! Please enter a number." << endl;
        } catch (const out_of_range& e) {
            cout << "Number too large! Please enter a smaller number." << endl;
        }
    }
}

// Function to get valid string input
string getValidStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

#endif