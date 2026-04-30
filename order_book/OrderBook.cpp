#include "OrderBook.h"

void OrderBook::addOrder(int id, double price, int quantity, Side side) {
    Order newOrder = {id, price, quantity, side};

    // Route the order to the correct queue
    if (side == Side::BUY) {
        bids[price].push_back(newOrder);
    } else {
        asks[price].push_back(newOrder);
    }
    
    // Instantly check if this new order triggers a trade
    match();
}

void OrderBook::match() {
    // Keep looking for trades as long as we have both buyers and sellers waiting
    while (!bids.empty() && !asks.empty()) {
        auto bestBidIter = bids.begin(); 
        auto bestAskIter = asks.begin();

        // If the best buyer is offering LESS than the best seller wants, trading stops.
        if (bestBidIter->first < bestAskIter->first) {
            break; 
        }

        // We have a match! Let's grab the actual tickets at the front of the line
        Order& buyOrder = bestBidIter->second.front();
        Order& sellOrder = bestAskIter->second.front();

        // Trade exactly as much as the smaller order allows
        int tradeQty = std::min(buyOrder.quantity, sellOrder.quantity);

        // --- HUMANIZED CONSOLE OUTPUT ---
        std::cout << "[TRADE MATCHED] 🤝 " << tradeQty 
                  << " shares sold at $" << sellOrder.price 
                  << " (Buyer ID: " << buyOrder.id 
                  << " -> Seller ID: " << sellOrder.id << ")\n";

        // Save it permanently to our CSV file
        logger.logTrade(buyOrder.id, sellOrder.price, tradeQty, "BUY");

        // Deduct the traded shares from both parties
        buyOrder.quantity -= tradeQty;
        sellOrder.quantity -= tradeQty;

        // If the buyer got all their shares, remove them from the line
        if (buyOrder.quantity == 0) {
            bestBidIter->second.pop_front();
            if (bestBidIter->second.empty()) {
                bids.erase(bestBidIter); // Clean up the empty price level
            }
        }

        // If the seller sold all their shares, remove them from the line
        if (sellOrder.quantity == 0) {
            bestAskIter->second.pop_front();
            if (bestAskIter->second.empty()) {
                asks.erase(bestAskIter); // Clean up the empty price level
            }
        }
    }
}

void OrderBook::printBook() {
    std::cout << "\n========== CURRENT MARKET ==========\n";
    std::cout << "🔻 ASKS (Sellers Waiting)\n";
    for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
        std::cout << "   Price: $" << it->first << " | Queue: ";
        for (const auto& o : it->second) std::cout << "[" << o.quantity << " shares] ";
        std::cout << "\n";
    }
    std::cout << "------------------------------------\n";
    std::cout << "🟩 BIDS (Buyers Waiting)\n";
    for (const auto& [price, list] : bids) {
        std::cout << "   Price: $" << price << " | Queue: ";
        for (const auto& o : list) std::cout << "[" << o.quantity << " shares] ";
        std::cout << "\n";
    }
    std::cout << "====================================\n\n";
}