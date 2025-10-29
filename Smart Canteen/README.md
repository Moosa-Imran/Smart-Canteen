# Smart Canteen System - Beginner-Friendly Version

A simple, beginner-friendly canteen management system with separate Admin and Client portals.

## Overview

This system is designed to be easy to understand for beginners. It uses:
- **No classes** - Only simple functions and structures
- **`using namespace std`** - No need to type `std::` everywhere
- **Simple data structures** - Uses vectors and basic structs
- **Separate portals** - Admin and Client have their own programs
- **Clear, readable code** - Easy to follow logic

## Features

### Admin Portal (`admin_portal.exe`)
- View current menu
- Add new menu items
- Update item prices
- Delete menu items
- View sales reports
- View sales history

### Client Portal (`client_portal.exe`)
- View menu
- Add items to cart
- View cart contents
- Remove items from cart
- Checkout and place orders
- Clear cart

## File Structure

```
Smart Canteen/
├── admin_portal.cpp      # Admin portal source code
├── client_portal.cpp     # Client portal source code
├── common.h              # Shared functions and data structures
├── compile.bat           # Windows compilation script
├── run.bat              # Windows run script with portal selection
├── Makefile             # Linux/Mac compilation
└── Text_files/
    ├── menu.txt         # Menu items (name,price format)
    └── sales.txt        # Sales records (items|total|date format)
```

## How to Compile

### Windows (using compile.bat)
```bash
compile.bat
```

### Windows (manual compilation)
```bash
g++ -std=c++11 -Wall -Wextra -g admin_portal.cpp -o admin_portal.exe
g++ -std=c++11 -Wall -Wextra -g client_portal.cpp -o client_portal.exe
```

### Linux/Mac (using Makefile)
```bash
make all           # Build both portals
make admin_portal  # Build only admin portal
make client_portal # Build only client portal
```

## How to Run

### Windows
```bash
run.bat            # Interactive menu to choose portal
admin_portal.exe   # Run admin portal directly
client_portal.exe  # Run client portal directly
```

### Linux/Mac
```bash
make run-admin     # Build and run admin portal
make run-client    # Build and run client portal
./admin_portal     # Run admin portal directly
./client_portal    # Run client portal directly
```

## Data Files

### menu.txt Format
```
ItemName,Price
Burger,250
Pizza,450
```

### sales.txt Format
```
Items|Total|Date
Burger x2, Pizza x1|950|Today
```

## Code Structure for Beginners

### Data Structures Used
- `vector<MenuItem>` - List of menu items
- `vector<CartItem>` - Shopping cart items
- `vector<SaleRecord>` - Sales history

### Key Functions
- `loadMenu()` - Reads menu from file
- `saveMenu()` - Saves menu to file
- `displayMenu()` - Shows menu in formatted table
- `addToCart()` - Adds items to shopping cart
- `processCheckout()` - Handles payment and order completion

## Sample Usage

1. **First Time Setup**: The system will create necessary files if they don't exist
2. **Admin Tasks**: Use admin portal to set up menu items and view reports
3. **Customer Orders**: Use client portal to browse menu and place orders
4. **Data Persistence**: All changes are automatically saved to text files

## Error Handling

- Input validation for all user entries
- File error handling with user-friendly messages
- Clear error messages for invalid operations
- Automatic recovery from common mistakes

## Benefits for Beginners

1. **No Complex OOP**: Uses simple functions instead of classes
2. **Clear Variable Names**: Easy to understand what each variable does
3. **Simple Logic Flow**: Linear, easy-to-follow program structure
4. **Extensive Comments**: Code is well-documented
5. **Error Messages**: Clear feedback when something goes wrong
6. **Modular Design**: Each function has a single, clear purpose

## Extending the System

To add new features:
1. Add new functions to `common.h` for shared functionality
2. Add menu options to the respective portal
3. Implement the new function following the existing pattern
4. Update this README with new features

## Troubleshooting

- **Compilation errors**: Make sure you have g++ installed
- **File not found**: The system will create missing files automatically
- **Invalid input**: The system will ask you to try again
- **Permission errors**: Make sure you have write access to the Text_files directory