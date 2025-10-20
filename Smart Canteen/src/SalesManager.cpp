#include "SalesManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

SalesManager::SalesManager(const std::string& filePath) : salesFilePath(filePath) {}

bool SalesManager::recordSale(const std::string& orderSummary, double totalAmount) {
    std::ofstream file(salesFilePath, std::ios::app);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open sales file: " << salesFilePath << std::endl;
        return false;
    }
    
    std::string currentDate = getCurrentDate();
    file << currentDate << " | " << orderSummary << " | Total: " 
         << std::fixed << std::setprecision(0) << totalAmount << std::endl;
    
    file.close();
    
    std::cout << "\nSale recorded successfully!" << std::endl;
    std::cout << "Date: " << currentDate << std::endl;
    std::cout << "Order: " << orderSummary << std::endl;
    std::cout << "Total: Rs. " << std::fixed << std::setprecision(2) << totalAmount << std::endl;
    
    return true;
}

std::vector<SalesRecord> SalesManager::loadSalesRecords() {
    std::vector<SalesRecord> records;
    std::ifstream file(salesFilePath);
    
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open sales file: " << salesFilePath << std::endl;
        return records;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            SalesRecord record = parseSalesRecord(line);
            if (!record.date.empty()) {
                records.push_back(record);
            }
        }
    }
    
    file.close();
    return records;
}

void SalesManager::displaySalesLog() {
    std::vector<SalesRecord> records = loadSalesRecords();
    
    if (records.empty()) {
        std::cout << "\nNo sales records found." << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "                            SALES LOG" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << std::left << std::setw(12) << "Date"
              << std::setw(40) << "Order Details"
              << std::right << std::setw(15) << "Amount (Rs.)" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (const auto& record : records) {
        std::cout << std::left << std::setw(12) << record.date
                  << std::setw(40) << record.orderSummary
                  << std::right << std::setw(15) << std::fixed 
                  << std::setprecision(2) << record.totalAmount << std::endl;
    }
    std::cout << std::string(80, '=') << std::endl;
}

std::string SalesManager::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto tm = *std::localtime(&time_t);
    
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d");
    return ss.str();
}

SalesRecord SalesManager::parseSalesRecord(const std::string& line) {
    SalesRecord record;
    
    // Expected format: "2025-10-07 | Burger x2, Fries x1 | Total: 620"
    std::stringstream ss(line);
    std::string datePart, orderPart, totalPart;
    
    if (std::getline(ss, datePart, '|') && 
        std::getline(ss, orderPart, '|') && 
        std::getline(ss, totalPart)) {
        
        // Trim whitespace
        datePart.erase(0, datePart.find_first_not_of(" \t"));
        datePart.erase(datePart.find_last_not_of(" \t") + 1);
        
        orderPart.erase(0, orderPart.find_first_not_of(" \t"));
        orderPart.erase(orderPart.find_last_not_of(" \t") + 1);
        
        totalPart.erase(0, totalPart.find_first_not_of(" \t"));
        totalPart.erase(totalPart.find_last_not_of(" \t") + 1);
        
        record.date = datePart;
        record.orderSummary = orderPart;
        
        // Extract total amount from "Total: 620"
        size_t colonPos = totalPart.find(':');
        if (colonPos != std::string::npos && colonPos + 1 < totalPart.length()) {
            std::string amountStr = totalPart.substr(colonPos + 1);
            amountStr.erase(0, amountStr.find_first_not_of(" \t"));
            try {
                record.totalAmount = std::stod(amountStr);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing amount from: " << totalPart << std::endl;
                record.totalAmount = 0.0;
            }
        }
    }
    
    return record;
}