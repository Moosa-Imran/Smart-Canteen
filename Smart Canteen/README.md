# Smart Canteen System

A comprehensive C++ application for managing canteen operations with separate Admin and Client panels.

## Features

### Admin Panel
- Menu & Item Management (Add, Update, Delete items)
- Price Management
- Sales Reports & Analytics
- Sales Log Viewing

### Client Panel
- Menu Browsing
- Order Management (Shopping Cart)
- Checkout Process

### Core Modules
1. **MenuManager** - Handles menu operations and file I/O
2. **OrderManager** - Manages shopping cart and order processing
3. **SalesManager** - Records and stores sales data
4. **Reports** - Generates analytics and reports
5. **AdminPanel** - Administrative interface
6. **ClientPanel** - Customer interface

## File Structure

```
Smart Canteen/
├── Text_files/
│   ├── menu.txt        # Menu items (name, price)
│   └── sales.txt       # Sales records
├── header/
│   ├── MenuManager.h
│   ├── OrderManager.h
│   ├── SalesManager.h
│   ├── Reports.h
│   ├── AdminPanel.h
│   └── ClientPanel.h
├── src/
│   ├── MenuManager.cpp
│   ├── OrderManager.cpp
│   ├── SalesManager.cpp
│   ├── Reports.cpp
│   ├── AdminPanel.cpp
│   ├── ClientPanel.cpp
│   └── main.cpp
├── Makefile
└── README.md
```

## Compilation and Running

### Method 1: Using Makefile (Linux/Mac/WSL)
```bash
# Navigate to the project directory
cd "Smart Canteen"

# Setup files and build
make build-run

# Or step by step:
make setup    # Create necessary files
make          # Compile
make run      # Run the program

# Clean build files
make clean
```

### Method 2: Manual Compilation (Windows/Any OS)
```bash
# Navigate to the project directory
cd "Smart Canteen"

# Compile all source files (Windows PowerShell/CMD)
g++ -std=c++11 -Wall -Wextra -g -Iheader src/main.cpp src/MenuManager.cpp src/OrderManager.cpp src/SalesManager.cpp src/Reports.cpp src/AdminPanel.cpp src/ClientPanel.cpp -o smart_canteen.exe

# Or use the compile script
compile.bat  # Windows

# Run the program
./smart_canteen  # Linux/Mac
smart_canteen.exe  # Windows
```

### Method 3: Using VS Code
1. Open the "Smart Canteen" folder in VS Code
2. Install C++ extension if not already installed
3. Use Ctrl+Shift+P and run "Tasks: Run Task" > "Build and Run"
4. Or use the terminal methods above

## Usage Guide

### Main Menu Options
1. **Display Menu** - View all available items
2. **Take Order** - Quick order interface
3. **View Daily Report** - Sales analytics
4. **Update Item Price** - Quick price update
5. **View Sales Log** - All sales records
6. **Admin Panel** - Full administrative access
7. **Client Panel** - Full customer interface
8. **Exit** - Close the application

### Sample Data
The system comes with pre-loaded menu items:
- Burger (Rs. 250)
- Pizza (Rs. 450)
- Fries (Rs. 150)
- Sandwich (Rs. 180)
- Coffee (Rs. 120)
- Tea (Rs. 80)
- And more...

### Sales Record Format
Sales are stored in the format:
```
2025-10-21 | Burger x2, Fries x1 | Total: 620
```

## Key Features

### Menu Management
- Load menu from `menu.txt`
- Add/Update/Delete items
- Automatic file synchronization

### Order Processing
- Interactive shopping cart
- Quantity management
- Real-time price calculation
- Order confirmation

### Sales Tracking
- Automatic sales recording
- Date-stamped entries
- Persistent storage

### Analytics & Reporting
- Total sales count
- Total revenue
- Highest single sale
- Average sale value
- Sales distribution analysis

## Requirements
- C++11 or later
- Standard C++ libraries
- File system access for text files

## Troubleshooting

### Common Issues
1. **File not found errors**: Ensure you're running from the correct directory
2. **Permission errors**: Check file permissions for Text_files directory
3. **Compilation errors**: Verify C++11 support and include paths

### File Locations
- Menu data: `Text_files/menu.txt`
- Sales data: `Text_files/sales.txt`
- All paths are relative to the executable location

## Contributing
Feel free to enhance the system with additional features like:
- User authentication
- Payment processing
- Inventory management
- Customer loyalty programs
- Web interface

## License
This project is created for educational purposes.