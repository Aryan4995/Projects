#pragma once
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>

// Enum prevents confusion between Buy (0) and Sell (1)
enum class Side {
    BUY,
    SELL
};

// 1. The Order Structure
// Represents a single instruction from a trader
struct Order {
    int id;             // Unique ID (e.g., 101)
    double price;       // Limit Price (e.g., 100.50)
    int quantity;       // Shares (e.g., 100)
    Side side;          // Buy or Sell
};

// 2. The OrderBook Class
class OrderBook {
private:
    // --- THE CORE DATA STRUCTURES ---
    
    // BIDS (Buyers): 
    // Key = Price, Value = List of Orders
    // We use 'std::greater' so the HIGHEST bid ($100) is at the top.
    std::map<double, std::list<Order>, std::greater<double>> bids;

    // ASKS (Sellers):
    // Standard map sorts Low -> High.
    // The LOWEST ask ($101) is at the top (Best Price for buyer).
    std::map<double, std::list<Order>> asks;

public:
    // Adds an order to the book and checks for matches
    void addOrder(int id, double price, int quantity, Side side);

    // The Engine: Matches Bids and Asks
    void match();

    // Visualizes the book in the console
    void printBook();
};