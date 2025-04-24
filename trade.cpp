// entry point for the system
/**multithreading using thread pool & dynamic thread creation
 * hash table for quick access to data
 * websocket to deribit
 * will track time of each action for latency
 * error handling and try-catch
 *  
 * 
 */

 #include "trade.h"
 #include <iostream>
 #include <unordered_map>
 
 TradingLogic::TradingLogic(ThreadPool& pool) : thread_pool(pool) {}
 
 void TradingLogic::executeTrades() {
     try {
         std::unordered_map<std::string, nlohmann::json> order_cache;
 
         while (true) {
             std::cout << "\n--- Trading Menu ---\n";
             std::cout << "1. Place Order\n";
             std::cout << "2. Cancel Order\n";
             std::cout << "3. Modify Order\n";
             std::cout << "4. Get Order Book\n";
             std::cout << "5. View Current Positions\n";
             std::cout << "6. Exit\n";
             std::cout << "Enter your choice: ";
             int choice;
             std::cin >> choice;
 
             if (choice == 6) {
                 std::cout << "Exiting trading application.\n";
                 break;
             }
 
             switch (choice) {
             case 1: {  // Place Order
                 std::string instrument_name;
                 double amount, price;
                 std::cout << "Enter instrument name (e.g., BTC-PERPETUAL): ";
                 std::cin >> instrument_name;
                 std::cout << "Enter amount: ";
                 std::cin >> amount;
                 std::cout << "Enter price: ";
                 std::cin >> price;
 
                 thread_pool.submit([this, instrument_name, amount, price]() {
                     placeOrder(instrument_name, amount, price);
                 }, true); // Mark as critical
                 break;
             }
             case 2: {  // Cancel Order
                 std::string order_id;
                 std::cout << "Enter order ID to cancel: ";
                 std::cin >> order_id;
 
                 thread_pool.submit([this, order_id]() {
                     cancelOrder(order_id);
                 }, true); // Mark as critical
                 break;
             }
             case 3: {  // Modify Order
                 std::string order_id;
                 double price, amount;
                 std::cout << "Enter order ID to modify: ";
                 std::cin >> order_id;
                 std::cout << "Enter new price: ";
                 std::cin >> price;
                 std::cout << "Enter new amount: ";
                 std::cin >> amount;
 
                 thread_pool.submit([this, order_id, price, amount]() {
                     modifyOrder(order_id, price, amount);
                 }, true); // Mark as critical
                 break;
             }
             case 4: {  // Get Order Book
                 std::string instrument_name;
                 std::cout << "Enter instrument name to view order book (e.g., BTC-PERPETUAL): ";
                 std::cin >> instrument_name;
 
                 thread_pool.submit([this, instrument_name]() {
                     auto order_book = getOrderBook(instrument_name);
                     std::cout << "Order Book: " << order_book.dump(4) << std::endl;
                 });
                 break;
             }
             case 5: {  // View Current Positions
                 thread_pool.submit([this]() {
                     auto positions = getPositions();
                     std::cout << "Current Positions: " << positions.dump(4) << std::endl;
                 });
                 break;
             }
             default:
                 std::cout << "Invalid choice. Please try again.\n";
                 break;
             }
         }
     } catch (const std::exception& e) {
         std::cerr << "Error in executeTrades: " << e.what() << std::endl;
     }
 }
 
 void TradingLogic::placeOrder(const std::string& instrument_name, double amount, double price) {
     std::cout << "Placing order for " << instrument_name << " with amount " << amount << " at price " << price << std::endl;
     // Simulate placing an order (replace with actual API call)
 }
 
 void TradingLogic::cancelOrder(const std::string& order_id) {
     std::cout << "Canceling order with ID: " << order_id << std::endl;
     // Simulate canceling an order (replace with actual API call)
 }
 
 void TradingLogic::modifyOrder(const std::string& order_id, double price, double amount) {
     std::cout << "Modifying order with ID: " << order_id << " to price " << price << " and amount " << amount << std::endl;
     // Simulate modifying an order (replace with actual API call)
 }
 
 nlohmann::json TradingLogic::getOrderBook(const std::string& instrument_name) {
     std::cout << "Fetching order book for " << instrument_name << std::endl;
     // Simulate fetching order book (replace with actual API call)
     return nlohmann::json::object();
 }
 
 nlohmann::json TradingLogic::getPositions() {
     std::cout << "Fetching current positions" << std::endl;
     // Simulate fetching positions (replace with actual API call)
     return nlohmann::json::array();
 }