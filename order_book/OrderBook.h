#pragma once
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include "Logger.h"

enum class Side {
    BUY,
    SELL
};

struct Order {
    int id;
    double price;
    int quantity;
    Side side;
};

class OrderBook {
private:
    std::map<double, std::list<Order>, std::greater<double>> bids;
    std::map<double, std::list<Order>> asks;
    
    // Initialize the Logger to create "trades.csv"
    Logger logger{"trades.csv"}; 

public:
    void addOrder(int id, double price, int quantity, Side side);
    void match();
    void printBook();
};