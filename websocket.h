#pragma once
#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <openssl/ssl.h>
#include <boost/beast/websocket.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl.hpp>
#include "json.hpp"
#include <boost/beast/core.hpp>

#include <string>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace ssl = asio::ssl;
using json = nlohmann::json;
using tcp = asio::ip::tcp;

class WebSocketHandler
{
public:
    WebSocketHandler(const std::string &host, const std::string &port, const std::string &endpoint);
    void connect();
    void inMessage(const std::string &msg);
    void sendMessage(const json &message);
    json readMessage();
    void close();

private:
    asio::io_context ioc_;
    std::string endpoint_;
    tcp::resolver resolver_;
    std::string host_;
    ssl::context ctx_;
    beast::websocket::stream<ssl::stream<tcp::socket>> websocket_;
};

#endif // WEBSOCKET_H