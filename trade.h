#ifndef TRADING_LOGIC_H
#define TRADING_LOGIC_H

#include <string>
#include <nlohmann/json.hpp> // Correctly include the nlohmann/json header
#include "threads.h"

class TradingLogic {
public:
    explicit TradingLogic(ThreadPool& pool);

    void executeTrades();

private:
    ThreadPool& thread_pool;
    void placeOrder(const std::string& instrument_name, double amount, double price);
    void cancelOrder(const std::string& order_id);
    void modifyOrder(const std::string& order_id, double price, double amount);
    nlohmann::json getOrderBook(const std::string& instrument_name);
    nlohmann::json getPositions();
};

#endif // TRADING_LOGIC_H