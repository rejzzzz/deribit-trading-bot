#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
#include "trade.h"
#include "threads.h"
#include "websocket.h"

// Function to parse the .env file
std::map<std::string, std::string> loadEnvFile(const std::string &filePath = ".env")
{
    std::map<std::string, std::string> envMap;
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open .env file.");
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        // Split line into key and value
        size_t delimiterPos = line.find('=');
        if (delimiterPos == std::string::npos)
        {
            throw std::runtime_error("Invalid format in .env file: " + line);
        }

        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);

        envMap[key] = value;
    }

    file.close();
    return envMap;
}

int main()
{
    try
    {
        // Step 1: Load environment variables from .env file
        std::map<std::string, std::string> env = loadEnvFile();

        // Step 2: Fetch CLIENT_ID and CLIENT_SECRET from the parsed map
        const std::string &client_id = env["CLIENT_ID"];
        const std::string &client_secret = env["CLIENT_SECRET"];

        if (client_id.empty() || client_secret.empty())
        {
            throw std::runtime_error("CLIENT_ID or CLIENT_SECRET not found in .env file.");
        }

        std::cout << "Loaded credentials from .env file." << std::endl;

        // Step 3: Initialize the thread pool with 4 worker threads
        ThreadPool pool(4);

        // Step 4: Initialize the WebSocket handler with Deribit Testnet details
        WebSocketHandler websocket("test.deribit.com", "443", "/ws/api/v2");

        // Step 5: Connect to the WebSocket server
        std::cout << "Connecting to WebSocket server..." << std::endl;
        websocket.connect();

        // Step 6: Authenticate using CLIENT_ID and CLIENT_SECRET
        json auth_payload = {
            {"method", "public/auth"},
            {"params", {{"grant_type", "client_credentials"}, {"client_id", client_id}, {"client_secret", client_secret}}}};
        websocket.sendMessage(auth_payload);
        json auth_response = websocket.readMessage();
        std::cout << "Authentication response: " << auth_response.dump(4) << std::endl;

        // Step 7: Initialize the trading logic with the thread pool and WebSocket handler
        TradingLogic trading_logic(pool, websocket);

        // Step 8: Start the trading loop
        std::cout << "Starting trading application..." << std::endl;
        trading_logic.executeTrades();

        // Step 9: Close the WebSocket connection gracefully
        std::cout << "Closing WebSocket connection..." << std::endl;
        websocket.close();
    }
    catch (const std::exception &e)
    {
        // Handle any exceptions and log the error
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}