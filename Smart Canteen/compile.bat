@echo off
echo Compiling Smart Canteen System...
echo.

echo Compiling Admin Portal...
g++ -std=c++11 -Wall -Wextra -g admin_portal.cpp -o admin_portal.exe
if errorlevel 1 (
    echo Admin Portal compilation failed!
    goto :error
)
echo Admin Portal compiled successfully!

echo.
echo Compiling Client Portal...
g++ -std=c++11 -Wall -Wextra -g client_portal.cpp -o client_portal.exe
if errorlevel 1 (
    echo Client Portal compilation failed!
    goto :error
)
echo Client Portal compiled successfully!

echo.
echo ========================================
echo All portals compiled successfully!
echo ========================================
echo.
echo To run:
echo - Admin Portal: admin_portal.exe
echo - Client Portal: client_portal.exe
echo.
pause
goto :end

:error
echo.
echo Compilation failed!
pause

:end