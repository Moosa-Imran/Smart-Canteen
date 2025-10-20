@echo off
echo Compiling Smart Canteen System...
g++ -std=c++11 -Wall -Wextra -g -Iheader src/main.cpp src/MenuManager.cpp src/OrderManager.cpp src/SalesManager.cpp src/Reports.cpp src/AdminPanel.cpp src/ClientPanel.cpp -o smart_canteen.exe
if errorlevel 1 (
    echo Compilation failed!
    pause
) else (
    echo Compilation successful! Run 'smart_canteen.exe' to start the program.
    pause
)