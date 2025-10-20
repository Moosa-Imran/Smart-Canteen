@echo off
echo ====================================
echo      Smart Canteen System
echo ====================================
echo.

REM Check if executable exists
if not exist smart_canteen.exe (
    echo Compiling the system...
    g++ -std=c++11 -Wall -Wextra -g -Iheader src/main.cpp src/MenuManager.cpp src/OrderManager.cpp src/SalesManager.cpp src/Reports.cpp src/AdminPanel.cpp src/ClientPanel.cpp -o smart_canteen.exe
    if errorlevel 1 (
        echo Compilation failed!
        pause
        exit /b 1
    )
    echo Compilation successful!
    echo.
)

echo Starting Smart Canteen System...
echo.
smart_canteen.exe

echo.
echo Program ended. Press any key to exit...
pause > nul