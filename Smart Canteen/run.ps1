Write-Host "====================================" -ForegroundColor Green
Write-Host "     Smart Canteen System" -ForegroundColor Green
Write-Host "====================================" -ForegroundColor Green
Write-Host ""

# Check if executable exists
if (-not (Test-Path "smart_canteen.exe")) {
    Write-Host "Compiling the system..." -ForegroundColor Yellow
    
    # Compile all source files
    $sourceFiles = @(
        "src/main.cpp",
        "src/MenuManager.cpp",
        "src/OrderManager.cpp", 
        "src/SalesManager.cpp",
        "src/Reports.cpp",
        "src/AdminPanel.cpp",
        "src/ClientPanel.cpp"
    )
    
    $compileCommand = "g++ -std=c++11 -Wall -Wextra -g -Iheader " + ($sourceFiles -join " ") + " -o smart_canteen.exe"
    
    try {
        Invoke-Expression $compileCommand
        if ($LASTEXITCODE -eq 0) {
            Write-Host "Compilation successful!" -ForegroundColor Green
            Write-Host ""
        } else {
            Write-Host "Compilation failed!" -ForegroundColor Red
            Write-Host "Press any key to exit..." -ForegroundColor Red
            $null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
            exit 1
        }
    } catch {
        Write-Host "Error during compilation: $($_.Exception.Message)" -ForegroundColor Red
        Write-Host "Press any key to exit..." -ForegroundColor Red
        $null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
        exit 1
    }
}

Write-Host "Starting Smart Canteen System..." -ForegroundColor Cyan
Write-Host ""

# Run the program
try {
    .\smart_canteen.exe
} catch {
    Write-Host "Error running the program: $($_.Exception.Message)" -ForegroundColor Red
}

Write-Host ""
Write-Host "Program ended. Press any key to exit..." -ForegroundColor Yellow
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")