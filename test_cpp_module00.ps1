#!/usr/bin/env pwsh

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Testing C++ Module 00" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan

$basePath = "c:\Users\Sam Heiles\Documents\42_cursus\CPP_module00"

# Test Ex00
Write-Host "`n[EX00] Megaphone:" -ForegroundColor Yellow
Push-Location "$basePath\ex00"
Write-Host "Cleaning and compiling..."
gcc.exe -Wall -Wextra -Werror -std=c++98 megaphone.cpp -lstdc++ -o megaphone 2>&1
if ($LASTEXITCODE -eq 0) {
    Write-Host "✓ Compilation successful" -ForegroundColor Green
    Write-Host "`nTest 1: shhhhh..."
    & .\megaphone.exe "shhhhh... I think the students are asleep..."
    
    Write-Host "`nTest 2: Multiple args"
    & .\megaphone.exe "Damnit" " ! " "Sorry students, I thought this thing was off."
    
    Write-Host "`nTest 3: No args (feedback)"
    & .\megaphone.exe
} else {
    Write-Host "✗ Compilation failed" -ForegroundColor Red
}
Pop-Location

# Test Ex01
Write-Host "`n[EX01] PhoneBook:" -ForegroundColor Yellow
Push-Location "$basePath\ex01"
Write-Host "Cleaning and compiling..."
gcc.exe -Wall -Wextra -Werror -std=c++98 main.cpp PhoneBook.cpp Contact.cpp -lstdc++ -o phonebook 2>&1
if ($LASTEXITCODE -eq 0) {
    Write-Host "✓ Compilation successful" -ForegroundColor Green
    Write-Host "Run phonebook interactively with: .\phonebook.exe"
} else {
    Write-Host "✗ Compilation failed" -ForegroundColor Red
}
Pop-Location

# Test Ex02
Write-Host "`n[EX02] Account:" -ForegroundColor Yellow
Push-Location "$basePath\ex02"
Write-Host "Cleaning and compiling..."
gcc.exe -Wall -Wextra -Werror -std=c++98 Account.cpp tests.cpp -lstdc++ -o account 2>&1
if ($LASTEXITCODE -eq 0) {
    Write-Host "✓ Compilation successful" -ForegroundColor Green
    Write-Host "`nExecution:"
    & .\account.exe
} else {
    Write-Host "✗ Compilation failed" -ForegroundColor Red
}
Pop-Location

Write-Host "`n========================================" -ForegroundColor Cyan
Write-Host "Testing complete" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
