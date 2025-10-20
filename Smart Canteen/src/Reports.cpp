#include "Reports.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Reports::Reports(SalesManager* sales) : salesManager(sales) {}

void Reports::generateDailyReport() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "                    DAILY REPORT" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    int totalSales = getTotalSalesCount();
    double totalRevenue = getTotalRevenue();
    double highestSale = getHighestSaleValue();
    double averageSale = getAverageSaleValue();
    
    std::cout << std::left << std::setw(30) << "Total Number of Sales:" 
              << std::right << std::setw(15) << totalSales << std::endl;
    
    std::cout << std::left << std::setw(30) << "Total Revenue:" 
              << std::right << std::setw(15) << "Rs. " 
              << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
    
    std::cout << std::left << std::setw(30) << "Highest Single Sale:" 
              << std::right << std::setw(15) << "Rs. " 
              << std::fixed << std::setprecision(2) << highestSale << std::endl;
    
    std::cout << std::left << std::setw(30) << "Average Sale Value:" 
              << std::right << std::setw(15) << "Rs. " 
              << std::fixed << std::setprecision(2) << averageSale << std::endl;
    
    std::cout << std::string(60, '=') << std::endl;
}

int Reports::getTotalSalesCount() {
    std::vector<SalesRecord> records = salesManager->loadSalesRecords();
    return static_cast<int>(records.size());
}

double Reports::getTotalRevenue() {
    std::vector<SalesRecord> records = salesManager->loadSalesRecords();
    double totalRevenue = 0.0;
    
    for (const auto& record : records) {
        totalRevenue += record.totalAmount;
    }
    
    return totalRevenue;
}

double Reports::getHighestSaleValue() {
    std::vector<SalesRecord> records = salesManager->loadSalesRecords();
    
    if (records.empty()) {
        return 0.0;
    }
    
    double highestSale = records[0].totalAmount;
    for (const auto& record : records) {
        if (record.totalAmount > highestSale) {
            highestSale = record.totalAmount;
        }
    }
    
    return highestSale;
}

double Reports::getAverageSaleValue() {
    std::vector<SalesRecord> records = salesManager->loadSalesRecords();
    
    if (records.empty()) {
        return 0.0;
    }
    
    double totalRevenue = getTotalRevenue();
    return totalRevenue / records.size();
}

void Reports::displayAnalytics() {
    std::vector<SalesRecord> records = salesManager->loadSalesRecords();
    
    if (records.empty()) {
        std::cout << "\nNo sales data available for analysis." << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "                        SALES ANALYTICS" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    // Basic statistics
    generateDailyReport();
    
    // Additional analytics
    std::cout << "\nADDITIONAL INSIGHTS:" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    // Find minimum sale value
    double minSale = records[0].totalAmount;
    for (const auto& record : records) {
        if (record.totalAmount < minSale) {
            minSale = record.totalAmount;
        }
    }
    
    std::cout << std::left << std::setw(30) << "Lowest Single Sale:" 
              << std::right << std::setw(15) << "Rs. " 
              << std::fixed << std::setprecision(2) << minSale << std::endl;
    
    // Calculate sales distribution
    int salesUnder200 = 0, sales200to500 = 0, salesAbove500 = 0;
    for (const auto& record : records) {
        if (record.totalAmount < 200) {
            salesUnder200++;
        } else if (record.totalAmount <= 500) {
            sales200to500++;
        } else {
            salesAbove500++;
        }
    }
    
    std::cout << "\nSALES DISTRIBUTION:" << std::endl;
    std::cout << std::left << std::setw(30) << "Sales under Rs. 200:" 
              << std::right << std::setw(15) << salesUnder200 << std::endl;
    std::cout << std::left << std::setw(30) << "Sales Rs. 200-500:" 
              << std::right << std::setw(15) << sales200to500 << std::endl;
    std::cout << std::left << std::setw(30) << "Sales above Rs. 500:" 
              << std::right << std::setw(15) << salesAbove500 << std::endl;
    
    std::cout << std::string(70, '=') << std::endl;
}

std::vector<SalesRecord> Reports::getSalesForDate(const std::string& date) {
    std::vector<SalesRecord> allRecords = salesManager->loadSalesRecords();
    std::vector<SalesRecord> dateRecords;
    
    for (const auto& record : allRecords) {
        if (record.date == date) {
            dateRecords.push_back(record);
        }
    }
    
    return dateRecords;
}