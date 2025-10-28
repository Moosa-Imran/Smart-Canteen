@echo off
echo ====================================
echo      Smart Canteen System
echo ====================================
echo.
echo Please choose which portal to run:
echo 1. Admin Portal
echo 2. Client Portal
echo 3. Exit
echo.
set /p choice="Enter your choice (1-3): "

if "%choice%"=="1" goto admin
if "%choice%"=="2" goto client
if "%choice%"=="3" goto end
echo Invalid choice!
pause
goto end

:admin
echo.
echo Starting Admin Portal...
if not exist admin_portal.exe (
    echo Compiling Admin Portal...
    g++ -std=c++11 -Wall -Wextra -g admin_portal.cpp -o admin_portal.exe
    if errorlevel 1 (
        echo Admin Portal compilation failed!
        pause
        exit /b 1
    )
    echo Compilation successful!
    echo.
)
admin_portal.exe
goto end

:client
echo.
echo Starting Client Portal...
if not exist client_portal.exe (
    echo Compiling Client Portal...
    g++ -std=c++11 -Wall -Wextra -g client_portal.cpp -o client_portal.exe
    if errorlevel 1 (
        echo Client Portal compilation failed!
        pause
        exit /b 1
    )
    echo Compilation successful!
    echo.
)
client_portal.exe
goto end

:end
echo.
echo Thank you for using Smart Canteen System!
echo.