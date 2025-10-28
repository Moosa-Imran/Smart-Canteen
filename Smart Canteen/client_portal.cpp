#include "common.h"

using namespace std;

// Function to display client menu
void displayClientMenu() {
    displayHeader("CLIENT PORTAL");
    cout << "1. View Menu" << endl;
    cout << "2. Add Item to Cart" << endl;
    cout << "3. View Cart" << endl;
    cout << "4. Remove Item from Cart" << endl;
    cout << "5. Checkout" << endl;
    cout << "6. Clear Cart" << endl;
    cout << "7. Exit Client Portal" << endl;
    cout << string(60, '=') << endl;
    cout << "Enter your choice: ";
}

// Function to display cart
void displayCart() {
    if (cart.empty()) {
        cout << "Your cart is empty." << endl;
        return;
    }
    
    cout << "\n" << left << setw(5) << "No."
         << setw(20) << "Item"
         << setw(12) << "Price (Rs.)"
         << setw(10) << "Quantity"
         << setw(15) << "Subtotal (Rs.)" << endl;
    cout << string(62, '-') << endl;
    
    double total = 0;
    for (size_t i = 0; i < cart.size(); i++) {
        double subtotal = cart[i].price * cart[i].quantity;
        total += subtotal;
        
        cout << left << setw(5) << (i + 1)
             << setw(20) << cart[i].name
             << setw(12) << fixed << setprecision(2) << cart[i].price
             << setw(10) << cart[i].quantity
             << setw(15) << fixed << setprecision(2) << subtotal << endl;
    }
    
    cout << string(62, '-') << endl;
    cout << right << setw(47) << "TOTAL: Rs. " 
         << fixed << setprecision(2) << total << endl;
    cout << string(62, '-') << endl;
}

// Function to calculate cart total
double calculateCartTotal() {
    double total = 0;
    for (const auto& item : cart) {
        total += item.price * item.quantity;
    }
    return total;
}

// Function to find cart item by name or number (from displayed cart)
int findCartItem(const string& input) {
    // First try to parse as a number (1-based index from displayed cart)
    try {
        int itemNumber = stoi(input);
        if (itemNumber >= 1 && itemNumber <= (int)cart.size()) {
            return itemNumber - 1; // Convert to 0-based index
        }
    } catch (const invalid_argument&) {
        // Not a number, try as name
    }
    
    // Try to find by name (case-insensitive)
    for (size_t i = 0; i < cart.size(); i++) {
        string cartItemLower = cart[i].name;
        string inputLower = input;
        
        // Convert both to lowercase for comparison
        transform(cartItemLower.begin(), cartItemLower.end(), cartItemLower.begin(), ::tolower);
        transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);
        
        if (cartItemLower == inputLower) {
            return i;
        }
    }
    return -1;
}

// Function to add item to cart
void addToCart() {
    displayHeader("ADD ITEM TO CART");
    
    if (menu.empty()) {
        cout << "Menu is empty. Please contact admin to add items." << endl;
        return;
    }
    
    displayMenu();
    
    string itemInput = getValidStringInput("\nEnter item number (1-12) or item name: ");
    
    int menuIndex = findMenuItem(itemInput);
    if (menuIndex == -1) {
        cout << "Error: Item '" << itemInput << "' not found in menu!" << endl;
        cout << "Please enter a valid item number (1-" << menu.size() << ") or exact item name." << endl;
        return;
    }
    
    string itemName = menu[menuIndex].name; // Get the actual item name
    
    int quantity = getValidIntInput("Enter quantity: ");
    if (quantity <= 0) {
        cout << "Invalid quantity! Please enter a positive number." << endl;
        return;
    }
    
    // Check if item already exists in cart
    int cartIndex = findCartItem(itemName);
    if (cartIndex != -1) {
        // Item exists, update quantity
        cart[cartIndex].quantity += quantity;
        cout << "\nUpdated quantity for '" << itemName << "' in cart." << endl;
        cout << "New quantity: " << cart[cartIndex].quantity << endl;
    } else {
        // Add new item to cart
        CartItem newCartItem;
        newCartItem.name = itemName;
        newCartItem.price = menu[menuIndex].price;
        newCartItem.quantity = quantity;
        cart.push_back(newCartItem);
        
        cout << "\nAdded '" << itemName << "' to cart." << endl;
    }
    
    cout << "Quantity: " << quantity << endl;
    cout << "Price per item: Rs. " << fixed << setprecision(2) << menu[menuIndex].price << endl;
    cout << "Subtotal: Rs. " << fixed << setprecision(2) << (menu[menuIndex].price * quantity) << endl;
}

