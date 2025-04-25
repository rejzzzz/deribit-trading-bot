#ifndef TRADING_LOGIC_H
#define TRADING_LOGIC_H

#include <string>
#include <json.hpp> // Assuming you're using nlohmann/json for JSON handling
#include "threads.h"
#include "websocket.h"

class TradingLogic
{
public:
    TradingLogic(ThreadPool &pool, WebSocketHandler &websocket);

    void executeTrades();

    void placeOrder(const std::string &instrument_name, double amount, double price);
    void cancelOrder(const std::string &order_id);
    void modifyOrder(const std::string &order_id, double price, double amount);
    nlohmann::json getOrderBook(const std::string &instrument_name);
    nlohmann::json getPositions();

private:
    ThreadPool &thread_pool;
    WebSocketHandler &websocket;
};

#endif // TRADING_LOGIC_H