#include "OrderBook.h"

// 1. ADD ORDER FUNCTION
// Takes an order and puts it into the correct list (Bids or Asks)
void OrderBook::addOrder(int id, double price, int quantity, Side side) {
    // Create the new order
    Order newOrder = {id, price, quantity, side};

    // Add it to the correct side of the book
    if (side == Side::BUY) {
        // Bids: Buyers want low prices, but we sort High->Low (std::greater)
        // .push_back adds to the END of the list (Time Priority)
        bids[price].push_back(newOrder);
    } else {
        // Asks: Sellers want high prices, we sort Low->High (Standard)
        asks[price].push_back(newOrder);
    }
    
    // Every time an order is added, we immediately check if a trade is possible
    match();
}

// 2. MATCHING ENGINE (The Core Logic)
// Checks if the Best Buyer and Best Seller agree on a price
void OrderBook::match() {
    // Keep looping as long as there are orders on both sides
    while (!bids.empty() && !asks.empty()) {
        
        // Peek at the top of both books
        auto bestBidIter = bids.begin();  // Highest Buy Price
        auto bestAskIter = asks.begin();  // Lowest Sell Price

        // CHECK PRICE: If Buyer's Price is LOWER than Seller's Price, no trade.
        if (bestBidIter->first < bestAskIter->first) {
            break; // Stop matching
        }

        // EXECUTE TRADE
        // Get the actual Order objects from the front of the list
        Order& buyOrder = bestBidIter->second.front();
        Order& sellOrder = bestAskIter->second.front();

        // Calculate how much can be traded (the smaller of the two quantities)
        int tradeQty = std::min(buyOrder.quantity, sellOrder.quantity);

        // Print the trade execution to the console
        std::cout << "TRADE EXEC: " << tradeQty << " shares @ $" << sellOrder.price << std::endl;

        // UPDATE QUANTITIES (Partial Fills)
        buyOrder.quantity -= tradeQty;
        sellOrder.quantity -= tradeQty;

        // CLEANUP: If an order is fully filled (0 qty), remove it from the list
        if (buyOrder.quantity == 0) {
            bestBidIter->second.pop_front(); // Remove from list
            // If the list is now empty, remove the price level entirely
            if (bestBidIter->second.empty()) {
                bids.erase(bestBidIter);
            }
        }

        if (sellOrder.quantity == 0) {
            bestAskIter->second.pop_front();
            if (bestAskIter->second.empty()) {
                asks.erase(bestAskIter);
            }
        }
        
        // The loop repeats automatically to see if the remaining order can match again
    }
}

// 3. PRINT BOOK (Visualization)
// Shows us what the market looks like right now
void OrderBook::printBook() {
    std::cout << "\n--- ASKS (Sellers) ---\n";
    // Iterate backwards (rbegin) to show highest prices at the top
    for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
        std::cout << "$" << it->first << " : ";
        for (const auto& o : it->second) std::cout << "(" << o.quantity << ") ";
        std::cout << "\n";
    }
    std::cout << "--- BIDS (Buyers) ---\n";
    for (const auto& [price, list] : bids) {
        std::cout << "$" << price << " : ";
        for (const auto& o : list) std::cout << "(" << o.quantity << ") ";
        std::cout << "\n";
    }
    std::cout << "----------------------\n\n";
}