#include "trade.h"
#include "websocket.h"
#include <iostream>
#include <unordered_map>
#include "json.hpp"

TradingLogic::TradingLogic(ThreadPool &pool, WebSocketHandler &websocket)
    : thread_pool(pool), websocket(websocket) {}

void TradingLogic::executeTrades()
{
    try
    {
        while (true)
        {
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

            if (choice == 6)
            {
                std::cout << "Exiting trading application.\n";
                break;
            }

            switch (choice)
            {
            case 1:
            { // Place Order
                std::string instrument_name;
                double amount, price;
                std::cout << "Enter instrument name (e.g., BTC-PERPETUAL): ";
                std::cin >> instrument_name;
                std::cout << "Enter amount: ";
                std::cin >> amount;
                std::cout << "Enter price: ";
                std::cin >> price;

                thread_pool.submit([this, instrument_name, amount, price]()
                                   { placeOrder(instrument_name, amount, price); }, true); // Mark as critical
                break;
            }
            case 2:
            { // Cancel Order
                std::string order_id;
                std::cout << "Enter order ID to cancel: ";
                std::cin >> order_id;

                thread_pool.submit([this, order_id]()
                                   { cancelOrder(order_id); }, true); // Mark as critical
                break;
            }
            case 3:
            { // Modify Order
                std::string order_id;
                double price, amount;
                std::cout << "Enter order ID to modify: ";
                std::cin >> order_id;
                std::cout << "Enter new price: ";
                std::cin >> price;
                std::cout << "Enter new amount: ";
                std::cin >> amount;

                thread_pool.submit([this, order_id, price, amount]()
                                   { modifyOrder(order_id, price, amount); }, true); // Mark as critical
                break;
            }
            case 4:
            { // Get Order Book
                std::string instrument_name;
                std::cout << "Enter instrument name to view order book (e.g., BTC-PERPETUAL): ";
                std::cin >> instrument_name;

                thread_pool.submit([this, instrument_name]()
                                   {
                    auto order_book = getOrderBook(instrument_name);
                    std::cout << "Order Book: " << order_book.dump(4) << std::endl; });
                break;
            }
            case 5:
            { // View Current Positions
                thread_pool.submit([this]()
                                   {
                    auto positions = getPositions();
                    std::cout << "Current Positions: " << positions.dump(4) << std::endl; });
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in executeTrades: " << e.what() << std::endl;
    }
}

void TradingLogic::placeOrder(const std::string &instrument_name, double amount, double price)
{
    json payload = {
        {"method", "private/buy"},
        {"params", {{"instrument_name", instrument_name}, {"amount", amount}, {"price", price}, {"type", "limit"}}}};
    websocket.sendMessage(payload);
}

void TradingLogic::cancelOrder(const std::string &order_id)
{
    json payload = {
        {"method", "private/cancel"},
        {"params", {{"order_id", order_id}}}};
    websocket.sendMessage(payload);
}

void TradingLogic::modifyOrder(const std::string &order_id, double price, double amount)
{
    nlohmann::json payload = {
        {"method", "private/edit"},
        {"params", {{"order_id", order_id}, {"price", price}, {"amount", amount}}}};
    websocket.sendMessage(payload);
}

nlohmann::json TradingLogic::getOrderBook(const std::string &instrument_name)
{
    json payload = {
        {"method", "public/get_order_book"},
        {"params", {{"instrument_name", instrument_name}}}};
    websocket.sendMessage(payload);
    return websocket.readMessage();
}

nlohmann::json TradingLogic::getPositions()
{
    json payload = {
        {"method", "private/get_positions"},
        {"params", {}}};
    websocket.sendMessage(payload);
    return websocket.readMessage();
}