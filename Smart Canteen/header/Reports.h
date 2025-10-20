#ifndef REPORTS_H
#define REPORTS_H

#include <string>
#include <vector>
#include "SalesManager.h"

class Reports {
private:
    SalesManager* salesManager;

public:
    Reports(SalesManager* sales);
    
    // Generate daily report
    void generateDailyReport();
    
    // Calculate total number of sales
    int getTotalSalesCount();
    
    // Calculate total revenue
    double getTotalRevenue();
    
    // Find highest single sale value
    double getHighestSaleValue();
    
    // Calculate average sale value
    double getAverageSaleValue();
    
    // Display detailed analytics
    void displayAnalytics();
    
    // Get sales for specific date
    std::vector<SalesRecord> getSalesForDate(const std::string& date);
};

#endif