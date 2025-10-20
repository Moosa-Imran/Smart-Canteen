#ifndef SALESMANAGER_H
#define SALESMANAGER_H

#include <string>
#include <vector>
#include "OrderManager.h"

struct SalesRecord {
    std::string date;
    std::string orderSummary;
    double totalAmount;
};

class SalesManager {
private:
    std::string salesFilePath;

public:
    SalesManager(const std::string& filePath);
    
    // Record a sale
    bool recordSale(const std::string& orderSummary, double totalAmount);
    
    // Load all sales records
    std::vector<SalesRecord> loadSalesRecords();
    
    // Display sales log
    void displaySalesLog();
    
    // Get current date string
    std::string getCurrentDate();
    
    // Parse sales record from file line
    SalesRecord parseSalesRecord(const std::string& line);
};

#endif