#include "OrderBook.h"

int main() {
    std::cout << "Initializing High-Frequency Trading Engine...\n\n";
    
    // Create the Market
    OrderBook book;
    
    // --- SCENARIO 1: Building Liquidity ---
    // Imagine 3 sellers arrive at the exchange.
    std::cout << "[Action] Adding liquidity (Sellers)...\n";
    
    // Seller A: Offers 10 shares at $100
    book.addOrder(1, 100.00, 10, Side::SELL);
    
    // Seller B: Offers 20 shares at $100 
    // (Arrived later, so they are BEHIND Seller A in the queue)
    book.addOrder(2, 100.00, 20, Side::SELL); 
    
    // Seller C: Offers 50 shares at $102
    // (Worse price, so they are further down the list)
    book.addOrder(3, 102.00, 50, Side::SELL); 
    
    // Show the book before any trading happens
    book.printBook(); 

    // --- SCENARIO 2: The Aggressive Buyer (Market Sweep) ---
    // A buyer wants 25 shares. They are willing to pay up to $101.
    // Logic Expectation:
    // 1. Matches 10 shares with Seller A (Best Price + First in Line)
    // 2. Matches 15 shares with Seller B (Best Price + Second in Line)
    // 3. Seller C is untouched.
    std::cout << "[Action] Aggressive Buyer incoming (25 shares @ $101)...\n";
    book.addOrder(4, 101.00, 25, Side::BUY);

    // Show the result
    book.printBook(); 
    
    return 0;
}