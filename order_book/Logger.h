#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>   
#include <iomanip> 

class Logger {
private:
    std::ofstream file; // This represents our actual CSV file on the hard drive

public:
    // Constructor: This runs automatically the moment the Logger is created.
    // It opens the file and prepares the column headers for our data.
    Logger(std::string filename) {
        file.open(filename);
        if (file.is_open()) {
            // Set up the columns exactly like Binance data
            file << "order_id,price,qty,side,timestamp\n";
        }
    }

    // Destructor: This runs automatically when the program finishes.
    // It ensures we safely close the file so data doesn't get corrupted.
    ~Logger() {
        if (file.is_open()) {
            file.close(); 
        }
    }

    // This function acts as the "save button" for our trades
    void logTrade(int order_id, double price, double qty, std::string side) {
        if (file.is_open()) {
            // Grab the current date and time from the computer's clock
            std::time_t t = std::time(nullptr);
            std::tm* now = std::localtime(&t);
            
            // Write the specific trade details into a new row in the CSV
            file << order_id << "," 
                 << price << "," 
                 << qty << "," 
                 << side << "," 
                 << std::put_time(now, "%Y-%m-%d %H:%M:%S") << "\n";
        }
    }
};