// Function to remove item from cart
void removeFromCart() {
    displayHeader("REMOVE ITEM FROM CART");
    
    if (cart.empty()) {
        cout << "Cart is empty. Nothing to remove." << endl;
        return;
    }
    
    displayCart();
    
    string itemInput = getValidStringInput("\nEnter item number or name to remove: ");
    
    int cartIndex = findCartItem(itemInput);
    if (cartIndex == -1) {
        cout << "Error: Item '" << itemInput << "' not found in cart!" << endl;
        return;
    }
    
    cout << "Current quantity: " << cart[cartIndex].quantity << endl;
    cout << "1. Remove specific quantity" << endl;
    cout << "2. Remove all of this item" << endl;
    
    int choice = getValidIntInput("Enter your choice (1 or 2): ");
    
    if (choice == 1) {
        int removeQty = getValidIntInput("Enter quantity to remove: ");
        
        if (removeQty <= 0) {
            cout << "Invalid quantity!" << endl;
            return;
        }
        
        if (removeQty >= cart[cartIndex].quantity) {
            // Remove entire item
            cout << "Removed all '" << cart[cartIndex].name << "' from cart." << endl;
            cart.erase(cart.begin() + cartIndex);
        } else {
            // Reduce quantity
            cart[cartIndex].quantity -= removeQty;
            cout << "Removed " << removeQty << " units of '" << cart[cartIndex].name << "' from cart." << endl;
            cout << "Remaining quantity: " << cart[cartIndex].quantity << endl;
        }
    } else if (choice == 2) {
        cout << "Removed all '" << cart[cartIndex].name << "' from cart." << endl;
        cart.erase(cart.begin() + cartIndex);
    } else {
        cout << "Invalid choice!" << endl;
    }
}

// Function to clear entire cart
void clearCart() {
    if (cart.empty()) {
        cout << "Cart is already empty." << endl;
        return;
    }
    
    cout << "Are you sure you want to clear your entire cart? (y/n): ";
    char confirm;
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        cart.clear();
        cout << "Cart has been cleared!" << endl;
    } else {
        cout << "Cart clear cancelled." << endl;
    }
}

// Function to process checkout
void processCheckout() {
    displayHeader("CHECKOUT");
    
    if (cart.empty()) {
        cout << "Your cart is empty. Please add items before checkout." << endl;
        return;
    }
    
    cout << "Order Summary:" << endl;
    displayCart();
    
    double total = calculateCartTotal();
    
    cout << "\nProceed with payment of Rs. " << fixed << setprecision(2) << total << "? (y/n): ";
    char confirm;
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        // Create order summary string
        string orderSummary = "";
        for (size_t i = 0; i < cart.size(); i++) {
            if (i > 0) orderSummary += ", ";
            orderSummary += cart[i].name + " x" + to_string(cart[i].quantity);
        }
        
        // Save the sale
        if (saveSale(orderSummary, total)) {
            displayHeader("ORDER CONFIRMED!");
            cout << "Payment successful!" << endl;
            cout << "Order Total: Rs. " << fixed << setprecision(2) << total << endl;
            cout << "Thank you for your order!" << endl;
            cout << "\nYour order:" << endl;
            
            for (const auto& item : cart) {
                cout << "- " << item.name << " x" << item.quantity 
                     << " @ Rs. " << fixed << setprecision(2) << item.price << " each" << endl;
            }
            
            // Clear cart after successful checkout
            cart.clear();
            cout << "\nEnjoy your meal!" << endl;
        } else {
            cout << "Error: Could not process payment. Please try again." << endl;
        }
    } else {
        cout << "Checkout cancelled. Items remain in cart." << endl;
    }
}

// Main function for client portal
int main() {
    displayWelcome("CLIENT PORTAL");
    
    // Load data from files
    if (!loadMenu()) {
        cout << "\nError: Could not load menu. Please contact admin." << endl;
        cout << "Press Enter to continue anyway...";
        cin.get();
    }
    
    loadSalesHistory();
    
    int choice;
    
    do {
        displayClientMenu();
        choice = getValidIntInput("");
        
        switch (choice) {
            case 1:
                displayHeader("MENU");
                displayMenu();
                break;
                
            case 2:
                addToCart();
                break;
                
            case 3:
                displayHeader("YOUR CART");
                displayCart();
                break;
                
            case 4:
                removeFromCart();
                break;
                
            case 5:
                processCheckout();
                break;
                
            case 6:
                clearCart();
                break;
                
            case 7:
                displayHeader("GOODBYE");
                cout << "Thank you for using Smart Canteen!" << endl;
                if (!cart.empty()) {
                    cout << "Note: Your cart items will be lost." << endl;
                    cout << "Complete checkout next time to place your order." << endl;
                }
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